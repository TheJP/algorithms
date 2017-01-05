﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CityPuzzle
{
    class Program
    {
        private enum Rotations { No, Two, Four }

        private static int previewSlowDown = 100;
        private static bool showLifePreviewOnConsole = true;
        private static bool showSolutionsOnConsole = false;
        private const int FieldDimension = 7;

        private static int solutionCount = 0;

        //Create field with border
        private static bool[][] field = Enumerable.Range(0, FieldDimension + 2).Select(y =>
            Enumerable.Range(0, FieldDimension + 2).Select(x =>
                x == 0 || y == 0 || x == FieldDimension + 1 || y == FieldDimension + 1
            ).ToArray()).ToArray();

        //Colors used to draw solutions
        private static ConsoleColor[] colors = new ConsoleColor[]
        {
            ConsoleColor.White, ConsoleColor.Yellow, ConsoleColor.Magenta, ConsoleColor.Red,
            ConsoleColor.Cyan, ConsoleColor.Green, ConsoleColor.Blue, ConsoleColor.DarkGreen,
            ConsoleColor.DarkRed, ConsoleColor.Black
        };

        //Create pieces in all needed rotations
        private static bool[][][][] pieces =
        {
            //8
            CreatePiece(new bool[,]
            {
                {  false, true, false },
                { true, true, true },
                { true, true, true },
                { true, false, false }
            }, Rotations.No),

            //7
            CreatePiece(new bool[,]
            {
                { false, true, false },
                { true, true, true },
                { true, true, true },
            }),

            //6
            CreatePiece(new bool[,]
            {
                { false, false, true},
                { false, true, true },
                { true, true, true },
            }),

            CreatePiece(new bool[,]
            {
                { false, true },
                { true, true },
                { true, true },
                { false, true }
            }),

            //5
            CreatePiece(new bool[,]
            {
                { false, true },
                { false, true },
                { true, true },
                { false, true }
            }),

            CreatePiece(new bool[,]
            {
                { true, true, true, true, true }
            }, Rotations.Two),

            CreatePiece(new bool[,]
            {
                { false, false, true},
                { false, true, true },
                { true, true, false },
            }),

            //4
            CreatePiece(new bool[,]
            {
                { false, true, false },
                { true, true, true },
            }),

            //2
            CreatePiece(new bool[,]
            {
                { true, true }
            }, Rotations.Two),

            //1 (Pin)
            CreatePiece(new bool[,]
            {
                { true }
            }, Rotations.No)
        };

        //Stores the location of pieces while searching solutions
        private static (int y, int x, int rotation)[] locations = new(int, int, int)[pieces.Length];

        private static List<(int y, int x, int rotation)[]> solutions = new List<(int, int, int)[]>();

        private static bool[][][] CreatePiece(bool[,] piece, Rotations rotations = Rotations.Four)
        {
            var results = new List<bool[][]>();

            var width = piece.GetLength(1);
            var height = piece.GetLength(0);
            var result = new bool[height][];
            for(int y = height - 1; y >= 0; --y)
            {
                result[y] = new bool[width];
                for(int x = 0; x < width; ++x)
                {
                    result[y][x] = piece[y, x];
                }
            }
            results.Add(result);

            bool[][] once = null;
            if (rotations != Rotations.No)
            {
                //Rotate at least once
                once = Rotate(result);
                results.Add(once);
            }

            if(rotations == Rotations.Four)
            {
                //Rotate 3 times (resulting in 4 rotations)
                var twice = Rotate(once);
                results.Add(twice);
                results.Add(Rotate(twice));
            }

            return results.ToArray();
        }

        private static bool[][] Rotate(bool[][] input)
        {
            var result = new bool[input[0].Length][];
            for(int y = 0; y < result.Length; ++y)
            {
                result[y] = new bool[input.Length];
                for(int x = 0; x < input.Length; ++x)
                {
                    //Affine transformation to rotate around center
                    result[y][x] = input[x][-y + result.Length - 1];
                }
            }
            return result;
        }

        /// <summary>Recursion to find all solutions</summary>
        private static void FindSolutions(int piece)
        {
            for(int rotation = 0; rotation < pieces[piece].Length; ++rotation)
            {
                bool[][] p = pieces[piece][rotation];
                for (int y = 1; y <= FieldDimension - p.Length + 1; ++y)
                {
                    for(int x = 1; x <= FieldDimension - p[0].Length + 1; ++x)
                    {
                        if (ValidLocation(y, x, p))
                        {
                            locations[piece] = (y, x, rotation);
                            SetPiece(piece, true);
                            if (piece + 1 >= pieces.Length)
                            {
                                //Found solution
                                ++solutionCount;
                                solutions.Add(((int, int, int)[])locations.Clone());
                                if (showSolutionsOnConsole) { PrintSolution(); }
                            }
                            else { FindSolutions(piece + 1); }
                            if (showLifePreviewOnConsole && previewSlowDown > 0) { System.Threading.Thread.Sleep(previewSlowDown); }
                            SetPiece(piece, false);
                        }
                    }
                }
            }
        }

        /// <summary>Check if the given coordinates are valid for the given piece on the field</summary>
        private static bool ValidLocation(int y, int x, bool[][] piece)
        {
            for(int dy = 0; dy < piece.Length; ++dy)
            {
                for(int dx = 0; dx < piece[dy].Length; ++dx)
                {
                    if(piece[dy][dx] && field[y + dy][x + dx]) { return false; }
                }
            }
            return true;
        }

        /// <summary>Set value of the piece on the field (can mean add or remove piece from field)</summary>
        private static void SetPiece(int piece, bool value)
        {
            var (y, x, rotation) = locations[piece];
            var p = pieces[piece][rotation];
            var cursor = (y: Console.CursorTop, x: Console.CursorLeft);
            if (showLifePreviewOnConsole && cursor.y + FieldDimension + 1 >= Console.BufferHeight)
            {
                showLifePreviewOnConsole = false;
                Console.WriteLine();
                Console.WriteLine("Reached Buffer Limit - Turned off life preview");
            }
            if (showLifePreviewOnConsole)
            {
                Console.WriteLine("Solution {0}", solutionCount);
                Console.BackgroundColor = value ? colors[piece] : ConsoleColor.Black;
            }
            for (int dy = 0; dy < p.Length; ++dy)
            {
                for (int dx = 0; dx < p[dy].Length; ++dx)
                {
                    if (p[dy][dx])
                    {
                        field[y + dy][x + dx] = value;
                        if (showLifePreviewOnConsole)
                        {
                            Console.CursorLeft = cursor.x + dx + locations[piece].x;
                            Console.CursorTop = cursor.y + dy + locations[piece].y;
                            Console.Write(" ");
                        }
                    }
                }
            }
            Console.CursorLeft = cursor.x;
            Console.CursorTop = cursor.y;
            Console.BackgroundColor = ConsoleColor.Black;
        }

        private static void PrintSolution()
        {
            var cursor = (y: Console.CursorTop, x: Console.CursorLeft);
            if (cursor.y + FieldDimension + 1 >= Console.BufferHeight) { return; }
            Console.BackgroundColor = ConsoleColor.Black;
            Console.WriteLine("Solution {0}", solutionCount);
            for (int piece = 0; piece < pieces.Length; ++piece)
            {
                if (locations[piece].x == 0) { break; } //0 means piece is not set (x and y are > 0)
                Console.BackgroundColor = colors[piece];
                var p = pieces[piece][locations[piece].rotation];
                for(int y = 0; y < p.Length; ++y)
                {
                    for(int x = 0; x < p[y].Length; ++x)
                    {
                        if (!p[y][x]) { continue; }
                        Console.CursorLeft = cursor.x + x + locations[piece].x;
                        Console.CursorTop = cursor.y + y + locations[piece].y;
                        Console.Write(" ");
                    }
                }
            }
            Console.CursorLeft = cursor.x + FieldDimension + 1;
            Console.CursorTop = cursor.y + FieldDimension + 1;
            Console.WriteLine();
            Console.BackgroundColor = ConsoleColor.Black;
        }

        static void Main(string[] args)
        {
            var background = Console.BackgroundColor;
            try { FindSolutions(0); }
            finally { Console.BackgroundColor = background; }
            Console.WriteLine("Found {0} solutions", solutionCount);
            Export(true);
        }

        private static string[] htmlColors = new string[] {
            //"yellow", "magenta", "red", "cyan", "lime", "blue", "green", "lightblue", "orange", "black"
            //"#1d6914", "#ad2323", "#2a4bd7", "#814a19", "#8126c0", "#81c570", "#9dafff", "#29d0d0", "#ff9233", "black", "#ffee33", "#e9debb", "#ffcdf3"
            //"#b58900", "#cb4b16", "#dc322f", "#d33682", "#6c71c4", "#268bd2", "#2aa198", "#859900", "gray", "black"
            "#acd964", "#5ac8fa", "#ffcc00", "#ff9500", "#c0504d", "#007aff", "#ff3b30", "#8e8e93", "#ceced2", "#333"
        };

        private static int RotationAmount(int y, int x)
        {
            int result = 0;
            while (y * 2 > FieldDimension + 1 || x * 2 > FieldDimension + 1 || (y * 2 == FieldDimension + 1 && x * 2 != FieldDimension + 1))
            {
                ++result;
                (y, x) = (x, -y + FieldDimension + 1);
            }
            return result;
        }

        private static Dictionary<(int y, int x), int> Rotate(Dictionary<(int y, int x), int> table) =>
            table.ToDictionary(entry => (entry.Key.x, -entry.Key.y + FieldDimension + 1), entry => entry.Value);

        private static void Export(bool grouped = false)
        {
            using (var writer = new StreamWriter("result.html", false, Encoding.UTF8))
            {
                writer.WriteLine("<!doctype html>");
                writer.WriteLine("<html><head><style>");
                //Style
                writer.WriteLine("td { width: 20px; height: 20px; }");
                writer.WriteLine("table { border-spacing: 0; display: inline-block; }");
                writer.WriteLine("h1 { font-family: Helvetica Neue,Helvetica,sans-serif; font-size: 18px; color: #333; }");
                writer.WriteLine("div { width: 630px; margin: 0 auto;  page-break-after: always; }");
                //Content
                writer.WriteLine("</style></head><body>");
                var htmlSolutions = solutions.Select(solution => solution.Select((p, piece) => (y: p.y, x: p.x, rotation: p.rotation, Piece: piece))
                    .SelectMany(p => pieces[p.Piece][p.rotation]
                        .SelectMany((row, dy) => row.Select((f, dx) => (y: p.y + dy, x: p.x + dx, Used: f, Piece: p.Piece))))
                    .Where(f => f.Used)
                    .ToDictionary(f => (y: f.y, x: f.x), f => f.Piece));

                if (grouped)
                {
                    //Rotate solutions to make grouping not dependend on rotation
                    var rotatedSolutions = htmlSolutions.Zip(solutions
                            .Select(solution => solution[pieces.Length - 1])
                            .Select(pin => RotationAmount(pin.y, pin.x)),
                            (table, rotation) => (Table: table, Rotation: rotation))
                        .Select(solution =>
                        {
                            var result = solution.Table;
                            for (int i = 0; i < solution.Rotation; ++i) { result = Rotate(result); }
                            return result;
                        });
                    var groupedSolutions = rotatedSolutions
                        .GroupBy(table => table.Single(entry => entry.Value == pieces.Length - 1).Key)
                        .OrderBy(group => group.Key.y)
                        .ThenBy(group => group.Key.x);
                    foreach(var group in groupedSolutions)
                    {
                        writer.WriteLine("<div>");
                        //writer.WriteLine("<h1>Count: {0}</h1>", group.Count());
                        foreach (var solution in group)
                        {
                            TableExport(solution);
                        }
                        writer.WriteLine("</div>");
                    }
                }
                else
                {
                    int i = 0;
                    foreach (var solution in htmlSolutions)
                    {
                        ++i;
                        writer.WriteLine("<h1>Solution {0}</h1>", i);
                        TableExport(solution);
                    }
                }
                writer.WriteLine("</body></html>");

                void TableExport(Dictionary<(int y, int x), int> table)
                {
                    writer.WriteLine("<table>");
                    for (int y = 1; y <= FieldDimension; ++y)
                    {
                        writer.WriteLine("<tr>");
                        for (int x = 1; x <= FieldDimension; ++x)
                        {
                            writer.WriteLine("<td style=\"background-color: {0}\"></td>", htmlColors[table.ContainsKey((y, x)) ? table[(y, x)] : pieces.Length]);
                        }
                        writer.WriteLine("</tr>");
                    }
                    writer.WriteLine("</table>");
                }
            }
        }
    }
}

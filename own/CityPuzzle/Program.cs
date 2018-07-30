using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CityPuzzle
{
    class Program
    {
        private enum Rotations { No, Two, Four }

        private static int previewSlowDown = 0;
        private static int sleepAfterSolution = 3000;
        private static bool showLifePreviewOnConsole = true;
        private static bool showSolutionsOnConsole = false;
        public const int FieldDimension = 7;

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
                var p = pieces[piece][rotation];
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
                                if (sleepAfterSolution > 0) { System.Threading.Thread.Sleep(sleepAfterSolution); }
                                Console.WriteLine($"Solutions: {solutionCount} Average time: {(stopwatch.ElapsedMilliseconds / 1000.0) / solutionCount:0.0000}s");
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
            var cursor = (y: 0, x: 0);
            if (showLifePreviewOnConsole)
            {
                cursor = (y: Console.CursorTop, x: Console.CursorLeft);
                if (cursor.y + FieldDimension + 1 >= Console.BufferHeight)
                {
                    showLifePreviewOnConsole = false;
                    Console.WriteLine();
                    Console.WriteLine("Reached Buffer Limit - Turned off life preview");
                }
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
            if (showLifePreviewOnConsole)
            {
                Console.CursorLeft = cursor.x;
                Console.CursorTop = cursor.y;
                Console.BackgroundColor = ConsoleColor.Black;
            }
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
            Measure();
        }

        private static void RunAndExport()
        {
            var background = Console.BackgroundColor;
            try { FindSolutions(0); }
            finally { Console.BackgroundColor = background; }
            Console.WriteLine("Found {0} solutions", solutionCount);
            new Exporter().Export(pieces, solutions, true);
        }

        private readonly static Stopwatch stopwatch = new Stopwatch();
        private static void Measure()
        {
            Array.Reverse(pieces);
            previewSlowDown = 0;
            sleepAfterSolution = 0;
            showLifePreviewOnConsole = false;
            showSolutionsOnConsole = false;
            
            stopwatch.Start();
            int testAmount = 1;
            for (int i = 0; i < testAmount; ++i)
            {
                solutions.Clear();
                solutionCount = 0;
                FindSolutions(0);
            }
            stopwatch.Stop();
            Console.WriteLine($"Found {solutionCount} solutions {testAmount} times in {stopwatch.ElapsedMilliseconds / 1000.0:0.0000}s");
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CityPuzzle
{
    class Program
    {
        private enum Rotations { No, Two, Four }

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
            ConsoleColor.DarkRed
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
                for (int y = 1; y < FieldDimension + 1 - p.Length + 1; ++y)
                {
                    for(int x = 1; x < FieldDimension + 1 - p[0].Length + 1; ++x)
                    {
                        if (ValidLocation(y, x, p))
                        {
                            SetPiece(y, x, p, true);
                            locations[piece] = (y, x, rotation);
                            if (piece + 1 >= pieces.Length)
                            {
                                //Found solution
                                ++solutionCount;
                                solutions.Add(((int, int, int)[])locations.Clone());
                                if (showSolutionsOnConsole) { PrintSolution(); }
                            }
                            else { FindSolutions(piece + 1); }
                            SetPiece(y, x, p, false);
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
        private static void SetPiece(int y, int x, bool[][] piece, bool value)
        {
            for (int dy = 0; dy < piece.Length; ++dy)
            {
                for (int dx = 0; dx < piece[dy].Length; ++dx)
                {
                    if (piece[dy][dx]) { field[y + dy][x + dx] = value; }
                }
            }
        }

        private static void PrintSolution()
        {
            var cursor = (y: Console.CursorTop, x: 0);
            if (cursor.y + FieldDimension + 1 >= Console.BufferHeight) { return; }
            Console.BackgroundColor = ConsoleColor.Black;
            Console.Write("Solution {0}", solutionCount);
            for (int piece = 0; piece < pieces.Length; ++piece)
            {
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
        }

        static void Main(string[] args)
        {
            var background = Console.BackgroundColor;
            try { FindSolutions(0); }
            finally { Console.BackgroundColor = background; }
            Console.WriteLine("Found {0} solutions", solutionCount);
        }
    }
}

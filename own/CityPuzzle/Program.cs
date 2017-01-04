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

        private const int FieldDimension = 7;

        //Create field with border
        private static bool[][] field = Enumerable.Range(0, FieldDimension + 2).Select(y =>
            Enumerable.Range(0, FieldDimension + 2).Select(x =>
                x == 0 || y == 0 || x == FieldDimension + 1 || y == FieldDimension + 1
            ).ToArray()).ToArray();

        //Stores the location of pieces while searching solutions
        private static (int x, int y, int rotation)[] locations = new (int, int, int)[pieces.Length];

        //All found solutions are stored here
        private static List<(int x, int y, int rotation)[]> solutions = new List<(int x, int y, int rotation)[]>();

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
                for(int y = 1; y < FieldDimension + 1 - pieces[piece][rotation].Length + 1; ++y)
                {
                    for(int x = 1; x < FieldDimension + 1 - pieces[piece][rotation][0].Length + 1; ++x)
                    {

                    }
                }
            }
        }

        static void Main(string[] args)
        {
            FindSolutions(0);
        }
    }
}

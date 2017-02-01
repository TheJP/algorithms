using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static CityPuzzle.Program;

namespace CityPuzzle
{
    class Exporter
    {
        private static string[] htmlColors = new string[] {
            //"yellow", "magenta", "red", "cyan", "lime", "blue", "green", "lightblue", "orange", "black"
            //"#1d6914", "#ad2323", "#2a4bd7", "#814a19", "#8126c0", "#81c570", "#9dafff", "#29d0d0", "#ff9233", "black", "#ffee33", "#e9debb", "#ffcdf3"
            //"#b58900", "#cb4b16", "#dc322f", "#d33682", "#6c71c4", "#268bd2", "#2aa198", "#859900", "gray", "black"
            "#acd964", "#5ac8fa", "#ffcc00", "#ff9500", "#c0504d", "#007aff", "#ff3b30", "#8e8e93", "#ceced2", "#333"
        };

        public void Export(bool[][][][] pieces, IEnumerable<(int y, int x, int rotation)[]> solutions, bool grouped = false, string file = "result.html")
        {
            using (var writer = new StreamWriter(file, false, Encoding.UTF8))
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
                    foreach (var group in groupedSolutions)
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
    }
}

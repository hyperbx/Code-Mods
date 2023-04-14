using System.Text.RegularExpressions;

namespace BT2CPP
{
    class Program
    {
        static bool PreserveSummaries = true;

        static List<string> StringsForLineRemoval = new()
        {
            "local uint64 BASE_OFFSET_VALUE<hidden=true>;",
            "local uint64 p<hidden=true> = FTell();"
        };

        static Dictionary<string, string> ReplacementPatterns = new()
        {
            { @"FSeek\(p \+ \d+\);", string.Empty },
            { @"^enum<(\w+)> (\w+)$", "enum $2 : $1" },
            { @"^enum<(\w+)> (\w+) {$", "enum $2 : $1 {" },
            { "<hidden=true>", string.Empty },
            { @"\bvector2\b", "Vector2" },
            { @"\bvector3\b", "Vector3" },
            { @"\bquaternion\b", "Quaternion" },
            { @"\bsint8\b", "int8_t" },
            { @"\buint8\b", "uint8_t" },
            { @"\bbyte\b", "uint8_t" },
            { @"\bsint16\b", "int16_t" },
            { @"\buint16\b", "uint16_t" },
            { @"\bsint32\b", "int32_t" },
            { @"\buint32\b", "uint32_t" },
            { @"\bsint64\b", "int64_t" },
            { @"\buint64\b", "uint64_t" },
        };

        static List<string> Output = new();

        static void Main(string[] args)
        {
            Console.WriteLine
            (
                "BT2CPP - Sonic Frontiers Binary Template to C++ Converter\n" +
                "Written by Hyper\n"
            );

            if (args.Length == 0)
            {
                Console.WriteLine
                (
                    "Usage;\n" +
                    "BT2CPP.exe [flags] [files]\n\n" +

                    "Flags;\n" +
                    "--no-summary - does not preserve RFL comments as summaries."
                );
            }

            foreach (string arg in args)
            {
                Output.Clear();

                if (arg == "--no-summary")
                    PreserveSummaries = false;

                if (!File.Exists(arg))
                    continue;

                Console.WriteLine($"File: {arg}");

                using (StreamReader reader = new(arg))
                {
                    while (!reader.EndOfStream)
                    {
                        string line = reader.ReadLine();

                        if (string.IsNullOrEmpty(line))
                            continue;

                        if (StringsForLineRemoval.Any(line.Contains))
                            continue;

                        if (line.StartsWith("typedef") && line.EndsWith(";"))
                            continue;

                        // end of file
                        if (line.Contains("LittleEndian();"))
                            break;

                        foreach (var pattern in ReplacementPatterns)
                            line = Regex.Replace(line, pattern.Key, pattern.Value);

                        string commentPattern = @"^(.*?)<comment=""([^""]+)""(,optimize=false)?>;";
                        {
                            if (Regex.IsMatch(line, commentPattern))
                            {
                                if (PreserveSummaries)
                                {
                                    line = Regex.Replace(line, commentPattern, m => $"\t/// <summary>\n\t/// {m.Groups[2].Value}\n\t/// </summary>\n\t{m.Groups[1].Value.TrimStart()};");
                                }
                                else
                                {
                                    line = Regex.Replace(line, commentPattern, m => $"\t{m.Groups[1].Value.TrimStart()};");
                                }
                            }
                        }

                        Output.Add(line);
                    }
                }

                Output.RemoveAll(x => string.IsNullOrEmpty(x) || string.IsNullOrWhiteSpace(x));

                // bad code I don't care
                for (int i = 0; i < Output.Count; i++)
                {
                    string line = Output[i];

                    if (line == "} Vector3;" || line == "} Quaternion;")
                        Output.RemoveRange(i - 5, 6);

                    if (line == "} cstring<read=ReadCString>;")
                    {
                        Output.RemoveRange(i - 2, 7);
                        Output.Insert(i - 2, "typedef struct\n{\n    const char* value;\n\n    INSERT_PADDING(8);\n\n} cstring;");
                    }

                    if (line == "enum bool : uint8_t {")
                        Output.RemoveRange(i, 4);
                }

                for (int i = 0; i < Output.Count; i++)
                {
                    if (Output[i].EndsWith(";"))
                        Output[i] += "\n";
                }

                Output.Insert(0, "#pragma once\n\n#include <gmath/Vector2.hpp>\n#include <gmath/Vector3.hpp>\n#include <gmath/Quaternion.hpp>\n");

                File.WriteAllText(Path.Combine(Path.GetDirectoryName(arg), $"{Path.GetFileNameWithoutExtension(arg)}.h"), string.Join("\r\n", Output));
            }
        }
    }
}
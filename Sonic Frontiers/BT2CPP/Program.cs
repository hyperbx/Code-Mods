using System.Text.RegularExpressions;

namespace BT2CPP
{
    class Program
    {
        static bool IsPreserveSummaries = true;
        static bool IsCSharpOutput = false;

        static List<string> StringsForLineRemoval = new()
        {
            "local uint64 BASE_OFFSET_VALUE<hidden=true>;",
            "local uint64 p<hidden=true> = FTell();"
        };

        static Dictionary<string, string> ReplacementPatternsCPP = new()
        {
            { @"FSeek\(p \+ \d+\);", string.Empty },
            { @"^enum<(\w+)> (\w+)$", "enum $2 : $1" },
            { @"^enum<(\w+)> (\w+) {$", "enum $2 : $1 {" },
            { "<hidden=true>", string.Empty },
            { @"\bvector2\b", "csl::math::Vector2" },
            { @"\bvector3\b", "csl::math::Vector3" },
            { @"\bquaternion\b", "csl::math::Quaternion" },
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

        static Dictionary<string, string> ReplacementPatternsCSharp = new()
        {
            { @"FSeek\(p \+ (\d+)\);(?=.*;.*)", "[FieldOffset($1)]" },
            { @"FSeek\(p \+ (\d+)\);", "// STRUCT SIZE: $1" },
            { @"\bparams\b", "parameters" },
            { @"^enum<(\w+)> (\w+)$", "public enum $2 : $1" },
            { @"^enum<(\w+)> (\w+) {$", "enum $2 : $1 {" },
            // { @"(\w+)\s+(\w+)\[(\d+)\]", "[MarshalAs(UnmanagedType.ByValArray, SizeConst = $3)] public $1[] $2" },
            { @"(\w+)\s+(\w+)\[(\d+)\]", "/* ARRAY SIZE: $3 */ public fixed $1 $2[$3]" },
            { "<hidden=true>", string.Empty },
            { @"\bvector2\b", "Vector2" },
            { @"\bvector3\b", "Vector4" },
            { @"\bcolorF\b", "Vector4" },
            { @"\bquaternion\b", "Quaternion" },
            { @"\bsint8\b", "sbyte" },
            { @"\buint8\b", "byte" },
            { @"\bbyte\b", "byte" },
            { @"\bsint16\b", "short" },
            { @"\buint16\b", "ushort" },
            { @"\bsint32\b", "int" },
            { @"\buint32\b", "uint" },
            { @"\bsint64\b", "long" },
            { @"\buint64\b", "ulong" },
            { @"\bcstring\b", "CString" }
        };

        static readonly string CSharpStructLayout = "[StructLayout(LayoutKind.Explicit)]";

        static List<string> Output = new();

        static void Main(string[] args)
        {
            Console.WriteLine
            (
                "BT2CPP - Sonic Frontiers Binary Template Converter\n" +
                "Written by Hyper\n"
            );

            if (args.Length == 0)
            {
                Console.WriteLine
                (
                    "Usage;\n" +
                    "BT2CPP.exe [flags] [files]\n\n" +

                    "Flags;\n" +
                    "--no-summary - does not preserve RFL comments as summaries." +
                    "--csharp - output in C# format (default is C++)."
                );
            }

            foreach (string arg in args)
            {
                Output.Clear();

                if (arg == "--no-summary")
                    IsPreserveSummaries = false;

                if (arg == "--csharp")
                    IsCSharpOutput = true;

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

                        foreach (var pattern in (IsCSharpOutput ? ReplacementPatternsCSharp : ReplacementPatternsCPP))
                            line = Regex.Replace(line, pattern.Key, pattern.Value);

                        string commentPattern = @"^(.*?)<comment=""([^""]+)""(,optimize=false)?>;";
                        {
                            if (Regex.IsMatch(line, commentPattern))
                            {
                                if (IsPreserveSummaries)
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

                    if (line == "} Vector2;")
                        Output.RemoveRange(i - 3, 4);

                    if (line == "} colorF;" || line == "} Vector3;" || line == "} Vector4;" || line == "} Quaternion;")
                        Output.RemoveRange(i - 5, 6);

                    if (IsCSharpOutput && line == "} CString<read=ReadCString>;")
                    {
                        Output.RemoveRange(i - 2, 7);
                        Output.Insert
                        (
                            i - 2,

                            $"[StructLayout(LayoutKind.Explicit, Size = 16)]\n" +
                            "public struct CString\n" +
                            "{\n" +
                            "    [FieldOffset(0)] long pValue;\n" +
                            "}\n"
                        );
                    }
                    else if (line == "} cstring<read=ReadCString>;")
                    {
                        Output.RemoveRange(i - 2, 7);
                        Output.Insert(i - 2, "typedef struct\n{\n    const char* value;\n\n    INSERT_PADDING(8);\n\n} cstring;");
                    }

                    if (line == "enum bool : uint8_t {" || line == "enum bool : byte {")
                        Output.RemoveRange(i, 4);
                }

                for (int i = 0; i < Output.Count; i++)
                {
                    if (Output[i].EndsWith(";"))
                        Output[i] += "\n";
                }

                // worst code ever written
                if (IsCSharpOutput)
                {
                    Output.Insert(0, "using System.Numerics;\nusing System.Runtime.InteropServices;\n");

                    string input = string.Join("\r\n", Output);

                    var regex = new Regex(@"typedef\s+struct\s*{([^}]*)}\s*(\w+)\s*;");

                    string result = regex.Replace
                    (
                        input, match => $"{CSharpStructLayout}\npublic struct {match.Groups[2].Value}\n{{{match.Groups[1].Value.TrimEnd()}\n}}"
                    );

                    regex = new Regex(@"(\w+ )(\w+;)");

                    result = regex.Replace
                    (
                        result, match => $"public {match.Groups[1].Value}{match.Groups[2].Value}"
                    );

                    List<string> resultLines = result.Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries).ToList();
                    string currentStructSize = "";

                    Dictionary<string, int> structSizes = new()
                    {
                        { "Action", 1 },
                        { "Vector4", 16 }
                    };

                    for (int i = resultLines.Count - 1; i > 0; i--)
                    {
                        string line = resultLines[i];

                        if (line.Contains("STRUCT SIZE: "))
                        {
                            int colonIndex = line.IndexOf(':');

                            currentStructSize = line.Substring(colonIndex + 1, line.Length - (colonIndex + 1)).TrimStart();

                            continue;
                        }

                        if (line.Contains(CSharpStructLayout) && !string.IsNullOrEmpty(currentStructSize))
                        {
                            string structName = resultLines[i + 1].Split(' ')[2];
                            string structSizeName = $"{structName}Size";

                            structSizes.Add(structName, int.Parse(currentStructSize));

                            resultLines[i] = $"private const int {structSizeName} = {currentStructSize};\n[StructLayout(LayoutKind.Explicit, Size = {currentStructSize})]";
                        }
                    }

                    for (int i = 0; i < resultLines.Count; i++)
                    {
                        string line = resultLines[i];

                        if (line.Contains("/* ARRAY SIZE: "))
                        {
                            int currentArraySize = int.Parse(Regex.Match(line, @"\/\* ARRAY SIZE: (\d+) \*\/").Groups[1].Value);
                            string currentArrayType = Regex.Match(line, @"\bpublic\s+fixed\s+(\w+)\s+\w+\[\w+\];").Groups[1].Value;
                            string currentArrayName = Regex.Match(line, @"\bpublic\s+fixed\s+\w+\s+(\w+)\[\w+\];").Groups[1].Value;

                            if (structSizes.ContainsKey(currentArrayType))
                            {
                                resultLines[i] = $"{line.Substring(0, line.IndexOf(currentArrayType))}byte _{currentArrayName}[{structSizes[currentArrayType] * currentArraySize}];\n\n";

                                // lmao
                                resultLines[i] += $"\tpublic {currentArrayType}* {currentArrayName}\n" +
                                    "\t{\n" +
                                    "\t\tget\n" +
                                    "\t\t{\n" +
                                    $"\t\t\tfixed (byte* p_{currentArrayName} = _{currentArrayName})\n" +
                                    $"\t\t\t\treturn ({currentArrayType}*)p_{currentArrayName};\n" +
                                    "\t\t}\n" +
                                    "\t}";
                            }

                            continue;
                        }
                    }

                    File.WriteAllText(Path.Combine(Path.GetDirectoryName(arg), $"{Path.GetFileNameWithoutExtension(arg)}.cs"), string.Join("\n", resultLines));
                }
                else
                {
                    Output.Insert(0, "#pragma once\n\n#include <rangers-api/rangers-api/rangers-api.h>\n");

                    File.WriteAllText(Path.Combine(Path.GetDirectoryName(arg), $"{Path.GetFileNameWithoutExtension(arg)}.h"), string.Join("\r\n", Output));
                }
            }
        }

        static int GetArrayByType(string line, string type, string size)
        {
            switch (type)
            {
                case "Action":
                case "sbyte":
                case "byte":
                    return 1;

                case "short":
                case "ushort":
                    return 2;

                case "int":
                case "uint":
                    return 4;

                case "long":
                case "ulong":
                    return 8;

                case "Vector4":
                    return 16;
            }

            return -1;
        }
    }
}
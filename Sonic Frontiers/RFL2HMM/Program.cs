using System.Text;

namespace RFL2HMM
{
    class Program
    {
        private const string _version = "1.0.0";
        private const string _arrayDelimiter = "__arr";

        private static StringBuilder _output = new();

        static void Main(string[] args)
        {
            Console.WriteLine
            (
                $"RFL2HMM v{_version} - RFL to HMM Code Converter\n" +
                "Written by Hyper\n"
            );

            if (args.Length > 4 || args.Length < 3)
            {
                Console.Write
                (
                    "Usage;\n" +
                    "- RFL2HMM.exe templateName \"original.rfl\" \"modified.rfl\"\n" +
                    "- RFL2HMM.exe templateName \"original.rfl\" \"modified.rfl\" \"output.hmm\"\n\n" +
                    "" +
                    "Information;\n" +
                    "- For the template name, browse the \"Templates\" folder provided and use the file name.\n" +
                    "- The original RFL file must use the original file name from the game data, this is used to load it from the HMM code.\n\n" +
                    "" +
                    "Press any key to exit..."
                );

                Console.ReadKey();

                return;
            }

            string templateName = args[0];
            string originalFilePath = args[1];
            string modifiedFilePath = args[2];

            if (!File.Exists(Path.Combine("Templates", $"{templateName}.cs")))
            {
                Console.WriteLine($"Failed to load template: \"{templateName}.cs\"");
                return;
            }

            if (!File.Exists(originalFilePath))
            {
                Console.WriteLine($"Failed to locate file: \"{originalFilePath}\"");
                return;
            }

            if (!File.Exists(modifiedFilePath))
            {
                Console.WriteLine($"Failed to locate file: \"{modifiedFilePath}\"");
                return;
            }

            string outputFilePath = Path.Combine(Path.GetDirectoryName(modifiedFilePath), $"{Path.GetFileNameWithoutExtension(modifiedFilePath)}.hmm");

            if (args.Length > 3)
                outputFilePath = args[3];

            Console.Write("Comparing reflection data...");

            var diffResults = DiffVmProvider.Run(originalFilePath, modifiedFilePath, templateName);

            if (diffResults == null)
            {
                Console.Write(" Failed.\n\nError: null comparison result.");
                return;
            }

            Console.WriteLine(" Success.\n");

            if (diffResults.Count == 0)
            {
                Console.Write("No differences found.");
                return;
            }

            _output.AppendLine
            (
                $"Code \"{templateName}-{DateTime.Now:hhmmssddMMyyyy}\" by \"{Environment.UserName}\"\n" +
                "//\n" +
                "\t#include \"ReflectionHelpers\" noemit\n\n" +
                $"\t#lib \"{templateName}\"\n" +
                "//\n" +
                "{\n" +
                $"\tvar {templateName}Info = Reflection.GetDataInfo<{templateName}.Root>(\"{Path.GetFileNameWithoutExtension(originalFilePath)}\");\n\n" +
                "" +
                $"\tif ({templateName}Info.pData == null)\n" +
                "\t\treturn;\n" +
                ""
            );

            foreach (var diff in diffResults)
            {
                string hierarchy = diff.Key;
                object value = diff.Value;

                if (hierarchy.Contains(_arrayDelimiter))
                {
                    var arrIndices = GetSubstringIndices(hierarchy, _arrayDelimiter);

                    foreach (int i in arrIndices)
                    {
                        int nextHierarchyIndex = hierarchy.IndexOf(".", i);

                        if (nextHierarchyIndex == -1)
                            nextHierarchyIndex = hierarchy.Length;

                        hierarchy = hierarchy.Insert(nextHierarchyIndex, "]");
                    }

                    hierarchy = hierarchy.Replace(_arrayDelimiter, "[");
                }

                _output.Append($"\tRFL_SET_PARAM({templateName}Info, {hierarchy}, ");

                if (value is Enum enumValue)
                {
                    _output.Append($"{templateName}.{enumValue.GetType().Name}.{enumValue}");
                }
                else
                {
                    if (value.GetType() == typeof(bool))
                    {
                        _output.Append(value.ToString().ToLowerInvariant());
                    }
                    else
                    {
                        _output.Append(value);
                    }

                    if (value.GetType() == typeof(float))
                    {
                        if (value.ToString().Contains("."))
                        {
                            _output.Append("f");
                        }
                        else
                        {
                            _output.Append(".0f");
                        }
                    }
                }

                _output.Append(");\n");
            }

            _output.AppendLine("}");

            try
            {
                if (templateName != "SonicParameters")
                {
                    Console.WriteLine("Writing external template to code file...\n");

                    string libraryFilePath = Path.Combine("Libraries", $"{templateName}.hmm");

                    if (File.Exists(libraryFilePath))
                    {
                        string libraryCode = File.ReadAllText(libraryFilePath);

                        // Rename root struct since it'll share the name with the library class.
                        libraryCode = libraryCode.Replace($"public struct {templateName}", "public struct Root");

                        _output.AppendLine($"\n{libraryCode}");
                    }
                    else
                    {
                        Console.WriteLine($"Failed to load library: \"{templateName}.hmm\"\n");
                        Console.WriteLine("WARNING: writing code file without external template!\n");
                    }
                }

                File.WriteAllText(outputFilePath, _output.ToString());

                Console.Write($"Code file written to: \"{outputFilePath}\"");
            }
            catch (Exception ex)
            {
                Console.Write(ex);
            }
        }

        static List<int> GetSubstringIndices(string str, string substr)
        {
            var indices = new List<int>();

            int i = 0;
            while ((i = str.IndexOf(substr, i)) != -1)
            {
                indices.Add(i);
                i += substr.Length;
            }

            return indices;
        }
    }
}
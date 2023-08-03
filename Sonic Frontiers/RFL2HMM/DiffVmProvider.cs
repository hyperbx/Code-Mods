using System.Reflection;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis;

namespace RFL2HMM
{
    class DiffVmProvider
    {
        private static string _scriptTemplate(string originalFilePath, string modifiedFilePath, string templateName) =>
        $$"""
            using System;
            using System.Collections.Generic;
            using System.IO;
            using System.Reflection;

            {{File.ReadAllText($@"Templates\{templateName}.cs")}}

            namespace RFL2HMM
            {
                public class DiffVm
                {
                    private static Dictionary<string, object> _diffResults = new();

                    public static Dictionary<string, object> Main()
                    {
                        byte[] originalFileData = File.ReadAllBytes("{{originalFilePath}}");
                        byte[] modifiedFileData = File.ReadAllBytes("{{modifiedFilePath}}");

                        unsafe
                        {
                            {{templateName}}Class.{{templateName}}* pOriginal{{templateName}};

                            fixed (byte* pOriginalFileData = originalFileData)
                                pOriginal{{templateName}} = ({{templateName}}Class.{{templateName}}*)(pOriginalFileData + 0x40);

                            {{templateName}}Class.{{templateName}}* pModified{{templateName}};

                            fixed (byte* pModifiedFileData = modifiedFileData)
                                pModified{{templateName}} = ({{templateName}}Class.{{templateName}}*)(pModifiedFileData + 0x40);

                            DiffStructs(*pOriginal{{templateName}}, *pModified{{templateName}}, string.Empty, "{{templateName}}");
                        }

                        return _diffResults;
                    }

                    static void DiffStructs(object instance1, object instance2, string currentStructName, string hierarchy)
                    {
                        Type type1 = instance1.GetType();
                        Type type2 = instance2.GetType();

                        foreach (FieldInfo field in type1.GetFields(BindingFlags.Instance | BindingFlags.Public))
                        {
                            object value1 = field.GetValue(instance1);
                            object value2 = field.GetValue(instance2);
                            string fieldName = field.Name;

                            // Remove first underscore to redirect to original name.
                            if (fieldName.StartsWith("_"))
                                fieldName = fieldName.Substring(1);

                            // Field is a struct.
                            if (field.FieldType.IsValueType && !field.FieldType.IsPrimitive && !field.FieldType.IsEnum)
                            {
                                string newHierarchy = string.Empty;

                                if (field.Name != currentStructName)
                                    newHierarchy = hierarchy + $".{fieldName}";

                                DiffStructs(value1, value2, fieldName, newHierarchy);
                            }
                            else
                            {
                                if (!Equals(value1, value2))
                                {
                                    int firstHierarchyIndex = hierarchy.IndexOf(".") + 1;
                                    string hierarchyWithoutRoot = hierarchy.Substring(firstHierarchyIndex, hierarchy.Length - firstHierarchyIndex);

                                    _diffResults.Add($"{hierarchyWithoutRoot}.{fieldName}", value2);
                                }
                            }
                        }
                    }
                }
            }
        """;

        public static Dictionary<string, object> Run(string originalFilePath, string modifiedFilePath, string templateName)
        {
            var options = new CSharpCompilationOptions(OutputKind.DynamicallyLinkedLibrary, allowUnsafe: true);
            var syntaxTree = CSharpSyntaxTree.ParseText(_scriptTemplate(originalFilePath, modifiedFilePath, templateName));
            var references = new MetadataReference[] { MetadataReference.CreateFromFile(typeof(object).Assembly.Location) };
            var compilation = CSharpCompilation.Create("DynamicScript", new[] { syntaxTree }, references, options);

            using (var ms = new MemoryStream())
            {
                var result = compilation.Emit(ms);

                if (result.Success)
                {
                    ms.Seek(0, SeekOrigin.Begin);

                    var assembly = Assembly.Load(ms.ToArray());
                    var scriptType = assembly.GetType("RFL2HMM.DiffVm");
                    var method = scriptType.GetMethod("Main");
                    object instance = null;

                    if (!method.IsStatic)
                        instance = Activator.CreateInstance(scriptType);

                    return (Dictionary<string, object>)method.Invoke(instance, null);
                }
                else
                {
                    foreach (var diagnostic in result.Diagnostics)
                        Console.WriteLine(diagnostic.ToString());
                }
            }

            return null;
        }
    }
}

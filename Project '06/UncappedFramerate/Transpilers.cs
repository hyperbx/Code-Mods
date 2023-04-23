using HarmonyLib;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using UnityEngine;

namespace UncappedFramerate
{
    public class Transpilers
    {
        public static IEnumerable<CodeInstruction> ReplaceFixedDeltaTime(IEnumerable<CodeInstruction> instructions, float value)
        {
            var newInstructions = new List<CodeInstruction>();

            foreach (var instruction in instructions)
            {
                if (instruction.Calls(AccessTools.DeclaredMethod(typeof(Time), "get_fixedDeltaTime")))
                {
                    var ldfld = new CodeInstruction(instruction)
                    {
                        opcode = OpCodes.Ldc_R4,
                        operand = value
                    };

                    newInstructions.Add(ldfld);

                    continue;
                }

                newInstructions.Add(instruction);
            }

            return newInstructions.AsEnumerable();
        }
    }
}

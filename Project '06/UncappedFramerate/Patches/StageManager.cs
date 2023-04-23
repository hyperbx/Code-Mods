using HarmonyLib;
using UnityEngine;

namespace UncappedFramerate.Patches
{
    class StageManager
    {
        [HarmonyPatch(typeof(global::StageManager), "Awake")]
        class Awake
        {
            public static void Postfix()
            {
                Application.targetFrameRate = Screen.currentResolution.refreshRate;
            }
        }
    }
}

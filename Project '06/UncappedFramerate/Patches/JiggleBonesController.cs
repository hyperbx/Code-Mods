using HarmonyLib;
using UnityEngine;

namespace UncappedFramerate.Patches
{
    class JiggleBonesController
    {
        [HarmonyPatch(typeof(global::JiggleBonesController), "Start")]
        class Start
        {
            public static void Postfix(global::JiggleBonesController __instance)
            {
                if (global::Singleton<global::Settings>.Instance.settings.JiggleBones != 0)
                {
                    // Update dynamic bones at target framerate to prevent glitching.
                    foreach (var bone in __instance.DynamicBones)
                        bone.m_UpdateRate = Application.targetFrameRate;
                }
            }
        }
    }
}

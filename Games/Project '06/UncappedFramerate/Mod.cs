using MelonLoader;
using UncappedFramerate.Patches.Scenes;
using UnityEngine;

namespace UncappedFramerate
{
    public class Mod : MelonMod
    {
        public static float UnpatchedFixedDeltaTime = 0.01666667f;

        public override void OnInitializeMelon()
        {
            Singleton<Settings>.Instance.settings.VSync = 1;
        }

        public override void OnUpdate()
        {
            UnpatchedFixedDeltaTime = 1.0f / Screen.currentResolution.refreshRate;

            if (Singleton<GameManager>.Instance.GameState != GameManager.State.Paused)
                Time.fixedDeltaTime = Time.smoothDeltaTime;
        }

        public override void OnSceneWasLoaded(int buildIndex, string sceneName)
        {
            base.OnSceneWasLoaded(buildIndex, sceneName);

            Debug.Log($"Applying frame rate patches for {sceneName}...");

            switch (sceneName)
            {
                case "wvo_a_sn":
                    WaveOceanA.FixWhaleChase();
                    break;

                case "csc_b_sn":
                case "csc_b_sd":
                    CrisisCityB.FixRooftopRoundabout();
                    break;

                case "csc_b_sv":
                    CrisisCityB.FixMisalignedSpring();
                    break;
            }
        }

        public override void OnDeinitializeMelon()
        {
            Time.fixedDeltaTime = 1.0f / 60.0f;

            HarmonyInstance.UnpatchSelf();

            Debug.Log("Uncapped Framerate is unloaded.");
        }
    }
}

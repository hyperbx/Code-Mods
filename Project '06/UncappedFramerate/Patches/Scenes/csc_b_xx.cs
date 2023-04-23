using UnityEngine;

namespace UncappedFramerate.Patches.Scenes
{
    public class csc_b_xx
    {
        static void FixRooftopRoundabout()
        {
            var jumpPanels = Resources.FindObjectsOfTypeAll<JumpPanel>();

            /* Unity is fucking stupid and doesn't return
               inactive objects through GameObject.Find(),
               so we have to do this garbage. */
            foreach (var jumpPanel in jumpPanels)
            {
                if (jumpPanel.name == "jumppanel01")
                {
                    // Move target position backwards so we land on the dash panel.
                    jumpPanel.TargetPosition = new Vector3(-122.4899f, 50.0f, -260.969f);
                }
            }
        }

        public static void ApplyPatches()
        {
            FixRooftopRoundabout();
        }
    }
}

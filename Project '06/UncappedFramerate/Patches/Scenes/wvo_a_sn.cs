using UnityEngine;

namespace UncappedFramerate.Patches.Scenes
{
    public class wvo_a_sn
    {
        static void FixWhaleChase()
        {
            var dashPanels = Resources.FindObjectsOfTypeAll<DashPanel>();

            /* Unity is fucking stupid and doesn't return
               inactive objects through GameObject.Find(),
               so we have to do this garbage. */
            foreach (var dashPanel in dashPanels)
            {
                if (dashPanel.name == "dashpanel22")
                {
                    // Move dash panel forwards so Sonic lands on it from the jump panel.
                    dashPanel.transform.position = new Vector3(338.0772f, 4.838f, -921.7548f);
                }
            }
        }

        public static void ApplyPatches()
        {
            FixWhaleChase();
        }
    }
}

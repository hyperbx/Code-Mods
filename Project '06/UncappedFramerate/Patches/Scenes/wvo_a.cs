using UnityEngine;

namespace UncappedFramerate.Patches.Scenes
{
    public class wvo_a
    {
        public static void SN_FixWhaleChase()
        {
            var dashPanels = Resources.FindObjectsOfTypeAll<global::DashPanel>();

            foreach (var dashPanel in dashPanels)
            {
                if (dashPanel.name == "dashpanel22")
                {
                    // Move dash panel forwards so Sonic lands on it from the jump panel.
                    dashPanel.transform.position = new Vector3(338.0772f, 4.838f, -921.7548f);
                }
            }
        }
    }
}

using UnityEngine;

namespace UncappedFramerate.Patches.Scenes
{
    public class WaveOceanA
    {
        public static void FixWhaleChase()
        {
            var dashPanels = Resources.FindObjectsOfTypeAll<DashPanel>();

            foreach (var dashPanel in dashPanels)
            {
                if (dashPanel.name != "dashpanel22")
                    continue;

                // Move dash panel forwards so Sonic lands on it from the jump panel.
                dashPanel.transform.position = new Vector3(338.0772f, 4.838f, -921.7548f);

                break;
            }
        }
    }
}

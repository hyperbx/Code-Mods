using UnityEngine;

namespace UncappedFramerate.Patches.Scenes
{
    public class CrisisCityB
    {
        public static void FixRooftopRoundabout()
        {
            var jumpPanels = Resources.FindObjectsOfTypeAll<JumpPanel>();

            foreach (var jumpPanel in jumpPanels)
            {
                if (jumpPanel.name != "jumppanel01")
                    continue;

                // Move target position backwards so we land on the dash panel.
                jumpPanel.TargetPosition = new Vector3(-122.4899f, 50.0f, -260.969f);

                break;
            }
        }

        public static void FixMisalignedSpring()
        {
            var springs = Resources.FindObjectsOfTypeAll<Spring>();

            foreach (var spring in springs)
            {
                if (spring.name != "spring58")
                    continue;

                var springLeft = Object.Instantiate(spring);
                {
                    springLeft.gameObject.SetActive(true);
                    springLeft.transform.position = new Vector3(-46.9563f, 93.0951f, -314.0689f);
                }

                var springRight = Object.Instantiate(spring);
                {
                    springRight.gameObject.SetActive(true);
                    springRight.transform.position = new Vector3(-43.4962f, 93.0951f, -316.349f);
                }

                break;
            }
        }
    }
}

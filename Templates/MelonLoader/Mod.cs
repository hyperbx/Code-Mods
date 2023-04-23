using MelonLoader;

namespace $safeprojectname$
{
    public class Mod : MelonMod
    {
        /// <summary>
        /// This function is called once the Unity game has opened after MelonLoader's initialisation.
        /// </summary>
        public override void OnApplicationStart()
        {

        }
		
        /// <summary>
        /// This function is called when this mod is unregistered by another mod.
        /// Use this function to unload any additional assets and dependencies that are being used.
        /// </summary>
		public override void OnDeinitializeMelon()
		{
			
		}
    }
}

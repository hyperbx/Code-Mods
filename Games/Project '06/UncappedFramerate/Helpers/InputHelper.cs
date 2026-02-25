using Rewired;

namespace UncappedFramerate.Helpers
{
    public class InputHelper
    {
        public const string kRewiredLeftBumper = "Left Bumper";
        public const string kRewiredLeftStickX = "Left Stick X";
        public const string kRewiredLeftStickY = "Left Stick Y";
        public const string kRewiredRightBumper = "Right Bumper";
        public const string kRewiredRightStickX = "Right Stick X";
        public const string kRewiredRightStickY = "Right Stick Y";

        public static Player GetRewiredPlayer(int in_index = 0)
        {
            return ReInput.players.GetPlayer(in_index);
        }
    }
}

using Rewired;

namespace UncappedFramerate.Helpers
{
    public class InputHelper
    {
        public const string REWIRED_LB   = "Left Bumper";
        public const string REWIRED_LS_X = "Left Stick X";
        public const string REWIRED_LS_Y = "Left Stick Y";
        public const string REWIRED_RB   = "Right Bumper";
        public const string REWIRED_RS_X = "Right Stick X";
        public const string REWIRED_RS_Y = "Right Stick Y";

        public static Player GetRewiredPlayer(int index = 0)
            => ReInput.players.GetPlayer(index);
    }
}

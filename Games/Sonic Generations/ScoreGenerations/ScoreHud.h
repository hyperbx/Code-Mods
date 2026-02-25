#pragma once

namespace ScoreGenerations
{
    class ScoreHud
    {
    public:
        /// <summary>
        /// Determines if the score counter is visible.
        /// </summary>
        inline static bool IsVisible{ true };

        /// <summary>
        /// Determines if the current stage is a mission.
        /// </summary>
        inline static bool IsMission{};

        static bool IsProhibitedStage();
        static bool IsCasinoNightZone();
        static void Install();
    };
}

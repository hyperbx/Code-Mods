#pragma once

#include "API/ScoreGenerationsTypes.h"

namespace ScoreGenerations
{
    class TableProvider
    {
        inline static ScoreTable m_ScoreTable{};
        inline static RankTableMap_t m_RankTables{};
        inline static BonusTable m_BonusTable{};
        inline static MultiplierTable m_MultiplierTable{};
        inline static TimerTable m_TimerTable{};

    public:
        static void Read(cmf::sys::cfg::Ini& in_rIni);

        static ScoreTable ReadScoreTable(cmf::sys::cfg::Ini& in_rIni);
        static RankTableMap_t ReadRankTables(cmf::sys::cfg::Ini& in_rIni);
        static BonusTable ReadBonusTable(cmf::sys::cfg::Ini& in_rIni);
        static MultiplierTable ReadMultiplierTable(cmf::sys::cfg::Ini& in_rIni);
        static TimerTable ReadTimerTable(cmf::sys::cfg::Ini& in_rIni);

        static ScoreTable& GetScoreTable();
        static RankTableMap_t& GetRankTables();
        static BonusTable& GetBonusTable();
        static MultiplierTable& GetMultiplierTable();
        static TimerTable& GetTimerTable();
    };
}

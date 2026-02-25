#include "TableProvider.h"

#define INI_V1_BACKCOMPAT_GET(TYPE, SECTION, KEY, DEFAULT_VALUE) in_rIni.Get<TYPE>(SECTION, KEY, in_rIni.Get<TYPE>(SECTION, g_v1KeyMap.at(KEY), DEFAULT_VALUE))

using namespace ScoreGenerations;

static const std::unordered_map<std::string, std::string> g_v1KeyMap =
{
    { "MinSeconds", "minSeconds" },
    { "MaxSeconds", "maxSeconds" },
    { "HomingChainBonus", "homingChainBonus" },
    { "HomingChainBonusLimit", "homingChainBonusLimit" },
    { "SlamBonus", "slamBonus" },
    { "SlamBonusLimit", "slamBonusLimit" },
    { "TrickBonusLimit", "trickBonusLimit" },
    { "TimeBonusExpression", "timeBonusAlgorithm" },
    { "RingBonusExpression", "ringBonusAlgorithm" },
    { "SpeedBonusExpression", "speedBonusAlgorithm" },
    { "UserExpression", "userAlgorithm" },
    { "SpeedBonusMultiplier", "speedBonusMultiplier" },
    { "HomingChainMultiplier", "homingChainMultiplier" },
    { "SlamMultiplier", "slamMultiplier" },
    { "TrickMultiplier", "trickMultiplier" },
    { "SuperSonicTimer", "superSonicTimer" },
    { "SlamTimer", "slamTimer" }
};

void TableProvider::Read(cmf::sys::cfg::Ini& in_rIni)
{
    m_ScoreTable = ReadScoreTable(in_rIni);
    m_RankTables = ReadRankTables(in_rIni);
    m_BonusTable = ReadBonusTable(in_rIni);
    m_MultiplierTable = ReadMultiplierTable(in_rIni);
    m_TimerTable = ReadTimerTable(in_rIni);
}

ScoreTable TableProvider::ReadScoreTable(cmf::sys::cfg::Ini& in_rIni)
{
    ScoreTable result{};

    result.Ring        = in_rIni.Get<int>("Score", "Ring", m_ScoreTable.Ring);
    result.Enemy       = in_rIni.Get<int>("Score", "Enemy", m_ScoreTable.Enemy);
    result.Physics     = in_rIni.Get<int>("Score", "Physics", m_ScoreTable.Physics);
    result.PointMarker = in_rIni.Get<int>("Score", "PointMarker", m_ScoreTable.PointMarker);
    result.RedRing     = in_rIni.Get<int>("Score", "RedRing", m_ScoreTable.RedRing);
    result.RainbowRing = in_rIni.Get<int>("Score", "RainbowRing", m_ScoreTable.RainbowRing);
    result.ItemBox     = in_rIni.Get<int>("Score", "ItemBox", m_ScoreTable.ItemBox);
    result.SuperRing   = in_rIni.Get<int>("Score", "SuperRing", m_ScoreTable.SuperRing);
    result.TrickFinish = in_rIni.Get<int>("Score", "TrickFinish", m_ScoreTable.TrickFinish);
    result.Trick       = in_rIni.Get<int>("Score", "Trick", m_ScoreTable.Trick);
    result.Life        = in_rIni.Get<int>("Score", "Life", m_ScoreTable.Life);
    result.DashRing    = in_rIni.Get<int>("Score", "DashRing", m_ScoreTable.DashRing);
    result.QuickStep   = in_rIni.Get<int>("Score", "QuickStep", m_ScoreTable.QuickStep);
    result.Drift       = in_rIni.Get<int>("Score", "Drift", m_ScoreTable.Drift);
    result.Balloon     = in_rIni.Get<int>("Score", "Balloon", m_ScoreTable.Balloon);
    result.Super       = in_rIni.Get<int>("Score", "Super", m_ScoreTable.Super);
    result.BoardTrick  = in_rIni.Get<int>("Score", "BoardTrick", m_ScoreTable.BoardTrick);

    LOGFN_UTILITY("Ring -------- : {}", result.Ring);
    LOGFN_UTILITY("Enemy ------- : {}", result.Enemy);
    LOGFN_UTILITY("Physics ----- : {}", result.Physics);
    LOGFN_UTILITY("PointMarker - : {}", result.PointMarker);
    LOGFN_UTILITY("RedRing ----- : {}", result.RedRing);
    LOGFN_UTILITY("RainbowRing - : {}", result.RainbowRing);
    LOGFN_UTILITY("ItemBox ----- : {}", result.ItemBox);
    LOGFN_UTILITY("SuperRing --- : {}", result.SuperRing);
    LOGFN_UTILITY("TrickFinish - : {}", result.TrickFinish);
    LOGFN_UTILITY("Trick ------- : {}", result.Trick);
    LOGFN_UTILITY("Life -------- : {}", result.Life);
    LOGFN_UTILITY("DashRing ---- : {}", result.DashRing);
    LOGFN_UTILITY("QuickStep --- : {}", result.QuickStep);
    LOGFN_UTILITY("Drift ------- : {}", result.Drift);
    LOGFN_UTILITY("Balloon ----- : {}", result.Balloon);
    LOGFN_UTILITY("Super ------- : {}", result.Balloon);
    LOGFN_UTILITY("BoardTrick -- : {}", result.BoardTrick);

    return result;
}

RankTableMap_t TableProvider::ReadRankTables(cmf::sys::cfg::Ini& in_rIni)
{
    for (const auto& rSection : in_rIni.GetSections())
    {
        if (rSection[0] != '#')
            continue;

        RankTable rankTable{};

        rankTable.MinSeconds = INI_V1_BACKCOMPAT_GET(int, rSection, "MinSeconds", 0);
        rankTable.MaxSeconds = INI_V1_BACKCOMPAT_GET(int, rSection, "MaxSeconds", 0);
        rankTable.S          = in_rIni.Get<int>(rSection, "S", -1);
        rankTable.A          = in_rIni.Get<int>(rSection, "A", -1);
        rankTable.B          = in_rIni.Get<int>(rSection, "B", -1);
        rankTable.C          = in_rIni.Get<int>(rSection, "C", -1);
        rankTable.D          = in_rIni.Get<int>(rSection, "D", -1);

        LOGFN_UTILITY("MinSeconds - : {}", rankTable.MinSeconds);
        LOGFN_UTILITY("MaxSeconds - : {}", rankTable.MaxSeconds);
        LOGFN_UTILITY("S ---------- : {}", rankTable.S);
        LOGFN_UTILITY("A ---------- : {}", rankTable.A);
        LOGFN_UTILITY("B ---------- : {}", rankTable.B);
        LOGFN_UTILITY("C ---------- : {}", rankTable.C);
        LOGFN_UTILITY("D ---------- : {}", rankTable.D);

        auto stageID = rSection.substr(1);

        m_RankTables[stageID] = rankTable;
    }

    return m_RankTables;
}

BonusTable TableProvider::ReadBonusTable(cmf::sys::cfg::Ini& in_rIni)
{
    BonusTable bonusTable{};

    bonusTable.HomingChainBonus      = INI_V1_BACKCOMPAT_GET(int, "GameplayBonus", "HomingChainBonus", m_BonusTable.HomingChainBonus);
    bonusTable.HomingChainBonusLimit = INI_V1_BACKCOMPAT_GET(int, "GameplayBonus", "HomingChainBonusLimit", m_BonusTable.HomingChainBonusLimit);
    bonusTable.SlamBonus             = INI_V1_BACKCOMPAT_GET(int, "GameplayBonus", "SlamBonus", m_BonusTable.SlamBonus);
    bonusTable.SlamBonusLimit        = INI_V1_BACKCOMPAT_GET(int, "GameplayBonus", "SlamBonusLimit", m_BonusTable.SlamBonusLimit);
    bonusTable.TrickBonusLimit       = INI_V1_BACKCOMPAT_GET(int, "GameplayBonus", "TrickBonusLimit", m_BonusTable.TrickBonusLimit);
    bonusTable.pTimeBonusExpression  = INI_V1_BACKCOMPAT_GET(const char*, "ResultBonus", "TimeBonusExpression", m_BonusTable.pTimeBonusExpression);
    bonusTable.pRingBonusExpression  = INI_V1_BACKCOMPAT_GET(const char*, "ResultBonus", "RingBonusExpression", m_BonusTable.pRingBonusExpression);
    bonusTable.pSpeedBonusExpression = INI_V1_BACKCOMPAT_GET(const char*, "ResultBonus", "SpeedBonusExpression", m_BonusTable.pSpeedBonusExpression);
    bonusTable.pUserExpression       = INI_V1_BACKCOMPAT_GET(const char*, "ResultBonus", "UserExpression", m_BonusTable.pUserExpression);

    LOGFN_UTILITY("HomingChainBonus ------ : {}", bonusTable.HomingChainBonus);
    LOGFN_UTILITY("HomingChainBonusLimit - : {}", bonusTable.HomingChainBonusLimit);
    LOGFN_UTILITY("SlamBonus ------------- : {}", bonusTable.SlamBonus);
    LOGFN_UTILITY("SlamBonusLimit -------- : {}", bonusTable.SlamBonusLimit);
    LOGFN_UTILITY("TrickBonusLimit ------- : {}", bonusTable.TrickBonusLimit);
    LOGFN_UTILITY("TimeBonusExpression --- : {}", bonusTable.pTimeBonusExpression);
    LOGFN_UTILITY("RingBonusExpression --- : {}", bonusTable.pRingBonusExpression);
    LOGFN_UTILITY("SpeedBonusExpression -- : {}", bonusTable.pSpeedBonusExpression);
    LOGFN_UTILITY("UserExpression -------- : {}", bonusTable.pUserExpression);

    return bonusTable;
}

MultiplierTable TableProvider::ReadMultiplierTable(cmf::sys::cfg::Ini& in_rIni)
{
    MultiplierTable multiplierTable{};
    
    multiplierTable.SpeedBonusMultiplier  = INI_V1_BACKCOMPAT_GET(float, "Multiplier", "SpeedBonusMultiplier", m_MultiplierTable.SpeedBonusMultiplier);
    multiplierTable.HomingChainMultiplier = INI_V1_BACKCOMPAT_GET(float, "Multiplier", "HomingChainMultiplier", m_MultiplierTable.HomingChainMultiplier);
    multiplierTable.SlamMultiplier        = INI_V1_BACKCOMPAT_GET(float, "Multiplier", "SlamMultiplier", m_MultiplierTable.SlamMultiplier);
    multiplierTable.TrickMultiplier       = INI_V1_BACKCOMPAT_GET(float, "Multiplier", "TrickMultiplier", m_MultiplierTable.TrickMultiplier);

    LOGFN_UTILITY("SpeedBonusMultiplier -- : {}", multiplierTable.SpeedBonusMultiplier);
    LOGFN_UTILITY("HomingChainMultiplier - : {}", multiplierTable.HomingChainMultiplier);
    LOGFN_UTILITY("SlamMultiplier -------- : {}", multiplierTable.SlamMultiplier);
    LOGFN_UTILITY("TrickMultiplier ------- : {}", multiplierTable.TrickMultiplier);

    return multiplierTable;
}

TimerTable TableProvider::ReadTimerTable(cmf::sys::cfg::Ini& in_rIni)
{
    TimerTable timerTable;

    timerTable.SuperSonicTimer = INI_V1_BACKCOMPAT_GET(float, "Timer", "SuperSonicTimer", m_TimerTable.SuperSonicTimer);
    timerTable.SlamTimer       = INI_V1_BACKCOMPAT_GET(float, "Timer", "SlamTimer", m_TimerTable.SlamTimer);

    LOGFN_UTILITY("SuperSonicTimer - : {}", timerTable.SuperSonicTimer);
    LOGFN_UTILITY("SlamTimer ------- : {}", timerTable.SlamTimer);

    return timerTable;
}

ScoreTable& TableProvider::GetScoreTable()
{
    return TableProvider::m_ScoreTable;
}

RankTableMap_t& TableProvider::GetRankTables()
{
    return TableProvider::m_RankTables;
}

BonusTable& TableProvider::GetBonusTable()
{
    return TableProvider::m_BonusTable;
}

MultiplierTable& TableProvider::GetMultiplierTable()
{
    return TableProvider::m_MultiplierTable;
}

TimerTable& TableProvider::GetTimerTable()
{
    return TableProvider::m_TimerTable;
}

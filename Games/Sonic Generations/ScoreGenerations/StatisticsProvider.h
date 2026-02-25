#pragma once

#include "API/ScoreGenerationsTypes.h"

namespace ScoreGenerations
{
    class StatisticsProvider
    {
        inline static Statistics m_Statistics{};

    public:
        static Statistics& GetStatistics();
        static void Install();
    };
}

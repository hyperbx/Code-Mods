#pragma once

#include <source_location>

#ifndef LOG_SOURCE
#define LOG_SOURCE "*"
#endif

#define LOG_IMPL(TYPE, CALLER_NAME, STR)       CMF::System::Logger::Log(STR, CMF::System::Logger::LogType::TYPE, CALLER_NAME)
#define LOGF_IMPL(TYPE, CALLER_NAME, STR, ...) CMF::System::Logger::Log(std::format(STR, __VA_ARGS__), CMF::System::Logger::LogType::TYPE, CALLER_NAME)

// Function-specific logging.

#define LOG(STR)               LOG_IMPL(None, __func__, STR)
#define LOG_WARNING(STR)       LOG_IMPL(Warning, __func__, STR)
#define LOG_ERROR(STR)         LOG_IMPL(Error, __func__, STR)

#if _DEBUG
#define LOG_UTILITY(STR)       LOG_IMPL(Utility, __func__, STR)
#else
#define LOG_UTILITY(STR)
#endif

#define LOGF(STR, ...)         LOGF_IMPL(None, __func__, STR, __VA_ARGS__)
#define LOGF_WARNING(STR, ...) LOGF_IMPL(Warning, __func__, STR, __VA_ARGS__)
#define LOGF_ERROR(STR, ...)   LOGF_IMPL(Error, __func__, STR, __VA_ARGS__)

#if _DEBUG
#define LOGF_UTILITY(STR, ...) LOGF_IMPL(Utility, __func__, STR, __VA_ARGS__)
#else
#define LOGF_UTILITY(STR, ...)
#endif

// Non-function-specific logging.

#define LOGN(STR)               LOG_IMPL(None, LOG_SOURCE, STR)
#define LOGN_WARNING(STR)       LOG_IMPL(Warning, LOG_SOURCE, STR)
#define LOGN_ERROR(STR)         LOG_IMPL(Error, LOG_SOURCE, STR)

#if _DEBUG
#define LOGN_UTILITY(STR)       LOG_IMPL(Utility, LOG_SOURCE, STR)
#else
#define LOGN_UTILITY(STR)
#endif

#define LOGFN(STR, ...)         LOGF_IMPL(None, LOG_SOURCE, STR, __VA_ARGS__)
#define LOGFN_WARNING(STR, ...) LOGF_IMPL(Warning, LOG_SOURCE, STR, __VA_ARGS__)
#define LOGFN_ERROR(STR, ...)   LOGF_IMPL(Error, LOG_SOURCE, STR, __VA_ARGS__)

#if _DEBUG
#define LOGFN_UTILITY(STR, ...) LOGF_IMPL(Utility, LOG_SOURCE, STR, __VA_ARGS__)
#else
#define LOGFN_UTILITY(STR, ...)
#endif

namespace CMF::System::Logger
{
    enum class LogType
    {
        None,
        Utility,
        Warning,
        Error
    };

    static void Init();
    static void Log(const std::string_view in_str, LogType in_logType, const char* in_callerName = nullptr);
}

#ifdef WIN32
#include "LoggerWin32.inl"
#endif
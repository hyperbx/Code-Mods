#include <print>
#include <Windows.h>

#define FOREGROUND_WHITE  (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)

namespace CMF::System::Logger
{
    inline static HANDLE g_hStdOut{};

    inline void Init(bool in_openConsole)
    {
        g_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        
        if (!in_openConsole)
            return;

        AllocConsole();
        freopen("CONOUT$", "w", stdout);
    }

    inline void Log(const std::string_view in_str, LogType in_logType, const char* in_callerName)
    {
        switch (in_logType)
        {
            case LogType::Utility:
                SetConsoleTextAttribute(g_hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;

            case LogType::Warning:
                SetConsoleTextAttribute(g_hStdOut, FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                break;

            case LogType::Error:
                SetConsoleTextAttribute(g_hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;

            default:
                SetConsoleTextAttribute(g_hStdOut, FOREGROUND_WHITE);
                break;
        }

        if (in_callerName)
        {
            std::println("[{}] {}", in_callerName, in_str);
        }
        else
        {
            std::println("{}", in_str);
        }

        SetConsoleTextAttribute(g_hStdOut, FOREGROUND_WHITE);
    }
}
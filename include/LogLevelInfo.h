#pragma once

#include <array>
#include <string_view>
#include "ConsoleColor.h"

namespace LogLevelInfo
{
    #define LOG_LEVEL_INFO_SIZE 4

    enum class LOG_LEVEL {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
    };

    struct LogLevelInfo {
        std::string info;
        ConsoleColor::ConsoleColor color;
    };

    const std::array<LogLevelInfo, LOG_LEVEL_INFO_SIZE> infoArray {
        LogLevelInfo{"DEBUG", ConsoleColor::ConsoleColor::CYAN},
        LogLevelInfo{"INFO", ConsoleColor::ConsoleColor::GREEN},
        LogLevelInfo{"WARNING", ConsoleColor::ConsoleColor::YELLOW},
        LogLevelInfo{"ERROR", ConsoleColor::ConsoleColor::RED},
    };
}


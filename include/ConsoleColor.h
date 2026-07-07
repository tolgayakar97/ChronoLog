#pragma once

#include <iostream>

namespace ConsoleColor
{
    enum class ConsoleColor {
        DEFAULT,
        RED,
        CYAN,
        GREEN,
        YELLOW
    };

    std::string SetConsoleColor(const ConsoleColor& color);
    std::string GetDefaultColor();
}
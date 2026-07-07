#include "iostream"
#include "ConsoleColor.h"

namespace ConsoleColor
{
    std::string SetConsoleColor(const ConsoleColor& color)
    {
        switch(color) {
            case ConsoleColor::RED:
                return "\033[31m";
            case ConsoleColor::CYAN:
                return "\033[36m";
            case ConsoleColor::GREEN:
                return "\033[32m";
            case ConsoleColor::YELLOW:
                return "\033[33m";
            default:
                return "\033[0m";
        }
    }

    std::string GetDefaultColor()
    {
        return "\033[0m";
    }
}
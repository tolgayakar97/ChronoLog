#pragma once

#include <iostream>
#include "LogLevelInfo.h"

namespace Logger
{
    struct LogContext
    {   
        std::string_view desc;
        std::string_view func;
        std::string_view file;
        int line;
        LogLevelInfo::LOG_LEVEL level;
    };
}
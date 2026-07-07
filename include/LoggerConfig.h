#pragma once

#include <iostream>
#include  "LogLevelInfo.h"

namespace Logger
{
    struct LoggerConfig
    {
        bool enableConsole{true};
        bool enableFile{false};
        std::string logFile;
        LogLevelInfo::LOG_LEVEL logLevel{LogLevelInfo::LOG_LEVEL::INFO};
    };
}
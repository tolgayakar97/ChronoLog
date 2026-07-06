#pragma once

#include <iostream>
#include  "LogLevel.h"

struct LoggerConfig
{
    bool enableConsole{false};
    bool enableFile{false};
    std::string logFile;
    LOG_LEVEL logLevel{LOG_LEVEL::INFO};
};
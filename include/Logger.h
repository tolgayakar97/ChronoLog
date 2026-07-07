#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include "LogLevelInfo.h"
#include "LoggerConfig.h"

namespace Logger
{
    #define MS 1000
    #define SETW 3

    class Logger // Singleton class
    {
    private:
        Logger() = default;
        ~Logger();
        Logger(const Logger& other) = delete;
        Logger(Logger&& other) = delete;
        Logger& operator=(const Logger& other) = delete;
        Logger& operator=(Logger&& other) = delete;
        std::string GetTimeStamp() const;
        void WriteToConsole(const std::string& timeStamp, const LogLevelInfo::LogLevelInfo& logLevelInfo,
            const std::string& desc);
        void WriteToFile(const std::string& timeStamp, const LogLevelInfo::LogLevelInfo& logLevelInfo,
            const std::string& desc);
        LogLevelInfo::LogLevelInfo GetLogLevel(const LogLevelInfo::LOG_LEVEL& level) const;
        void Log(const LogLevelInfo::LOG_LEVEL& level, const std::string& text);
        
        LoggerConfig config_;
        std::ofstream logFile_;
        std::mutex mtx_;

    public:
        static Logger& GetInstance();
        void Configure(const LoggerConfig& config);
        void InfoLog(const std::string& text);
        void DebugLog(const std::string& text);
        void WarnLog(const std::string& text);
        void ErrorLog(const std::string& text);
        void OpenLogFile();
        void CloseLogFile();
    };
}


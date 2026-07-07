#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include "LogLevelInfo.h"
#include "LoggerConfig.h"
#include "LogContext.h"

namespace Logger
{
    #define MS 1000
    #define SETW 3
    #define INFO_LOG(desc) Logger::GetInstance().Log({desc, __FUNCTION__, __FILE__, __LINE__, LogLevelInfo::LOG_LEVEL::INFO})
    #define WARNING_LOG(desc) Logger::GetInstance().Log({desc, __FUNCTION__, __FILE__, __LINE__, LogLevelInfo::LOG_LEVEL::WARNING})
    #define ERROR_LOG(desc) Logger::GetInstance().Log({desc, __FUNCTION__, __FILE__, __LINE__, LogLevelInfo::LOG_LEVEL::ERROR})
    #define DEBUG_LOG(desc) Logger::GetInstance().Log({desc, __FUNCTION__, __FILE__, __LINE__, LogLevelInfo::LOG_LEVEL::DEBUG})

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
        void WriteToConsole(const std::string& timeStamp, const LogContext& ctx);
        void WriteToFile(const std::string& timeStamp, const LogContext& ctx);
        LogLevelInfo::LogLevelInfo GetLogLevelInfo(const LogLevelInfo::LOG_LEVEL& level) const;
        
        LoggerConfig config_;
        std::ofstream logFile_;
        std::mutex mtx_;
        
        public:
        static Logger& GetInstance();
        void Configure(const LoggerConfig& config);
        void OpenLogFile();
        void CloseLogFile();
        void Log(const LogContext& ctx);
    };
}
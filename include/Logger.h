#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include "LogLevel.h"
#define MS 1000
#define SETW 3

struct LoggerConfig
{
    bool enableConsole{false};
    bool enableFile{false};
    std::string logFile;
};

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
    void WriteToConsole(const std::string& log);
    void WriteToFile(const std::string& log);
    std::string GetLogLevel(const LOG_LEVEL& level) const;
    void Log(const LOG_LEVEL& level, const std::string& text);
    
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


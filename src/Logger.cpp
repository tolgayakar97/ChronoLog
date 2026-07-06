#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Logger.h"

Logger::~Logger()
{
    CloseLogFile();
}

Logger& Logger::GetInstance()
{
    // Meyers Singleton
    static Logger instance_;
    return instance_;
}

void Logger::Configure(const LoggerConfig& config)
{
    config_ = config;
}

std::string Logger::GetTimeStamp() const
{ 
    auto time = std::chrono::system_clock::now();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        time.time_since_epoch()
    ) % MS;

    auto toTime = std::chrono::system_clock::to_time_t(time);
    auto timeStamp = std::localtime(&toTime);

    std::ostringstream oss;
    oss << std::put_time(timeStamp, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(SETW) <<
        std::setfill('0') << time_ms.count();
    return oss.str();
}

std::string Logger::GetLogLevel(const LOG_LEVEL& level) const
{
    std::string logLevel;

    switch(level)
    {
        case LOG_LEVEL::INFO:
            logLevel = "[INFO]";
            break;
        case LOG_LEVEL::DEBUG:
            logLevel = "[DEBUG]";
            break;
        case LOG_LEVEL::WARNING:
            logLevel = "[WARNING]";
            break;
        case LOG_LEVEL::ERROR:
            logLevel = "[ERROR]";
            break;
    }
    return logLevel;
}

void Logger::Log(const LOG_LEVEL& level, const std::string& text)
{
    std::lock_guard<std::mutex> lg_(mtx_);
    std::string log = GetTimeStamp() + ' ' + GetLogLevel(level) + " : " + text + '\n';

    if (config_.enableConsole) {
        WriteToConsole(log);
    }

    if (config_.enableFile && !config_.logFile.empty()) {
        WriteToFile(log);
    }
}

void Logger::InfoLog(const std::string& text)
{
    Log(LOG_LEVEL::INFO, text);
}

void Logger::DebugLog(const std::string& text)
{
    Log(LOG_LEVEL::DEBUG, text);
}

void Logger::WarnLog(const std::string& text)
{
    Log(LOG_LEVEL::WARNING, text);
}

void Logger::ErrorLog(const std::string& text)
{
    Log(LOG_LEVEL::ERROR, text);
}

void Logger::WriteToConsole(const std::string& log)
{
    std::cout << log;
}

void Logger::OpenLogFile()
{
    if (!logFile_.is_open()) {
        logFile_.open(config_.logFile, std::ios::app);
    }
}

void Logger::CloseLogFile()
{
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

void Logger::WriteToFile(const std::string& log)
{
    if (logFile_.is_open()) {
        logFile_ << log;
    } else {
        OpenLogFile();
        logFile_ << log;
    }
}


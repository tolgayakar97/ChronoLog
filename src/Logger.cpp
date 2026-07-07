#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Logger.h"

namespace Logger
{
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

    LogLevelInfo::LogLevelInfo Logger::GetLogLevel(const LogLevelInfo::LOG_LEVEL& level) const
    {
        // TODO: Return LogLevelInfo as reference to avoid copying, but ensure the lifetime of the returned reference is valid.
        return LogLevelInfo::infoArray[static_cast<std::size_t>(level)];
    }

    void Logger::Log(const LogLevelInfo::LOG_LEVEL& level, const std::string& desc)
    {
        std::lock_guard<std::mutex> lg_(mtx_);

        if (level < config_.logLevel) {
            return;
        }

        auto logLevelInfo = GetLogLevel(level);
        auto timeStamp = GetTimeStamp();

        if (config_.enableConsole) {
            WriteToConsole(timeStamp, logLevelInfo, desc);
        }

        if (config_.enableFile && !config_.logFile.empty()) {
            WriteToFile(timeStamp, logLevelInfo, desc);
        }
    }

    void Logger::InfoLog(const std::string& desc)
    {
        Log(LogLevelInfo::LOG_LEVEL::INFO, desc);
    }

    void Logger::DebugLog(const std::string& desc)
    {
        Log(LogLevelInfo::LOG_LEVEL::DEBUG, desc);
    }

    void Logger::WarnLog(const std::string& desc)
    {
        Log(LogLevelInfo::LOG_LEVEL::WARNING, desc);
    }

    void Logger::ErrorLog(const std::string& desc)
    {
        Log(LogLevelInfo::LOG_LEVEL::ERROR, desc);
    }

    void Logger::OpenLogFile()
    {
        if (!logFile_.is_open()) {
            logFile_.open(config_.logFile, std::ios::out);
        }
    }

    void Logger::CloseLogFile()
    {
        if (logFile_.is_open()) {
            logFile_.close();
        }
    }

    void Logger::WriteToFile(const std::string& timeStamp, const LogLevelInfo::LogLevelInfo& logLevelInfo,
            const std::string& desc)
    {
        auto log = timeStamp + " " + logLevelInfo.info + " : " + desc + '\n';
        if (logFile_.is_open()) {
            logFile_ << log;
        } else {
            OpenLogFile();
            logFile_ << log;
        }
    }

    void Logger::WriteToConsole(const std::string& timeStamp, const LogLevelInfo::LogLevelInfo& logLevelInfo,
            const std::string& desc)
    {
        auto log = timeStamp + ' ' + ConsoleColor::SetConsoleColor(logLevelInfo.color) + '[' +
            logLevelInfo.info + ']' + ConsoleColor::GetDefaultColor() + ": " + desc + '\n';
        std::cout << log;
    }
}


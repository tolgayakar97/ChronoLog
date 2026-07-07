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

    LogLevelInfo::LogLevelInfo Logger::GetLogLevelInfo(const LogLevelInfo::LOG_LEVEL& level) const
    {
        // TODO: Return LogLevelInfo as reference to avoid copying, but ensure the lifetime of the returned reference is valid.
        return LogLevelInfo::infoArray[static_cast<std::size_t>(level)];
    }

    void Logger::Log(const LogContext& ctx)
    {
        std::lock_guard<std::mutex> lg_(mtx_);

        if (ctx.level < config_.logLevel) {
            return;
        }

        auto timeStamp = GetTimeStamp();

        if (config_.enableConsole) {
            WriteToConsole(timeStamp, ctx);
        }

        if (config_.enableFile && !config_.logFile.empty()) {
            WriteToFile(timeStamp, ctx);
        }
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

    void Logger::WriteToFile(const std::string& timeStamp, const LogContext& ctx)
    {
        std::stringstream log;
        auto logLevelInfo = GetLogLevelInfo(ctx.level);
        log << timeStamp << " [" << logLevelInfo.info << "] (" << ctx.func << '@' << ctx.file << ':' << ctx.line << ") " << ctx.desc << '\n';
        if (logFile_.is_open()) {
            logFile_ << log.str();
        } else {
            OpenLogFile();
            logFile_ << log.str();
        }
    }

    void Logger::WriteToConsole(const std::string& timeStamp, const LogContext& ctx)
    {
        auto logLevelInfo = GetLogLevelInfo(ctx.level);

        auto level = ConsoleColor::SetConsoleColor(logLevelInfo.color) + '[' +
            logLevelInfo.info + ']' + ConsoleColor::GetDefaultColor();
        
        std::stringstream log;
        log << timeStamp << ' ' << level << " (" << ctx.func << '@' << ctx.file << ':' << ctx.line << ") " << ctx.desc << '\n';
        std::cout << log.str();
    }
}


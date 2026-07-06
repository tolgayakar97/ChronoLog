#include <thread>
#include "Logger.h"

int main()
{
    LoggerConfig config;
    config.enableConsole = true;
    config.enableFile = true;
    config.logFile = "log.log";
    config.logLevel = LOG_LEVEL::INFO;

    auto &logger = Logger::GetInstance();
    logger.Configure(config);
    logger.OpenLogFile();

    std::thread t1(&Logger::InfoLog, std::ref(logger), "Deneme");
    std::thread t2(&Logger::DebugLog, std::ref(logger), "Deneme");
    std::thread t3(&Logger::WarnLog, std::ref(logger), "Deneme");
    std::thread t4(&Logger::ErrorLog, std::ref(logger), "Deneme");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
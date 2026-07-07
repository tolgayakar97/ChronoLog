#include <thread>
#include "Logger.h"

int main()
{
    Logger::LoggerConfig config;
    config.enableConsole = true;
    config.enableFile = false;
    config.logFile = "";
    config.logLevel = LogLevelInfo::LOG_LEVEL::INFO;

    auto &logger = Logger::Logger::GetInstance();
    logger.Configure(config);
    logger.OpenLogFile();

    auto string1 = "\033[31;1mDeneme\033[0m\n";
    auto string2 = "Deneme2";
    std::thread t1(&Logger::Logger::InfoLog, std::ref(logger), "Deneme");
    std::thread t2(&Logger::Logger::DebugLog, std::ref(logger), "Deneme");
    std::thread t3(&Logger::Logger::WarnLog, std::ref(logger), "Deneme");
    std::thread t4(&Logger::Logger::ErrorLog, std::ref(logger), "Deneme");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
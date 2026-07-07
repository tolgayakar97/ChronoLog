#include <thread>
#include "Logger.h"

void MainInfo()
{
    Logger::INFO_LOG("Info deneme");
}

void MainDebug()
{
    Logger::DEBUG_LOG("Debug deneme");
}

void MainWarn()
{
    Logger::WARNING_LOG("Warning deneme");
}

void MainError()
{
    Logger::ERROR_LOG("Error deneme");
}

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

    std::thread t1(MainInfo);
    std::thread t2(MainWarn);
    std::thread t3(MainDebug);
    std::thread t4(MainError);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
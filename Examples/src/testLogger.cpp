/**
 * @file testLogger.cpp
 * @author Brothers.AI (brothers.ai.local@gmail.com)
 * @brief Test App for Cpp Logger
 * @version 0.1
 * @date 2024-01-25
 * 
 */

// CppLogger Include
#include <CppLogger.h>

int main(int argc, char const *argv[])
{
    // Set the Logger Log Level
    Logger::getInstance().setLogLevel(Logger::LOG_TRACE);
    // Set the Logger Stream
    Logger::getInstance().setLogStream(Logger::STDOUT);
    // Set the Log File
    Logger::getInstance().setLogFile("logger.log");
    // Log For Fatal prints
    Logger::getInstance().fatal("Fatal Logs");
    // Log for Error prints
    Logger::getInstance().error("Error Logs");
    // Log for Warnings prints
    Logger::getInstance().warning("Warn Logs");
    // Log for Information prints
    Logger::getInstance().info("Info Logs");
    // Log for Debug prints
    Logger::getInstance().debug("Debug Logs");
    // Log for trace prints
    Logger::getInstance().trace("Trace Logs");
    // Log for profile prints
    Logger::getInstance().profile("Profile Logs");
    return 0;
}

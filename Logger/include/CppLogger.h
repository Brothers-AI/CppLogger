/**
 * @file CppLogger.h
 * @author Brothers.AI (brothers.ai.local@gmail.com)
 * @brief Logger class Declaration for Cpp
 * @version 0.1
 * @date 2024-01-25
 * 
 */
#ifndef __CPP_LOGGER_H__
#define __CPP_LOGGER_H__

// System Includes
#include <iostream>
#include <cstdarg>

/**
 * @brief Cpp Logger for Logging
 */
class Logger
{
public:
    /**
     * @brief Enums for Log Levels
     */
    enum LogLevel
    {
        // Log level for No Logging
        LOG_OFF = 0,
        // Log Level for Only Fatal Logs
        LOG_FATAL,
        // Log Level till Error Logs
        LOG_ERROR,
        // Log Level till Warn Logs
        LOG_WARN,
        // Log Level till Info Logs
        LOG_INFO,
        // Log Level till Debug Logs
        LOG_DEBUG,
        // Log Level till Trace Logs
        LOG_TRACE,
        // Log Level for Only Profile Logs
        LOG_PROFILE,
        // Maximum Number of Log Level
        LOG_MAX_LEVEL,
    };

    /**
     * @brief Enum for Stream
     */
    enum LogStream
    {
        // For stdout stream prints
        STDOUT,
        // For stderr stream prints
        STDERR
    };

    /**
     * @brief Destroy the Logger object
     */
    ~Logger();

    /**
     * @brief Get the Logger Instance
     *
     * @return Logger&
     */
    static Logger &getInstance();

    /**
     * @brief Get the Min Log Level
     *
     * @return unsigned char : Minimum Log level Allowed
     */
    static unsigned char getMinLogLevel();

    /**
     * @brief Get the Max Log Level
     *
     * @return unsigned char : Maximum Log Level Allowed
     */
    static unsigned char getMaxLogLevel();

    /**
     * @brief Set the Log Level for Logging
     * 
     * @param level Log Level (Logger::LogLevel)
     */
    void setLogLevel(LogLevel level);

    /**
     * @brief Set the Log Stream 
     * 
     * @param stream stream (Logger::LogStream)
     */
    void setLogStream(LogStream stream);

    /**
     * @brief Saves Logs to File instead of console print
     * 
     * @param filepath filepath to save the log
     */
    void setLogFile(const char *filepath);

    /**
     * @brief Logger for Fatal Logs
     * 
     * @param format print arguments
     * @param ... 
     */
    void fatal(const char *format, ...);

    /**
     * @brief Logger for Error Logs
     * 
     * @param format print arguments
     * @param ... 
     */
    void error(const char *format, ...);

    /**
     * @brief Logger for Warning Logs
     * 
     * @param format print arguments
     * @param ... 
     */
    void warning(const char *format, ...);

    /**
     * @brief Logger for Information Logs
     * 
     * @param format print arguments
     * @param ... 
     */
    void info(const char *format, ...);

    /**
     * @brief Logger for Debug Logs
     * 
     * @param format print arguments
     * @param ... 
     */
    void debug(const char *format, ...);

    /**
     * @brief Logger for Trace Logs
     * 
     * @param format print arguments
     * @param ... 
     */
    void trace(const char *format, ...);

    /**
     * @brief Logger for Profile Logs
     * 
     * @param format print arguments
     * @param ... 
     */
    void profile(const char *format, ...);

private:
    /**
     * @brief Construct a new Logger object
     */
    Logger();

    /**
     * @brief Construct a new Logger object
     */
    Logger(const Logger&) {}

    // Log Level for Logs
    LogLevel mCurrLogLevel;

    // Log Stream
    LogStream mLogStream;

    // Flag to Check setLogLevel Called
    bool mIsLogLevelInitalized;

    // Flag to Check setLogStream Called
    bool mIsLogStreamInitalized;

    // Flag to Check setLogFile Called
    bool mIsSetLogFileInitalized;
};

#endif // __CPP_LOGGER_H__
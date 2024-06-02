/**
 * @file CppLogger.cpp
 * @author Brothers.AI (brothers.ai.local@gmail.com)
 * @brief Logger Class Implementation for Cpp
 * @version 0.1
 * @date 2024-01-25
 * 
 */
// System Includes
#include <string>
#include <cstring>
#include <mutex>

#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdint.h>
#include <time.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#else
#include <sys/time.h>
#endif // _WIN32

// Logger Includes
#include <CppLogger.h>

// Mutex for logging
static std::mutex s_logMutex;

/**
 * @brief Color Codes for Different Log Levels
 */
const char colorCodes[Logger::LOG_MAX_LEVEL][10] = {
            "\033[1;31m",
            "\033[0;31m",
            "\033[0;33m",
            "\033[0;32m",
            "\033[0;36m",
            "\033[0;35m",
            "\033[0;32m"};

/**
 * @brief Print Available Log Levels
 */
void printAvaialbleLogs()
{
    printf("Available Values are: ");
    for (unsigned char i = static_cast<unsigned char>(Logger::LogLevel::LOG_OFF);
            i <= static_cast<unsigned char>(Logger::LogLevel::LOG_MAX_LEVEL) - 2; i++)
    {
        // Log Levels
        printf("%d, ", i);
    }
    // Log Level for Profiling
    printf("P\n");
}

/**
 * @brief Function to Print log on Console
 * 
 * @param stream Stream type (stdout or stderr) [Logger::LogStream]
 * @param logLevelName name of the log level
 * @param colorCode color code for the log level
 * @param format print format
 * @param args print arguments
 */
void printLog(Logger::LogStream stream, const char *logLevelName, const char *colorCode,
              const char *format, va_list args, bool isSavingToFile)
{
    char dateTime[30];
#ifdef _WIN32
    // Get System Time in Windows
    SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);
    sprintf(dateTime, "%d-%02d-%02d %02d:%02d:%02d:%03d",
            sysTime.wYear, sysTime.wMonth, sysTime.wDay,
            sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
#else
    timeval currTime;

    // Get time
    gettimeofday(&currTime, NULL);

    // Get Milliseconds time
    int milliSeconds = currTime.tv_usec / 1000;

    struct tm tm = *localtime(reinterpret_cast<time_t *>(&currTime.tv_sec));
    sprintf(dateTime, "%d-%02d-%02d %02d:%02d:%02d:%03d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec, milliSeconds);
#endif // _WIN32

    if (Logger::LogStream::STDOUT == stream)
    {
        // Output Stream in stdout
        if (isSavingToFile)
        {
            // To avoid interleved messages
            std::lock_guard<std::mutex> lock(s_logMutex);

            // Remove the color codes from the string
            fprintf(stdout, "[%s]:[%s] ", dateTime, logLevelName);
            vfprintf(stdout, format, args);
            vfprintf(stdout, "\n", args);
        }
        else
        {
            // To avoid interleved messages
            std::lock_guard<std::mutex> lock(s_logMutex);

            fprintf(stdout, "%s[%s]:[%s] ", colorCode, dateTime, logLevelName);
            vfprintf(stdout, format, args);
            vfprintf(stdout, "\033[1;0m\n", args);
        }
    }
    else if (Logger::LogStream::STDERR == stream)
    {
        // Output Stream in stderr
        if (isSavingToFile)
        {
            // To avoid interleved messages
            std::lock_guard<std::mutex> lock(s_logMutex);

            // Remove the color codes from the string
            fprintf(stderr, "[%s]:[%s] ", dateTime, logLevelName);
            vfprintf(stderr, format, args);
            vfprintf(stderr, "\n", args);
        }
        else
        {
            // To avoid interleved messages
            std::lock_guard<std::mutex> lock(s_logMutex);

            fprintf(stderr, "%s[%s]:[%s] ", colorCode, dateTime, logLevelName);
            vfprintf(stderr, format, args);
            vfprintf(stderr, "\033[1;0m\n", args);
        }
    }
}

/**
 * @brief Function to initalize the log file with respective to the stream
 * 
 * @param stream current selected stream
 * @param filepath filepath to save the log
 * @return true 
 * @return false 
 */
bool initalizeLogFile(Logger::LogStream stream, const char *filepath)
{
    bool isInitalized = true;
    if (Logger::LogStream::STDOUT == stream)
    {
        // Redirect stdout to file
        FILE *fp = freopen(filepath, "w", stdout);
        if (!fp)
        {
            printf("Failed to open file %s for writing\n", filepath);
            isInitalized = false;
        }
    }
    else if (Logger::LogStream::STDERR == stream)
    {
        // Redirect stderr to file
        FILE *fp = freopen(filepath, "w", stderr);
        if (!fp)
        {
            printf("Failed to open file %s for writing\n", filepath);
            isInitalized = false;
        }
    }
    else
    {
        printf("Not Implemented for Stream: %d\n", static_cast<unsigned char>(stream));
        isInitalized = false;
    }
    return isInitalized;
}

Logger::~Logger()
{
    if (mIsSetLogFileInitalized)
    {
        // Close the file
        if (LogStream::STDOUT == mLogStream)
            fclose(stdout);
        else if (LogStream::STDERR == mLogStream)
            fclose(stderr);
    }
}

Logger &Logger::getInstance()
{
    static Logger instance;
    return instance;
}

unsigned char Logger::getMinLogLevel()
{
    return static_cast<unsigned char>(LogLevel::LOG_OFF);
}

unsigned char Logger::getMaxLogLevel()
{
    return (static_cast<unsigned char>(LogLevel::LOG_MAX_LEVEL)) - 1;
}

void Logger::setLogLevel(LogLevel level)
{
    // If Already Initalized return
    if (mIsLogLevelInitalized)
        return;

    // Read the Environment Variable
    const char *envName = "LOG_LEVEL";
    const char *envVarData = std::getenv(envName);

    if (envVarData == NULL)
    {
        printf("Environment Variable \"%s\" is not available.\n", envName);
        mCurrLogLevel = level;
        if (mCurrLogLevel == LogLevel::LOG_PROFILE)
            printf("Setting Log Level to Profile\n");
        else
            printf("Setting Log Level to %d\n", static_cast<unsigned char>(mCurrLogLevel));
    }
    else
    {
        printf("Environment Variable \"%s\" is set to %s\n", envName, envVarData);

        // Check the Size of the Environment Variable (it should be 1)
        size_t envVarSize = strlen(envVarData);
        if (envVarSize != 1)
        {
            printf("Invalid Environment Variable Value (%s) passed\n", envVarData);
            // Avaialble Logs
            printAvaialbleLogs();
            mCurrLogLevel = LogLevel::LOG_OFF;
            printf("Setting Log Level to %d\n", static_cast<unsigned char>(mCurrLogLevel));
            return;
        }
        else
        {
            // Check the Character in LOG_LEVEL
            const unsigned char logLevel = static_cast<unsigned char>(envVarData[0]);
            // '0' to (LOG_MAX_LEVEL - 2) - 48 to -
            // 'P' for Profile Log Level
            if ((logLevel < 48 || logLevel > (48 + (LOG_MAX_LEVEL - 2))) && (logLevel != 'P'))
            {
                printf("Invalid Environment Variable Value (%s) passed\n", envVarData);
                printAvaialbleLogs();
                mCurrLogLevel = LogLevel::LOG_OFF;
                printf("Setting Log Level to %d\n", static_cast<unsigned char>(mCurrLogLevel));
                return;
            }

            if (logLevel == 'P')
            {
                mCurrLogLevel = LogLevel::LOG_PROFILE;
                printf("Setting Log Level to Profile\n");
            }
            else
            {
                mCurrLogLevel = static_cast<LogLevel>(logLevel - 48);
                printf("Setting Log Level to %d\n", static_cast<unsigned char>(mCurrLogLevel));
            }
        }
    }

    // Set the Flag for Initalize
    mIsLogLevelInitalized = true;

    return;
}

void Logger::setLogStream(LogStream stream)
{
    // Return if already Intialized
    if (mIsLogStreamInitalized)
        return;
    
    // Read the Environment Variable
    const char *envName = "LOG_STREAM";
    const char *envVarData = std::getenv(envName);

    if (envVarData == NULL)
    {
        printf("Environment Variable \"%s\" is not available\n", envName);

        // Set the Log Stream
        mLogStream = stream;

        printf("Setting Log Stream to %d\n", static_cast<unsigned char>(mLogStream));
    }
    else
    {
        printf("Environment Variable \"%s\" is set to %s\n", envName, envVarData);

        // Check the Size of the Environment Variable (it should be 1)
        size_t envVarSize = strlen(envVarData);
        if (envVarSize != 1)
        {
            printf("Invalid Environment Variable Value (%s) passed\n", envVarData);
            // Avaialble Logs Stream
            printf("Available Log Stream are: 0 and 1\n");
            mLogStream = LogStream::STDOUT;
            printf("Setting Log Stream to %d\n", static_cast<unsigned char>(mLogStream));
            return;
        }
        else
        {
            // Check the Character in LOG_STREAM
            const unsigned char logStream = static_cast<unsigned char>(envVarData[0]);
            // '0' and '1'
            if (logStream < 48 && logStream > 49)
            {
                printf("Invalid Environment Variable Value (%s) passed\n", envVarData);
                // Avaialble Logs Stream
                printf("Available Log Stream are: 0 and 1\n");
                mLogStream = LogStream::STDOUT;
                printf("Setting Log Stream to %d\n", static_cast<unsigned char>(mLogStream));
                return;
            }

            mLogStream = static_cast<LogStream>(logStream - 48);
            printf("Setting Log Stream to %d\n", static_cast<unsigned char>(mLogStream));
        }
    }

    // Set the Flag for Initalize
    mIsLogStreamInitalized = true;

    return;
}


void Logger::setLogFile(const char *filepath)
{
    if (mIsLogLevelInitalized && mIsLogStreamInitalized)
    {
        // Return if already initalized
        if (mIsSetLogFileInitalized)
            return;
        
        // Read the Environment Variable
        const char *envName = "LOG_FILE";
        const char *envVarData = std::getenv(envName);

        // Check if the Environment variable is set
        if (NULL == envVarData)
        {
            printf("Environment Variable \"%s\" is not available\n", envName);

            // Check if the filepath passes is null
            if (NULL == filepath)
            {
                // Defaulting to logger.log
                printf("Found NULL in filepath, Defaulting to logger.log");
                mIsSetLogFileInitalized = initalizeLogFile(mLogStream, "logger.log");
            }
            else
            {
                // Save to the respective file
                printf("Saving Logs to file (%s)\n", filepath);
                mIsSetLogFileInitalized = initalizeLogFile(mLogStream, filepath);
            }
            return;
        }
        else
        {
            // Save to the Environment variable file
            printf("Environment Variable \"%s\" is set to %s\n", envName, envVarData);
            printf("Saving Logs to file (%s)\n", envVarData);
            mIsSetLogFileInitalized = initalizeLogFile(mLogStream, envVarData);
            return;
        }
    }
    else
    {
        // Function Needs to be called after setLogLevel() and setLogStream()
        // Reason: File needs to created based on the LogStream
        printf("Please call the function setLogFile() after setLogLevel() and setLogStream()\n");
    }

    return;
}

void Logger::fatal(const char *format, ...)
{
    // Check if the Loglevel is Profile or less than the Fatal
    // If Less than Fatal, return. as it is not requried to print
    if ((mCurrLogLevel == LogLevel::LOG_PROFILE) || (mCurrLogLevel < LogLevel::LOG_FATAL))
        return;
    
    va_list args;
    va_start(args, format);
    printLog(mLogStream, "FATAL", colorCodes[static_cast<unsigned char>(LogLevel::LOG_FATAL) - 1],
             format, args, mIsSetLogFileInitalized);
    va_end(args);

    return;
}

void Logger::error(const char *format, ...)
{
    // Check if the Loglevel is Profile or less than the error
    // If Less than error, return. as it is not requried to print
    if ((mCurrLogLevel == LogLevel::LOG_PROFILE) || (mCurrLogLevel < LogLevel::LOG_ERROR))
        return;
    
    va_list args;
    va_start(args, format);
    printLog(mLogStream, "ERROR", colorCodes[static_cast<unsigned char>(LogLevel::LOG_ERROR) - 1],
             format, args, mIsSetLogFileInitalized);
    va_end(args);

    return;
}

void Logger::warning(const char *format, ...)
{
    // Check if the Loglevel is Profile or less than the warning
    // If Less than warning, return. as it is not requried to print
    if ((mCurrLogLevel == LogLevel::LOG_PROFILE) || (mCurrLogLevel < LogLevel::LOG_WARN))
        return;
    
    va_list args;
    va_start(args, format);
    printLog(mLogStream, "WARN", colorCodes[static_cast<unsigned char>(LogLevel::LOG_WARN) - 1],
             format, args, mIsSetLogFileInitalized);
    va_end(args);

    return;
}

void Logger::info(const char *format, ...)
{
    // Check if the Loglevel is Profile or less than the info
    // If Less than info, return. as it is not requried to print
    if ((mCurrLogLevel == LogLevel::LOG_PROFILE) || (mCurrLogLevel < LogLevel::LOG_INFO))
        return;
    
    va_list args;
    va_start(args, format);
    printLog(mLogStream, "INFO", colorCodes[static_cast<unsigned char>(LogLevel::LOG_INFO) - 1],
             format, args, mIsSetLogFileInitalized);
    va_end(args);

    return;
}

void Logger::debug(const char *format, ...)
{
    // Check if the Loglevel is Profile or less than the debug
    // If Less than debug, return. as it is not requried to print
    if ((mCurrLogLevel == LogLevel::LOG_PROFILE) || (mCurrLogLevel < LogLevel::LOG_DEBUG))
        return;
    
    va_list args;
    va_start(args, format);
    printLog(mLogStream, "DEBUG", colorCodes[static_cast<unsigned char>(LogLevel::LOG_DEBUG) - 1],
             format, args, mIsSetLogFileInitalized);
    va_end(args);

    return;
}

void Logger::trace(const char *format, ...)
{
    // Check if the Loglevel is Profile or less than the trace
    // If Less than trace, return. as it is not requried to print
    if ((mCurrLogLevel == LogLevel::LOG_PROFILE) || (mCurrLogLevel < LogLevel::LOG_TRACE))
        return;
    
    va_list args;
    va_start(args, format);
    printLog(mLogStream, "TRACE", colorCodes[static_cast<unsigned char>(LogLevel::LOG_TRACE) - 1],
             format, args, mIsSetLogFileInitalized);
    va_end(args);

    return;
}

void Logger::profile(const char *format, ...)
{
    // Check if the Loglevel is Profile
    // If not profile, return. as it is not requried to print
    if (mCurrLogLevel != LogLevel::LOG_PROFILE)
        return;
    
    va_list args;
    va_start(args, format);
    printLog(mLogStream, "PROFILE", colorCodes[static_cast<unsigned char>(LogLevel::LOG_PROFILE) - 1],
             format, args, mIsSetLogFileInitalized);
    va_end(args);

    return;
}

Logger::Logger()
{
    // Set Default Log Level Values
    mCurrLogLevel = LogLevel::LOG_OFF;

    // Set Default Log Stream
    mLogStream = LogStream::STDOUT;

    // Set mIsLogLevelInitalized to false;
    mIsLogLevelInitalized = false;

    // Set mIsLogStreamInitialized to false;
    mIsLogStreamInitalized = false;

    // Set mIsSetLogFileInitalized to false
    mIsSetLogFileInitalized = false;

#ifdef _WIN32
    // Flag setting for Color in Windows Console
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hInput, ENABLE_VIRTUAL_TERMINAL_INPUT);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(hOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif // _WIN32
}

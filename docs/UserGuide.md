<h1 style="text-align: center;">Cpp Logger - User Guide</h1>

## User Guide

**APIs**
 - **Logger::getInstance()**    - To get the Logger Instance Object
 - **Logger::getMinLogLevel()** - To get the Minimum Log level allowed in Cpp Logger
 - **Logger::getMaxLogLevel()** - To get the Maximum Log level allowed in Cpp Logger
 - **setLogLevel()**            - To set the Log Level for Logging
 - **setLogStream()**           - To set the Log Stream type (stdout / stderr)
 - **setLogFile()**             - To set the Log file for saving the logs
 - **fatal()**                  - To print fatal logs (LOG_LEVEL = 1)
 - **error()**                  - To print error logs (LOG_LEVEL = 2)
 - **warning()**                - To print warning logs (LOG_LEVEL = 3)
 - **info()**                   - To print information logs (LOG_LEVEL = 4)
 - **debug()**                  - To print debug logs (LOG_LEVEL = 5)
 - **trace()**                  - To print trace logs (LOG_LEVEL = 6)
 - **profile()**                - To print profile logs (LOG_LEVEL = P)
  
**Enumerations**
 - LogLevel
   - LogLevel::LOG_OFF        - For No Logs
   - LogLevel::LOG_FATAL      - For Fatal Logs
   - LogLevel::LOG_ERROR      - For Logs upto Error
   - LogLevel::LOG_WARN       - For Logs upto Warning
   - LogLevel::LOG_INFO       - For Logs upto Information
   - LogLevel::LOG_DEBUG      - For Logs upto Debug
   - LogLevel::LOG_TRACE      - For Logs upto Trace
   - LogLevel::LOG_PROFILE    - For only Profile Logs
   - LogLevel::LOG_MAX_LEVEL  - Maxmum Log Levels
 - LogStream
   - LogStream::STDOUT        - For stdout stream prints
   - LogStream::STDERR        - For stderr stream prints
  
## Usage

1. **setLogLevel()**
   1. Use this API to set the Log Level for Logging prints
   2. This API must be used in order to use the Environment variable `LOG_LEVEL` to get affect at runtime
   3. Environment Variable `LOG_LEVEL` if available, Log level will be setted to the value of `LOG_LEVEL` else the value passed to `setLogLevel` will be used.
   4. Available Values for `LOG_LEVEL` are: 0, 1, 2, 3, 4, 5, 6, P
   5. Environment Variable `LOG_LEVEL` can be set using: `export LOG_LEVEL=0`

   Example:
   ```
   #include <CppLogger.h>

   int main()
   {
        Logger::getInstance().setLogLevel(Logger::LogLevel::LOG_PROFILE);
        return 0;
   }
   ```


2. **setLogStream()**
   1. Use this API to set the Log Stream for Logging
   2. This API must be used in order to use the Environment Variable `LOG_STREAM` to get affect at runtime.
   3. Envirnoment Variable `LOG_STREAM` if available, Log stream will be setted to the value of `LOG_STREAM` else the value passes to `setLogStream` will be used.
   4. Available values for `LOG_STREAM` are: 0 (stdout), 1 (stderr)
   5. Environment Variable `LOG_STREAM` can be set using `export LOG_STREAM=0`
   
   Example:
   ```
   #include <CppLogger.h>

   int main()
   {
        Logger::getInstance().setLogStream(Logger::LogStream::STDOUT);
        return 0;
   }
   ```

3. **setLogFile()**
   1. Use this API to set the Log File for saving the logs
   2. This API must be used in order to use the Environment variable `LOG_FILE` to get affect at runtime
   3. Environment Variable `LOG_FILE` if available, Log file will used as the value of `LOG_FILE` else the value passed to `setLogFile` will be used.
   4. Environment Variable `LOG_FILE` can be set using: `export LOG_FILE=logger.log`

    Example:
    ```
    #include <CppLogger.h>

   int main()
   {
        Logger::getInstance().setLogFile("logfile.log");
        return 0;
   }
    ```


## Test Example

```
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
```
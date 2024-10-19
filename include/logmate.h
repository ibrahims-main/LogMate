#ifndef LOGMATE_H
#define LOGMATE_H

#include <string>
#include <fstream>
#include <iostream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <functional>

// Define log levels
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class LogMate {
public:
    LogMate(const std::string& filePath, LogLevel level);
    ~LogMate();

    // Logging methods
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);

    // Configuration methods
    void setLogLevel(LogLevel level);
    void setFormat(const std::string& format);
    void enableLogRotation(size_t maxSizeBytes);
    void setErrorHandler(const std::function<void(const std::string&)>& handler);

private:
    LogLevel currentLogLevel;
    std::string logFormat;
    std::ofstream logFile;
    std::mutex logMutex;
    size_t maxLogSize;
    std::function<void(const std::string&)> errorHandler;

    void log(const std::string& message, LogLevel level);
    std::string getTimestamp();
    std::string levelToString(LogLevel level);
    void rotateLogFile();
};

#endif // LOGMATE_H
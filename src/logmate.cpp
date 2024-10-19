#include "../include/logmate.h"

// Constructor: Opens log file and sets initial log level
LogMate::LogMate(const std::string& filePath, LogLevel level)
    : currentLogLevel(level), maxLogSize(0), errorHandler(nullptr) {
    logFile.open(filePath, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file!" << std::endl;
    }
}

// Destructor: Closes log file
LogMate::~LogMate() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

// Generic logging function
void LogMate::log(const std::string& message, LogLevel level) {
    if (level < currentLogLevel) return;

    std::lock_guard<std::mutex> lock(logMutex);

    std::string logMessage = getTimestamp() + " [" + levelToString(level) + "] " + message;

    // Log to file
    if (logFile.is_open()) {
        logFile << logMessage << std::endl;
        if (maxLogSize > 0 && logFile.tellp() >= maxLogSize) {
            rotateLogFile();
        }
    }

    // Log to console
    std::cout << logMessage << std::endl;
}

// Logging methods
void LogMate::debug(const std::string& message) { log(message, LogLevel::DEBUG); }
void LogMate::info(const std::string& message) { log(message, LogLevel::INFO); }
void LogMate::warning(const std::string& message) { log(message, LogLevel::WARNING); }
void LogMate::error(const std::string& message) { log(message, LogLevel::ERROR); }
void LogMate::critical(const std::string& message) { log(message, LogLevel::CRITICAL); }

// Set log level
void LogMate::setLogLevel(LogLevel level) {
    currentLogLevel = level;
}

// Set custom format (this could be extended later)
void LogMate::setFormat(const std::string& format) {
    logFormat = format;
}

// Enable log rotation
void LogMate::enableLogRotation(size_t maxSizeBytes) {
    maxLogSize = maxSizeBytes;
}

// Set custom error handler
void LogMate::setErrorHandler(const std::function<void(const std::string&)>& handler) {
    errorHandler = handler;
}

// Rotate log file when it exceeds the maximum size
void LogMate::rotateLogFile() {
    logFile.close();
    logFile.open("log_rotated.txt", std::ios::out | std::ios::trunc); // Rotate to a new file
}

// Get the current timestamp as a string
std::string LogMate::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Convert log level enum to string
std::string LogMate::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}
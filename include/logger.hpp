#pragma once

#include <fmt/chrono.h>
#include <fmt/format.h>
#include <switch.h>

#include <ctime>
#include <string>

enum class LogLevel {
    ERROR = 0,
    WARNING,
    INFO,
    DEBUG
};

class Logger {
public:
    static void setLogLevel(LogLevel logLevel) {
        Logger::logLevel = logLevel;
    }

    template <typename... Args>
    static void error(std::string format, Args&&... args) {
        Logger::log(LogLevel::ERROR, "ERROR", format, args...);
    }

    template <typename... Args>
    static void warning(std::string format, Args&&... args) {
        Logger::log(LogLevel::WARNING, "WARNING", format, args...);
    }

    template <typename... Args>
    static void info(std::string format, Args&&... args) {
        Logger::log(LogLevel::INFO, "INFO", format, args...);
    }

    template <typename... Args>
    static void debug(std::string format, Args&&... args) {
        Logger::log(LogLevel::DEBUG, "DEBUG", format, args...);
    }

private:
    inline static LogLevel logLevel = LogLevel::INFO;

    template <typename... Args>
    static void log(LogLevel logLevel, std::string prefix,
        std::string format, Args&&... args) {
        if (Logger::logLevel < logLevel)
            return;

        try {
            std::time_t time = std::time(nullptr);

            std::string logString = fmt::format(
                "[{}] [{:%a %b %d %H:%M:%S %Y}] [{}] {}", PROJECT_NAME,
                fmt::localtime(time), prefix, fmt::format(format, args...));

            printf("%s\n", logString.c_str());

#ifndef NDEBUG
            svcOutputDebugString(logString.c_str(), logString.size());
#endif
        } catch (const std::exception& e) {
            std::string logString = fmt::format("[{}] ! Invalid log format string: \"{}\": {}",
                PROJECT_NAME, format.c_str(), e.what());

            printf("%s\n", logString.c_str());

#ifndef NDEBUG
            svcOutputDebugString(logString.c_str(), logString.size());
#endif
        }
    }
};
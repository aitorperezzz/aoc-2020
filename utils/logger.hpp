#pragma once

#include <string>

enum LogLevel
{
    INFO,
    ERROR,
    DEBUG
};

// Logger class
class Logger
{
private:
    static bool silent;

public:
    static void log(const std::string &message, LogLevel level);
    static void setSilentMode(const bool inSilent);
};
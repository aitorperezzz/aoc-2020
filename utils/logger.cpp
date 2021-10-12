#include <iostream>

#include "logger.hpp"

bool Logger::silent = false;

void Logger::log(const std::string &message, LogLevel level)
{
    if (silent)
    {
        return;
    }

    std::string begin;
    switch (level)
    {
    case INFO:
        begin = "Info: ";
        break;
    case ERROR:
        begin = "Error: ";
        break;
    case DEBUG:
        begin = "Debug: ";
        break;
    }

    std::cout << begin + message << std::endl;
}

void Logger::setSilentMode(const bool inSilent)
{
    silent = inSilent;
}
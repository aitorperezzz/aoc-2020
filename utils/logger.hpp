#pragma once

#include <string>

enum LogLevel
{
	INFO,
	ERROR,
	DEBUG
};

// If silent mode is on, calls to logger will not print
// to the console. This mode is mainly for unit testing.
inline bool silentMode = false;

class Logger
{

public:
	static void log(const std::string& message, LogLevel level);
	static void setSilentMode(void);
};
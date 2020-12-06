#pragma once

#include <string>

enum LogLevel
{
	INFO,
	ERROR,
	DEBUG
};

class Logger
{

public:
	static void log(const std::string& message, LogLevel level);
};
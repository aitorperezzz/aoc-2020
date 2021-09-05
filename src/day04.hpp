#pragma once

#include <string>
#include <map>
#include <vector>

#include "errorCode.hpp"

#define Passport std::map<std::string, std::string>

class Day04
{

public:
	static ErrorCode execute(const std::string& filename, int& result1,
	int& result2);

private:
	static ErrorCode parseToMap(std::vector<Passport>& passports,
		const std::vector<std::string>& inData);
	static ErrorCode parseLine(Passport& passport, const std::string& line);
	static void debugPassports(std::vector<Passport>& passports);
	static ErrorCode checkRequiredFields(int& presentCounter, int& validCounter,
		const std::vector<Passport>& passports);
	
	static bool checkValidity(const std::string& key, const std::string& value);
	static bool checkIntBetween(const std::string& value,
		const int& min, const int& max);
	static bool checkHeight(const std::string& value);
	static bool checkHairColor(const std::string& value);
	static bool checkEyeColor(const std::string& value);
	static bool checkPassportID(const std::string& value);

	static void debugPassport(Passport& pass);
};
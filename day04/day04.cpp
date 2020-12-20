#include <vector>
#include <string>
#include <map>

#include "day04.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

ErrorCode Day04::execute(const std::string& filename, int& result1, int& result2)
{
	// Load the input file as a vector of strings.
	std::vector<std::string> inData;
	if (FileOpener::loadVector(inData, filename) != Ok)
	{
		Logger::log("Could not load input information from file", ERROR);
		return InvalidFile;
	}

	// Parse all the information into a vector of maps. Each map will
	// be a passport, where all key value pairs will be found.
	std::vector<Passport> passports;
	if (parseToMap(passports, inData) != Ok)
	{
		Logger::log("Could not parse all the passport information to map", ERROR);
		return InternalInconsistency;
	}

	//debugPassports(passports);

	// Check the passports have all required fields and are valid.
	if (checkRequiredFields(result1, result2, passports) != Ok)
	{
		Logger::log("Could not check validity of the passports", ERROR);
		return InternalInconsistency;
	}

	Logger::log("Number of passports with all required fields: " + std::to_string(result1), INFO);
	Logger::log("Number of passports with all required fields valid: " + std::to_string(result2), INFO);
	return Ok;
}

ErrorCode Day04::parseToMap(std::vector<Passport>& passports,
	const std::vector<std::string>& inData)
{
	// Initialize the list of passports with one.
	passports.push_back({});

	// Loop over all the lines in the file
	for (auto i = inData.begin(); i != inData.end(); i++)
	{
		// Add a new passport if this current line is blank,
		// and in fact skip it.
		if (*i == "")
		{
			passports.push_back({});
			continue;
		}

		// If not blank, parse it to the current passport.
		if (parseLine(passports.back(), *i) != Ok)
		{
			Logger::log("Could not parse line in input file", ERROR);
			return InvalidFile;
		}
	}

	return Ok;
}

ErrorCode Day04::parseLine(Passport& passport, const std::string& line)
{
	size_t iPos = 0, fPos;
	std::string key, value;
	while (iPos < line.length())
	{
		// Find the key.
		fPos = line.find(':', iPos);
		if (fPos != std::string::npos)
		{
			key = line.substr(iPos, fPos - iPos);
			iPos = fPos + 1;
		}
		else
		{
			Logger::log("There was a problem finding a key", ERROR);
			return InternalInconsistency;
		}

		// Find the value.
		iPos = fPos + 1;
		fPos = line.find(' ', iPos);
		if (fPos != std::string::npos)
		{
			value = line.substr(iPos, fPos - iPos);
			iPos = fPos + 1;
		}
		else
		{
			// We have reached the end of the line.
			value = line.substr(iPos, line.length() - iPos);
			iPos = line.length() + 1;
		}
		
		// Add this key value pair to the map.
		passport[key] = value;
	}

	return Ok;
}

ErrorCode Day04::checkRequiredFields(int& presentCounter, int& validCounter,
	const std::vector<Passport>& passports)
{
	// Define the required fields in the passports.
	std::vector<std::string> requiredFields;
	requiredFields.push_back("byr");
	requiredFields.push_back("iyr");
	requiredFields.push_back("eyr");
	requiredFields.push_back("hgt");
	requiredFields.push_back("hcl");
	requiredFields.push_back("ecl");
	requiredFields.push_back("pid");

	// Loop over all passports.
	presentCounter = 0;
	validCounter = 0;
	bool present, valid;
	for (auto pass = passports.begin(); pass != passports.end(); pass++)
	{
		// This passport has everything present by default,
		// and all values are valid.
		present = true;
		valid = true;

		// Loop over all required fields.
		for (auto field = requiredFields.begin(); field != requiredFields.end(); field++)
		{
			auto currentPair = (*pass).find(*field);
			if (currentPair == (*pass).end())
			{
				// The required key is not in the map.
				present = false;
				break;
			}
			else if (valid)
			{
				// The key is present in the map and the passport is still valid,
				// so check validity.
				if (!checkValidity((*currentPair).first, (*currentPair).second))
				{
					Logger::log("valid", INFO);
					Logger::log((*currentPair).first + ", " + (*currentPair).second, INFO);
					valid = false;
				}
				else
				{
					Logger::log("valid", INFO);
					Logger::log((*currentPair).first + ", " + (*currentPair).second, INFO);
				}
			}
		}

		if (present)
		{
			presentCounter++;
			if (valid)
			{
				//debugPassport(*pass);
				validCounter++;
			}
		}
	}

	return Ok;
}

void Day04::debugPassports(std::vector<Passport>& passports)
{
	for (auto pass = passports.begin(); pass != passports.end(); pass++)
	{
		for (auto pair = (*pass).begin(); pair != (*pass).end(); pair++)
		{
			Logger::log((*pair).first + ", " + (*pair).second, DEBUG);
		}
		Logger::log("", DEBUG);
	}
}

/*void Day04::debugPassport(Passport& pass)
{
	for (auto pair = pass.begin(); pair != pass.end(); pair++)
	{
		Logger::log((*pair).first + ", " + (*pair).second, DEBUG);
	}
}*/


bool Day04::checkValidity(const std::string& key, const std::string& value)
{
	if (key == "byr")
	{
		return checkIntBetween(value, 1920, 2002);
	}
	else if (key == "iyr")
	{
		return checkIntBetween(value, 2010, 2020);
	}
	else if (key == "eyr")
	{
		return checkIntBetween(value, 2020, 2030);
	}
	else if (key == "hgt")
	{
		return checkHeight(value);
	}
	else if (key == "hcl")
	{
		return checkHairColor(value);
	}
	else if (key == "ecl")
	{
		return checkEyeColor(value);
	}
	else if (key == "pid")
	{
		return checkPassportID(value);
	}
	
	return false;
}

bool Day04::checkIntBetween(const std::string& value,
	const int& min, const int& max)
{
	// Convert to an integer.
	int number;
	try
	{
		number = std::stoi(value);
	}
	catch(const std::exception& e)
	{
		return false;
	}

	// Check validity of number.
	return min <= number && number <= max;
}

bool Day04::checkHeight(const std::string& value)
{
	size_t length = value.length();
	std::string unit = value.substr(length - 2, 2);
	if (unit == "cm")
	{
		return checkIntBetween(value.substr(0, length - 2), 150, 193);
	}
	else if (unit == "in")
	{
		return checkIntBetween(value.substr(0, length - 2), 59, 76);
	}

	return false;
}

bool Day04::checkHairColor(const std::string& value)
{
	// Check first character.
	if (value[0] != '#')
	{
		return false;
	}

	// Check length.
	if (value.length() != 7)
	{
		return false;
	}

	// Check each value after the #.
	for (size_t i = 1, n = value.length(); i < n; i++)
	{
		if (!std::isdigit(value[i]) &&
			!('a' <= value[i] && value[i] <= 'f'))
		{
			return false;
		}
	}

	return true;
}

bool Day04::checkEyeColor(const std::string& value)
{
	if (value == "amb" ||
		value == "blu" ||
		value == "brn" ||
		value == "gry" ||
		value == "grn" ||
		value == "hzl" ||
		value == "oth")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Day04::checkPassportID(const std::string& value)
{
	// Check the number of digits.
	if (value.length() != 9)
	{
		return false;
	}

	// Check it can be converted to an int.
	try
	{
		std::stoi(value);
	}
	catch(const std::exception& e)
	{
		return false;
	}

	return true;
}

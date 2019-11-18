#pragma once
#include <string>

class MyFunctions {
public:
	// Converts uppercase to lower
	static char toLower(char c);

	// Does string comparison with option to do caseless checking
	static bool strEqual(const std::string &str1, const std::string &str2, bool caseless = false);

	// Removes leading and trailing whitespace
	static std::string trim(const std::string &str);
	
	// Checks if character is whitespace
	static bool isWhiteSpace(char c);

	// Checks if string1 contains string2 with the option of caseless checking
	static size_t strContains(const std::string &str1, const std::string &str2, bool caseless = false);
};

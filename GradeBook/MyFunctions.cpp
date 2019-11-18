#include "MyFunctions.hpp"

// Converts uppercase to lower
char MyFunctions::toLower(char c) {
	if ('A' <= c && c <= 'Z') c += 32;
	return c;
}

// Does string comparison with option to do caseless checking
bool MyFunctions::strEqual(const std::string &str1, const std::string &str2, bool caseless) {
	if (!caseless) {
		return str1 == str2;
	}

	size_t len = str1.length();
	if (len != str2.length()) {
		return false;
	}

	for (size_t i = 0; i < len; ++i) {
		if (toLower(str1[i]) != toLower(str2[i])) {
			return false;
		}
	}

	return true;
}

// Removes leading and trailing whitespace
std::string MyFunctions::trim(const std::string &str) {
	if (!str.length()) {
		return "";
	}

	unsigned int begin = 0, end = str.length() - 1;
	while (isWhiteSpace(str[begin]) && begin <= end) {
		++begin;
	}
	while (isWhiteSpace(str[end]) && begin <= end) {
		--end;
	}

	return str.substr(begin, end - begin + 1);
}

// Checks if character is whitespace
bool MyFunctions::isWhiteSpace(char c) {
	switch (c) {
	case ' ': case '\t': case '\n': case '\r': case '\f': case '\v':
		return true;
	}

	return false;
}

// Checks if string 1 contains string 2 with caseless option
size_t MyFunctions::strContains(const std::string &str1, const std::string &str2, bool caseless) {
	std::string _str1 = str1, _str2 = str2;
	if (caseless) {
		size_t len = _str1.length();
		for (size_t i = 0; i < len; ++i) {
			_str1[i] = toLower(_str1[i]);
		}
		len = _str2.length();
		for (size_t i = 0; i < len; ++i) {
			_str2[i] = toLower(_str2[i]);
		}
	}

	return _str1.find(_str2);
}

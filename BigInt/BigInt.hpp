/* BigInt
 * A class which to be utilized for handling very large integer values */

#pragma once
#include <string>
#include <iostream>
#include "Collection.hpp"

class BigInt {
public:
/* Constructors */
	// Default constructor
	// Sets value to 0 and initializes negative to false
	BigInt();
	// Constructor with string param
	// Throws std::invalid_argument if string invalid value
	BigInt(std::string const &);
	// Constructor with long long param
	// Range of -9,223,372,036,854,775,807
	// to 9,223,372,036,854,775,807
	BigInt(long long);

/* Comparative operators */
	bool operator==(BigInt const &) const;
	bool operator!=(BigInt const &) const;
	bool operator<(BigInt const &) const;
	bool operator>(BigInt const &) const;
	bool operator<=(BigInt const &) const;
	bool operator>=(BigInt const &) const;

/* Arithmatic operators */
	BigInt operator+(BigInt const &) const;
	BigInt operator-() const;
	BigInt operator-(BigInt const &) const;
	BigInt &operator++(); // Pre
	BigInt operator++(int); // Post
	BigInt &operator--(); // Pre
	BigInt operator--(int); // Post

/* Assignment operators */
	BigInt &operator+=(BigInt const &);
	BigInt &operator-=(BigInt const &);

/* ios operators */
	friend std::ostream &operator<<(std::ostream &os, const BigInt &b);
	friend std::istream &operator>>(std::istream &os, BigInt &b);

/* Function members */
	// Returns the BigInt value as a string
	std::string toString() const;
	// Compares BigInt value to other BigInt value
	//
	// -1 if this is less than other
	//  0 if this is equal to other
	//  1 if this is greater than other
	short compare(BigInt const &) const;

	// Checks if a string input is a valid BigInt value
	static bool isValidValue(std::string const &s);

private:
	// Store unsigned single byte
	// Index 0 is first place value, Index 1 is second, etc.
	mylib::Collection<char> m_value;
	// Is this BigInt value negative?
	bool m_isNegative;
	
	// Attempts to set value. If string is non-numeric, throws std::invalid_argument
	// Set valid to true if the string has already been validated
	void setValue(std::string const &s, bool validated = false);

	// Removes leading 0's from the BigInt value
	void trimLeadingZeros();
};

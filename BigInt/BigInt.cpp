#include "BigInt.hpp"
#include <stdexcept> /* std::invalid_argument */
#include <sstream> /* stringstream */

// -------------- Public
/* Default constructor
 * Sets value to 0 and initializes negative to false */
BigInt::BigInt() {
	m_isNegative = false;
	m_value.push(0);
}

/* Constructor with string param 
 * Throws std::invalid_argument if string invalid value */
BigInt::BigInt(std::string const &s) {
	setValue(s);
}

/* Constructor with long long param
 * Range of -9,223,372,036,854,775,807
 * to 9,223,372,036,854,775,807 */
BigInt::BigInt(long long value) {
	// Use string stream to convert value to string
	// No need to mess with looping arithmatic
	std::stringstream ss;
	ss << value;

	setValue(ss.str(), true);
}

/* Returns the BigInt value as a string */
std::string BigInt::toString() const {
	std::stringstream s;
	if (m_isNegative) {
		s << '-';
	}

	// Loop backwards and add to string stream. 'i' is used due to using unsigned
	size_t thisSize = m_value.size();
	for (size_t i = 0, idx = thisSize - 1; i < thisSize; ++i, --idx) {
		s << (short)m_value[idx];
	}

	// Pass by ref for efficiency
	return std::move(s.str());
}

/* Checks if two BigInt values are equal */
bool BigInt::operator==(BigInt const &other) const {
	return compare(other) == 0;
}

/* Checks if two BigInt values are not equal */
bool BigInt::operator!=(BigInt const &other) const {
	return compare(other) != 0;
}

/* Checks if one BigInt value is less than the other */
bool BigInt::operator<(BigInt const &other) const {
	return compare(other) == -1;
}

/* Checks if one BigInt value is greater than the other */
bool BigInt::operator>(BigInt const &other) const {
	return compare(other) == 1;
}

/* Checks if one BigInt value is greater than or equal to the other */
bool BigInt::operator<=(BigInt const &other) const {
	return compare(other) != 1;
}

/* Checks if one BigInt value is greater than or equal to the other */
bool BigInt::operator>=(BigInt const &other) const {
	return compare(other) != -1;
}

/* Adds one BigInt to the other and returns the result as another BigInt */
BigInt BigInt::operator+(BigInt const &other) const {
	BigInt buffer; buffer.m_value.clear();
	size_t thisSize = m_value.size();
	size_t otherSize = other.m_value.size();
	bool carry = false;
	short value;

	// If both have same sign
	if (m_isNegative == other.m_isNegative) {
		buffer.m_isNegative = m_isNegative;

		// Use value of larger length to determine loop
		if (thisSize >= otherSize) {
			// Iterate through each index and add the two
			for (size_t i = 0; i < thisSize; ++i) {
				value = carry; // add one if previous iteration had a carry over value

				if (i < otherSize) { // if still iterating over both, add both together
					value += m_value[i] + other.m_value[i];
				}
				else { // otherwise, only add the one of larger length
					value += m_value[i];
				}

				carry = value > 9; // Set carry to true if value is greater than 9
				buffer.m_value.push(value % 10); // Perform mod 10 on value and add
			}
		}
		else { // Same as above, except uses other bigint to control loop
			for (size_t i = 0; i < otherSize; ++i) {
				value = carry;

				if (i < thisSize) {
					value += m_value[i] + other.m_value[i];
				}
				else {
					value += other.m_value[i];
				}
				
				carry = value > 9;
				buffer.m_value.push(value % 10);
			}
		}

		if (carry) { // Push one if there's still a carry over value
			buffer.m_value.push(1);
		}
	}
	else {
		if (m_isNegative) { // if this is negative and other is positive
			if (-*this < other) { // if positive this is less than other
				for (size_t i = 0; i < otherSize; ++i) { // use otherSize to dictate loop
					if (i < thisSize) {
						value = other.m_value[i] - m_value[i];
					}
					else {
						value = other.m_value[i];
					}

					value -= carry;
					carry = value < 0;

					buffer.m_value.push(carry ? value + 10 : value);
				}
			}
			else { // otherwise use thisSize to dictate loop
				buffer.m_isNegative = true; // new value will be negative

				for (size_t i = 0; i < thisSize; ++i) {
					if (i < otherSize) { // subtract both values if still in range
						value = m_value[i] - other.m_value[i];
					}
					else { // otherwise only set it to the longer value
						value = m_value[i];
					}

					value -= carry; // subtract 1 if there was a previous carry over
					carry = value < 0;
					buffer.m_value.push(carry ? value + 10 : value); // add our new value to the collection
				}
			}
		}
		else { // if this is positive and other is negative ... inverse of above
			if (*this < -other) {
				buffer.m_isNegative = true;

				for (size_t i = 0; i < otherSize; ++i) {
					if (i < thisSize) {
						value = other.m_value[i] - m_value[i];
					}
					else {
						value = other.m_value[i];
					}

					value -= carry;
					carry = value < 0;

					buffer.m_value.push(carry ? value + 10 : value);
				}
			}
			else {
				for (size_t i = 0; i < thisSize; ++i) {
					if (i < otherSize) {
						value = m_value[i] - other.m_value[i];
					}
					else {
						value = m_value[i];
					}

					value -= carry;
					carry = value < 0;
					buffer.m_value.push(carry ? value + 10 : value);
				}
			}
		}

		buffer.trimLeadingZeros();
	}

	return buffer;
}

/* Negates the value of the BigInt value */
BigInt BigInt::operator-() const {
	BigInt buffer(*this);
	buffer.m_isNegative = !buffer.m_isNegative;

	return buffer;
}

/* Subtracts other from this. */
BigInt BigInt::operator-(BigInt const &other) const {
	// No need to rewrite, just negate other and add
	return *this + -other;
}

/* Pre-increment */
BigInt &BigInt::operator++() {
	return *this = *this + 1;
}

/* Post-increment */
BigInt BigInt::operator++(int) {
	BigInt buffer(*this);
	*this = *this + 1;

	return buffer;
}

/* Pre-decrement */
BigInt &BigInt::operator--() {
	return *this = *this - 1;
}

/* Post-decrement */
BigInt BigInt::operator--(int) {
	BigInt buffer(*this);
	*this = *this - 1;

	return buffer;
}

/* Addition assignment */
BigInt &BigInt::operator+=(BigInt const &other) {
	return *this = *this + other;
}

/* Subtraction assignment */
BigInt &BigInt::operator-=(BigInt const &other) {
	return *this = *this + -other;
}

/* Compares BigInt value to value of other BitInt
 *
 * @return       -1 if this is less than other
 *                0 if this is equal to other
 *                1 if this is greater than other */
short BigInt::compare(BigInt const &other) const {
	if (m_isNegative) { // if this is negative ...
		if (!other.m_isNegative) { // and other is positive ...
			return -1; // this is less than other ...
		}
	}
	else if (other.m_isNegative) { // else if this is positive and other is negative ...
		return 1; // this is greater than other
	}

	size_t thisSize = m_value.size();
	size_t otherSize = other.m_value.size();

	if (thisSize > otherSize) { // if this value len is greater than other value len
		if (m_isNegative) { // if this is negative
			return -1; // this is less than other
		}
		return 1; // else this is greater than other
	}

	if (thisSize < otherSize) { // same as above, but opposite
		if (m_isNegative) {
			return 1;
		}
		return -1;
	}

	// Iterate backwards through values and compare
	for (size_t i = 0, idx = thisSize - 1; i < thisSize; ++i, --idx) {
		if (m_value[idx] == other.m_value[idx]) {
			continue;
		}

		// If this[idx] is less than other[idx]
		if (m_value[idx] < other.m_value[idx]) {
			return m_isNegative ? 1 : -1;
		}

		// else if this[idx] is greater than other[idx]
		return m_isNegative ? -1 : 1;
	}
	return 0; // This equals other
}

/* Checks if a string input is a valid BigInt value */
bool BigInt::isValidValue(std::string const &s) {
	size_t start = 0;

	// If first char is hyphen, treat as negative value
	if (s[0] == '-') {
		++start;
	}

	size_t thisSize = s.size();
	// Loop through string backwards
	// This is done so that arr[0] will 1's placevalue, arr[1] == 10's, arr[2] == 100's ...
	for (size_t i = start, idx = s.size() - 1; i < thisSize; ++i, --idx) {
		// if non numeric, throw
		if (s[idx] < '0' || s[idx] > '9') {
			return false;
		}
	}

	return true;
}

// -------------- Friend
/* Insertion operator
 * Outputs BigInt value as string */
std::ostream &operator<<(std::ostream &out, const BigInt &b) {
	// Convert to string and output it
	out << b.toString();

	return out;
}

/* Extraction operator
 * If invalid input, istream set to fail and BitInt valid set to 0
 * else sets value of BigInt to input */
std::istream &operator>>(std::istream &in, BigInt &b) {
	std::ios_base::iostate err = std::ios_base::goodbit;
	std::string s;
	in >> s;
	
	// Validate input. If not valid, set state to fail
	if (!BigInt::isValidValue(s)) {
		err = std::ios_base::badbit;
		b.setValue(static_cast<std::string>(""));
	}
	else {
		b.setValue(s, true);
	}

	in.setstate(err);

	return in;
}

// -------------- Private

/* Sets the BigInt value
 * If validated is true, this method will not attempt to validated the string input */
void BigInt::setValue(std::string const &s, bool validated) {
	m_value.clear();

	if (s.empty()) {
		m_value.push(0);
		return;
	}

	size_t start = 0;

	// If first char is hyphen, treat as negative value
	if (s[0] == '-') {
		++start;
		m_isNegative = true;
	}
	else {
		m_isNegative = false;
	}

	size_t thisSize = s.size();

	if (!validated) { // if not validated, loop and check
		// Loop through string backwards
		// This is done so that arr[0] will 1's placevalue, arr[1] == 10's, arr[2] == 100's ...
		for (size_t i = start, idx = thisSize - 1; i < thisSize; ++i, --idx) {
			// if non numeric, throw
			if (s[idx] < '0' || s[idx] > '9') {
				throw std::invalid_argument(std::string("Value must be numeric: ") + s);
			}

			// convert to int and store as char for efficiency (1 byte)
			m_value.push(s[idx] - '0');
		}
	}
	else { // if validated, loop through and add value
		for (size_t i = start, idx = thisSize - 1; i < thisSize; ++i, --idx) {
			m_value.push(s[idx] - '0');
		}
	}
	trimLeadingZeros();
}

// Removes leading 0's from the BigInt value
void BigInt::trimLeadingZeros() {
	size_t count = m_value.size();
	for (size_t i = 0, j = count - 1; i < count && !m_value[j]; ++i, --j) {
		m_value.erase(j);
	}

	if (m_value.size() == 0) {
		m_value.push(0);
		m_isNegative = false;
	}
}
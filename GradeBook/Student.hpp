#pragma once
#include <string>
#include <cstdint>

using StudentID = uint32_t;

class Student {
private:
	// Incrementor used for unique student id
	static StudentID incrementor;
	// Unique id, set on creation
	StudentID id;

	std::string name;
public:
	Student(const std::string &name = "");

	std::string getName() const;
	void setName(const std::string &name);

	StudentID getID() const;

	static StudentID getNextID();
};

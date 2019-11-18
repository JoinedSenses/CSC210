#include "Student.hpp"

// -- Private --

StudentID Student::incrementor = 1;

// -- Public --

Student::Student(const std::string &n) {
	name = n;
	id = incrementor++;
}

std::string Student::getName() const {
	return name;
}

void Student::setName(const std::string &n) {
	name = n;
}

StudentID Student::getID() const {
	return id;
}

StudentID Student::getNextID() {
	return incrementor;
}
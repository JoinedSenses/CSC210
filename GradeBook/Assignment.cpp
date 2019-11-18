#include "Assignment.hpp"

// -- Private --

AssignmentID Assignment::incrementor = 1;

// -- Public --

Assignment::Assignment(const std::string &n, double m) {
	name = n;
	maxPoints = m;
	id = incrementor++;
}

std::string Assignment::getName() const {
	return name;
}

void Assignment::setName(const std::string &n) {
	name = n;
}

AssignmentID Assignment::getID() const {
	return id;
}

double Assignment::getMaxPoints() const {
	return maxPoints;
}

void Assignment::setMaxPoints(double m) {
	maxPoints = m;
}

bool Assignment::hasScore(StudentID studentID) const {
	return scores.find(studentID) != scores.end();
}

double Assignment::getScore(StudentID studentID) const {
	std::map<uint32_t, double>::const_iterator it = scores.find(studentID);
	if (it != scores.end()) {
		return it->second;
	}
	return 0.0;
}

void Assignment::setScore(StudentID studentID, double score) {
	scores[studentID] = score;
}

bool Assignment::removeScore(StudentID studentID) {
	std::map<StudentID, double>::iterator it = scores.find(studentID);
	if (it != scores.end()) {
		scores.erase(it);
		return true;
	}
	return false;
}

AssignmentID Assignment::getNextID() {
	return incrementor;
}
#pragma once
#include <cstdint> // uint*_t
#include <string>
#include <map>

using AssignmentID = uint32_t;
using StudentID = uint32_t;

class Assignment {
private:
	// increments each time a new Assignment is created;
	static AssignmentID incrementor;
	// unique id
	AssignmentID id;

	std::string name;
	double maxPoints;
	std::map<StudentID, double> scores; // {studentID, score}
public:
	Assignment(const std::string &name = "", double maxPoints = 100.0);

	std::string getName() const;
	void setName(const std::string &name);

	AssignmentID getID() const;

	double getMaxPoints() const;
	void setMaxPoints(double max);

	bool hasScore(StudentID studentID) const;
	double getScore(StudentID studentID) const;
	void setScore(StudentID studentID, double score);
	bool removeScore(StudentID studentID);

	static AssignmentID getNextID();
};

#pragma once
#include <string>
#include <vector>

class AssignmentCategory {
private:
	std::string name;
	double weight;
public:
	AssignmentCategory(const std::string &name = "", double weight = 0.0);
	std::vector<uint32_t> assignmentIDs;

	std::string getName() const;
	void setName(const std::string &name);

	double getWeight() const;
	void setWeight(double weight);
};
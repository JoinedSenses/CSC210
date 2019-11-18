#include "AssignmentCategory.hpp"

AssignmentCategory::AssignmentCategory(const std::string &n, double w) {
	name = n;
	weight = w;
}

std::string AssignmentCategory::getName() const {
	return name;
}

void AssignmentCategory::setName(const std::string &n) {
	name = n;
}

double AssignmentCategory::getWeight() const {
	return weight;
}

void AssignmentCategory::setWeight(double w) {
	weight = w;
}
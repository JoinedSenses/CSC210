#include "GradeBook.hpp"
#include "MyFunctions.hpp"
#include <iostream>

// Constructor for GradeBook
GradeBook::GradeBook(const std::string &n) {
	name = MyFunctions::trim(n);
}

// ====== Students

// Returns a vector of pairs that contain student name and ID
void GradeBook::getRoster(std::vector<std::pair<std::string, StudentID>> &list) const {
	list.clear();

	// Loop through roster and add {name, id} pairs to vector
	if (size_t len = m_roster.size()) {
		for (size_t i = 0; i < len; i++) {
			list.emplace_back(m_roster[i].getName(), m_roster[i].getID());
		}
	}
}

// Checks if student exists with studentID
bool GradeBook::studentExists(StudentID id) const {
	if (id == 0) {
		return false;
	}

	// Loop through roster and check if student id matches parameter
	if (size_t len = m_roster.size()) {
		for (size_t i = 0; i < len; ++i) {
			if (m_roster[i].getID() == id) {
				return true;
			}
		}
	}

	return false;
}

// Searches roster for students names containing name and {name, id} pairs to found vector
void GradeBook::findStudent(const std::string &query, std::vector<std::pair<std::string, StudentID>> &found) const {
	found.clear();

	if (!query.length()) {
		return;
	}

	// Loop through roster
	if (size_t len = m_roster.size()) {
		for (size_t i = 0; i < len; ++i) {
			const Student *s = &m_roster[i];
			// If student name contains query
			if (MyFunctions::strContains(s->getName(), query, true) != std::string::npos) {
				// Add them to vector as {name, id} pair
				found.emplace_back(s->getName(), s->getID());
			}
		}
	}
}

// Returns name of student with matching id
std::string GradeBook::getStudentName(StudentID id) const {
	// Loop through roster
	if (size_t len = m_roster.size()) {
		for (size_t i = 0; i < len; ++i) {
			// If student id matches query
			if (m_roster[i].getID() == id) {
				// return student name
				return m_roster[i].getName();
			}
		}
	}

	return std::string("");
}

// Adds student to roster
StudentID GradeBook::addStudent(const std::string &name) {
	std::string newName = MyFunctions::trim(name);

	if (newName.empty()) {
		return 0;
	}

	// If name is not empty, add them to roster
	Student s(name);
	m_roster.push_back(s);
	return s.getID();
}

// Removes student from roster
void GradeBook::removeStudent(StudentID id) {
	// Loop through m_roster
	if (size_t len = m_roster.size()) {
		for (size_t i = 0; i < len; ++i) {
			// if student id matches query
			if (m_roster[i].getID() == id) {
				// remove them from the roster
				m_roster.erase(m_roster.begin() + i);
				return;
			}
		}
	}
}

// Edits name of student
bool GradeBook::editStudentName(StudentID id, const std::string &name) {
	std::string newName = MyFunctions::trim(name);

	if (newName.empty()) {
		return false;
	}

	// Loop through m_roster
	if (size_t len = m_roster.size()) {
		for (size_t i = 0; i < len; ++i) {
			// if student id matches query
			if (m_roster[i].getID() == id) {
				// set their name
				m_roster[i].setName(newName);
				return true;
			}
		}
	}

	return false;
}

// ====== Categories

// Fills vector with {name, weight} pairs of current categories
void GradeBook::getCategories(std::vector<std::pair<std::string, double>> &found) const {
	found.clear();

	// Loop through categories
	if (size_t len = m_categories.size()) {
		const AssignmentCategory *c;
		for (size_t i = 0; i < len; ++i) {
			c = &m_categories[i];
			// add {name, weight} pair to vector
			found.emplace_back(c->getName(), c->getWeight());
		}
	}
}

// Checks if category exists with name
bool GradeBook::categoryExists(const std::string &name) const {
	// Loop through m_categories
	if (size_t len = m_categories.size()) {
		for (size_t i = 0; i < len; ++i) {
			// check if names match (caseless compare)
			if (MyFunctions::strEqual(name, m_categories[i].getName(), true)) {
				return true;
			}
		}
	}
	return false;
}

// Creates a new assignment category
bool GradeBook::createCategory(const std::string &name, double weight) {
	std::string newName = MyFunctions::trim(name);
	
	if (newName.empty() || categoryExists(newName)) {
		return false;
	}

	// If name is valid and category doesnt exist, create it
	m_categories.emplace_back(newName, weight);
	return true;
}

// Removes an assignment category
void GradeBook::removeCategory(const std::string &name) {
	// Loop through categories
	if (size_t len = m_categories.size()) {
		for (size_t i = 0; i < len; ++i) {
			// if names match (caseless compare)
			if (MyFunctions::strEqual(name, m_categories[i].getName(), true)) {
				// remove category from vector
				m_categories.erase(m_categories.begin() + i);
				return;
			}
		}
	}
}

// Edits a categories name;
void GradeBook::editCategoryName(const std::string &name, const std::string &newName) {
	if (name.empty() || newName.empty()) {
		return;
	}

	// Loop through categories
	if (size_t len = m_categories.size()) {
		for (size_t i = 0; i < len; ++i) {
			// if names match (caseless compare)
			if (MyFunctions::strEqual(name, m_categories[i].getName(), true)) {
				// set its name to newname
				m_categories[i].setName(newName);
				return;
			}
		}
	}
}

// Adjusts the weight of a category
void GradeBook::setCategoryWeight(const std::string &name, double weight) {
	// Loop through m_categories
	if (size_t len = m_categories.size()) {
		for (size_t i = 0; i < len; ++i) {
			// if names match (caseless compare)
			if (MyFunctions::strEqual(name, m_categories[i].getName(), true)) {
				// set its weight
				m_categories[i].setWeight(weight);
				return;
			}
		}
	}
}

// ====== Assignments

// Finds category and fills vector with assignment ids that belong to it
void GradeBook::getAssignmentsFromCategory(const std::string &name, std::vector<AssignmentID> &found) const {
	found.clear();

	if (!name.length()) {
		return;
	}

	// Loop through m_categories
	if (size_t len = m_categories.size()) {
		const AssignmentCategory *c;
		for (size_t i = 0; i < len; ++i) {
			c = &m_categories[i];
			if (MyFunctions::strEqual(name, c->getName(), true)) {
				// append assignment ids to end of vector
				found.insert(std::end(found), std::begin(c->assignmentIDs), std::end(c->assignmentIDs));
			}
		}
	}
}

// Fills vector with all assignment ids of assignments that exist
void GradeBook::getAllAssignments(std::vector<AssignmentID> &found) const {
	found.clear();

	// Iterate through map of assignments and add id to vector
	std::map<AssignmentID, Assignment>::const_iterator it;
	for (it = m_assignments.begin(); it != m_assignments.end(); ++it) {
		found.push_back(it->second.getID());
	}
}

// Searches for assignment names containing query and adds their ids to vector
void GradeBook::findAssignment(const std::string &query, std::vector<AssignmentID> &found) const {
	found.clear();

	if (!query.length()) {
		return;
	}

	// Iterate through map of assignments
	std::map<AssignmentID, Assignment>::const_iterator it;
	for (it = m_assignments.begin(); it != m_assignments.end(); ++it) {
		const Assignment *a = &(it->second);
		// if name containts query
		if (MyFunctions::strContains(a->getName(), query, true) != std::string::npos) {
			// add id to the vector
			found.push_back(a->getID());
		}
	}
}

// Checks if assignment exists with id
bool GradeBook::assignmentExists(AssignmentID id) const {
	return m_assignments.find(id) != m_assignments.end();
}

// Gets name and maxpoints of assignment with matching id
void GradeBook::getAssignmentInfo(AssignmentID id, std::string &name, double &maxPoints) const {
	std::map<AssignmentID, Assignment>::const_iterator it = m_assignments.find(id); // would prefer to use `auto it`
	// if assignment found by id
	if (it != m_assignments.end()) {
		// set name and maxpoints by reference
		name = it->second.getName();
		maxPoints = it->second.getMaxPoints();
	}
}

// Creates a new assignment
bool GradeBook::createAssignment(const std::string &category, const std::string &name, double max) {
	std::string newName = MyFunctions::trim(name);

	if (newName.empty()) {
		return false;
	}

	// Loop through categories
	if (size_t len = m_categories.size()) {
		AssignmentCategory *c;
		for (size_t i = 0; i < len; ++i) {
			c = &m_categories[i];
			// if category name matches parameter
			if (MyFunctions::strEqual(category, c->getName(), true)) {
				// get next available id
				AssignmentID id = Assignment::getNextID();
				// push id to assignmentID vector
				c->assignmentIDs.push_back(id);
				// add assignment to map
				m_assignments.emplace(id, Assignment(name, max));
				return true;
			}
		}
	}
	return false;
}

// Removes an existing assignment
void GradeBook::removeAssignment(AssignmentID assignmentID) {
	std::map<AssignmentID, Assignment>::iterator it = m_assignments.find(assignmentID);
	// if the assignment was found, erase it
	if (it != m_assignments.end()) {
		m_assignments.erase(it);
	}
	// otherwise stop
	else {
		return;
	}

	// Loop through categories
	size_t catLen = m_categories.size();
	for (size_t i = 0; i < catLen; ++i) {
		AssignmentCategory *c = &m_categories[i];
		size_t assignLen = c->assignmentIDs.size();
		// Loop through assignmentID vector
		for (size_t j = 0; j < assignLen; ++j) {
			// if id is found
			if (c->assignmentIDs[j] == assignmentID) {
				// remove the id
				c->assignmentIDs.erase(c->assignmentIDs.begin() + j);
				return;
			}
		}
	}
	
}

// Edits assignment name and max points
void GradeBook::editAssignment(AssignmentID assignmentID, const std::string &name, double max) {
	std::map<AssignmentID, Assignment>::iterator it = m_assignments.find(assignmentID);
	if (it != m_assignments.end()) {
		it->second.setName(name);
		it->second.setMaxPoints(max);
	}
}

// ==== Grades

// Checks if a student has a score for an assignment
bool GradeBook::hasScore(AssignmentID assignmentID, StudentID studentID) const {
	std::map<AssignmentID, Assignment>::const_iterator it;
	if ((it = m_assignments.find(assignmentID)) != m_assignments.end()) {
		return it->second.hasScore(studentID);
	}
	return false;
}

// Sets students score for a particular assignment
bool GradeBook::setScore(AssignmentID assignmentID, StudentID studentID, double points) {
	std::map<AssignmentID, Assignment>::iterator it;
	// if student existt and assignment found in map
	if (studentExists(studentID) && (it = m_assignments.find(assignmentID)) != m_assignments.end()) {
		// set students score
		it->second.setScore(studentID, points);
		return true;
	}
	return false;
}

// Retrieves a student score for a particular assignment. If invalid data, returns -1
double GradeBook::getScore(AssignmentID assignmentID, StudentID studentID) const {
	// check for valid student
	if (studentExists(studentID)) {
		std::map<AssignmentID, Assignment>::const_iterator it;
		// if assignment found in map
		if ((it = m_assignments.find(assignmentID)) != m_assignments.end()) {
			// get the students score
			return it->second.getScore(studentID);
		}
	}

	return -1.0f;
}

// Removes a students score for a particular assignment
void GradeBook::removeScore(AssignmentID assignmentID, StudentID studentID) {
	// check for valid student
	if (studentExists(studentID)) {
		std::map<AssignmentID, Assignment>::iterator it;
		// if assignment found in map
		if ((it = m_assignments.find(assignmentID)) != m_assignments.end()) {
			// remove their score
			it->second.removeScore(studentID);
		}
	}
}

// Sets all scores for students in the roster who have not completed a particular assignment to 0.0
void GradeBook::setIncompleteToZero(AssignmentID assignmentID) {
	std::map<AssignmentID, Assignment>::iterator it;
	// if assignment found in map
	if ((it = m_assignments.find(assignmentID)) != m_assignments.end()) {
		Assignment *a = &it->second;
		size_t len = m_roster.size();
		// loop through roster
		for (size_t i = 0; i < len; i++) {
			StudentID id = m_roster[i].getID();
			// if student doesnt have score for assignment
			if (!a->hasScore(id)) {
				// set score to 0.0
				a->setScore(id, 0.0);
			}
		}
	}
}

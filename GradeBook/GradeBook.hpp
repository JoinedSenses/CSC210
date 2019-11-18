#pragma once
#include <cstdint> // uint_t
#include <string>
#include <vector>
#include <map>
#include "Assignment.hpp"
#include "AssignmentCategory.hpp"
#include "Student.hpp"

using StudentID = uint32_t;
using AssignmentID = uint32_t;

class GradeBook {
private:
	std::string name; // Optional name

	std::vector<Student> m_roster; // Vector containing all current students
	std::vector<AssignmentCategory> m_categories; // Vector containing each assignment category
	std::map<AssignmentID, Assignment> m_assignments; // Map containing assignments that can be retrieved by id

public:
	/* Desc: Constructor for GradeBook
	 * Post: Gradebook object created and name set */
	GradeBook(const std::string &name = "");

//==== Student ====
	/* Desc: Returns a vector of {name, id} pairs
	 * Post: List vector has been filled with pairs containing student names and IDs */
	void getRoster(std::vector<std::pair<std::string, StudentID>> &list) const;
	/* Desc: Checks if student exists with studentID
	 * Pre: id is a positive number
	 * Post: Returns true if student exists, else false */
	bool studentExists(StudentID id) const;

	/* Desc: Searches roster for students names containing name and {name, id} pairs to found vector
	 * Post: found vector is fulled with pairs of name and id of students whos names contain */
	void findStudent(const std::string &search, std::vector<std::pair<std::string, StudentID>> &found) const;
	/* Desc: Returns name of student with matching id
	 * Pre: id is valid and positive
	 * Post: Student name has been returned as string */
	std::string getStudentName(StudentID id) const;

	/* Desc: Adds student to roster and returns their id
	 * Pre: name is not empty
	 * Post: Student has been created and added to roster */
	StudentID addStudent(const std::string &name);
	/* Desc: Removes student from roster
	 * Pre: id is valid and positive
	 * Post: Student has been removed from roster */
	void removeStudent(StudentID id);
	/* Desc: Edits name of student
	 * Pre: id is valid and name is not empty
	 * Post: Students name has been changed */
	bool editStudentName(StudentID id, const std::string &newName);

//==== Category ====
	/* Desc: Fills vector with {name, weight} pairs of current categories
	 * Post: vector has been filled with current categories */
	void getCategories(std::vector<std::pair<std::string, double>> &found) const;

	/* Desc: Checks if category exists with name
	 * Post: true if category exists, else false */
	bool categoryExists(const std::string &name) const;

	/* Desc: Creates a new assignment category
	 * Pre: name is not empty and weight is a value on scale of 0.0 to 1.0
	 * Post: category has been created */
	bool createCategory(const std::string &name, double weight);
	/* Desc: Removes an assignment category
	 * Pre: Category with name exists
	 * Post: Category has been removed */
	void removeCategory(const std::string &name);
	/* Desc: Edits a category name
	 * Pre: Name is a valid category name and newName is not empty
	 * Post Category name has been changed */
	void editCategoryName(const std::string &name, const std::string &newName);
	/* Desc: Adjusts the weight of a category
	 * Pre: Category with name exists
	 * Post: Categories weight has been adjusted */
	void setCategoryWeight(const std::string &name, double weight);

//==== Assignment ====
	/* Desc: Finds category and fills vector with assignment ids that belong to it
	 * Pre: Category exists with name
	 * Post: Vector has been filled with assignment ids */
	void getAssignmentsFromCategory(const std::string &name, std::vector<AssignmentID> &found) const;
	/* Desc: Fills vector with all assignment ids of assignments that exist
	 * Post: Vector has been filled with all assignment ids */
	void getAllAssignments(std::vector<AssignmentID> &found) const;

	/* Desc: Searches for assignment names containing query and adds their ids to vector
	 * Pre: name is not empty and contains name of existing assignments
	 * Post: Vector has been filled with assignments whose names contain the query */
	void findAssignment(const std::string &query, std::vector<AssignmentID> &found) const;
	/* Desc: Checks if assignment with id exists
	 * Post: Returns if assignment exists */
	bool assignmentExists(AssignmentID id) const;
	/* Desc: Gets name and maxpoints of assignment with matching id
	 * Pre: id is positive and valid
	 * Post: name and maxpoints has been retrieved and passed by reference */
	void getAssignmentInfo(AssignmentID id, std::string &name, double &maxPoints) const;

	/* Desc: Creates a new assignment
	 * Pre: Category exists and name is not empty
	 * Post: New assignment has been created */
	bool createAssignment(const std::string &category, const std::string &assignmentname, double max = 100.0f);
	/* Desc: Removes a current assignment
	 * Pre: Assignment is positive and valid
	 * Post: Assignment with matching id has been removed */
	void removeAssignment(AssignmentID assignmentID);
	/* Desc: Edits name of assignment
	 * Pre: AssignmentID is positive and valid
	 * Post: Assignment has been renamed */
	void editAssignment(AssignmentID assignmentID, const std::string &name, double max);

//==== Grades ====
	/* Desc: Checks if a student has a score for an assignment
	 * Pre: Assignment and studentID are both positive and valid
	 * Post: True if student has a score, else false */
	bool hasScore(AssignmentID assignmentID, StudentID studentID) const;
	/* Desc: Sets students score for a particular assignment
	 * Pre: ids are positive and valid
	 * Post: Students score has been set */
	bool setScore(AssignmentID assignmentID, StudentID studentID, double points);
	/* Desc: Retrieves a student score for a particular assignment. If invalid data, returns -1
	 * Pre: ids are positive and valid
	 * Post: Student's assignment score has been retrieved */
	double getScore(AssignmentID assignmentID, StudentID studentID) const;
	/* Desc: Removes a students score for a particular assignment
	 * Pre: ids are positive and valid
	 * Post: Students score for the assignment has been removed */
	void removeScore(AssignmentID assignmentID, StudentID studentID);
	/* Desc: Sets all scores for students in the roster who have not completed a particular assignment to 0.0
	 * Pre: Assignment ID is positive and valid
	 * Post: Incomplete assignments have been set to 0.0 */
	void setIncompleteToZero(AssignmentID assignmentID);
};

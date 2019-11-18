/* A program to test and use the features of the gradebook class
 * Currently lacks data retention features. */

#include "GradeBook.hpp"
#include "MyFunctions.hpp"
#include <iostream>
#include <iomanip>

enum {
	EXIT = 0,
	ROSTER,
	CATEGORIES,
	ASSIGNMENTS,
	GRADES
};

int enterMainMenu();
void enterRosterMenu(GradeBook&);
void enterCategoryMenu(GradeBook&);
void enterAssignmentMenu(GradeBook&);
void enterGradeMenu(GradeBook&);

void printGrades(const GradeBook &gb, StudentID studentID);

// Helper functions
void clearcin();
bool promptYesNo();
int promptIntRange(int min, int max);
int promptPositiveInt();
std::string promptLine();

/* Recommended Workflow:
 *  Add categories (Summed weight should be 1.0)
 *  Add assignments to each category
 *  Add students to roster
 *  Set scores
 *  Print grades */

int main() {
	std::cout << "Welcome to your gradebook." << std::endl;

	GradeBook gb("C++ Programming");

	int selection;
	while ((selection = enterMainMenu()) != EXIT) {
		switch (selection) {
		case ROSTER:
			enterRosterMenu(gb);
			break;
		case CATEGORIES:
			enterCategoryMenu(gb);
			break;
		case ASSIGNMENTS:
			enterAssignmentMenu(gb);
			break;
		case GRADES:
			enterGradeMenu(gb);
			break;
		}
		std::cout << std::endl;
	}

	return 0;
}

// Display main menu options
int enterMainMenu() {
	int input;

	std::cout << "Main Menu:\n"
		<< "1. Roster\n"
		<< "2. Categories\n"
		<< "3. Assignments\n"
		<< "4. Grades\n"
		<< "0. Exit" << std::endl;

	return promptIntRange(0, 4);
}

// Display roster options
void enterRosterMenu(GradeBook &gb) {
	int input;
	bool invalid;
	std::vector<std::pair<std::string, StudentID>> students;
	std::string buffer;

	for (;;) {
		std::cout << "\nRoster Menu\n"
			<< "1. View roster\n"
			<< "2. Add student\n"
			<< "3. Remove student\n"
			<< "4. Edit student name\n"
			<< "0. Return to main menu" << std::endl;

		input = promptIntRange(0, 4);
		std::cout << std::endl;

		switch (input) {
		case 0: return; // exit
		case 1: { // view roster
			gb.getRoster(students);

			std::cout << "Roster (Name, ID)" << std::endl;
			// Loop through students, print name and ID
			if (size_t len = students.size()) {
				for (size_t i = 0; i < len; ++i) {
					std::cout << students[i].first << ", "
						<< students[i].second << std::endl;
				}
			}
			else {
				std::cout << "None." << std::endl;
			}

			break;
		}
		case 2: { // add student
			std::cout << "Enter full student name: ";

			buffer = promptLine();

			// Add student and print result
			std::cout << buffer << " added to roster with ID " << gb.addStudent(buffer) << std::endl;

			break;
		}
		case 3: { // remove student
			std::cout << "Enter student id to remove or -1 to exit: ";

			do { // prompt for id until valid or -1
				std::cin >> input; clearcin();
				if (input <= 0 || !gb.studentExists(input)) {
					if (input == -1) break;

					std::cout << "Invalid id." << std::endl;
				}
			} while (input <= 0);
			if (input == -1) break;

			buffer = gb.getStudentName(input);
			std::cout << "Confirm removal of " << buffer << " [Y/N]: ";

			if (promptYesNo()) {
				gb.removeStudent(input);
				std::cout << "Student removed from roster" << std::endl;
			}

			break;
		}
		case 4: { // edit student name
			std::cout << "Enter student id to remove or -1 to exit: ";

			do { // prompt for id until valid or -1
				std::cin >> input; clearcin();
				if (input <= 0 || !gb.studentExists(input)) {
					if (input == -1) break;

					std::cout << "Invalid id." << std::endl;
				}
			} while (input <= 0);
			if (input == -1) break;

			buffer = gb.getStudentName(input);
			std::cout << "Enter new name for student (" << buffer << "): ";

			buffer = promptLine();

			// Change name and output result
			gb.editStudentName(input, buffer);
			std::cout << "Student name changed to " << buffer << std::endl;

			break;
		}
		} // switch (input)
		system("pause");
	} // for (;;)
}

// Display assignment category options
void enterCategoryMenu(GradeBook &gb) {
	int input;
	double weight;
	char c;
	bool invalid;
	std::string buffer, buffer2;
	std::vector<std::pair<std::string, double>> categories;

	for (;;) {
		std::cout << "\nCategory Menu\n"
			<< "1. Display categories\n"
			<< "2. Create category\n"
			<< "3. Remove category\n"
			<< "4. Edit category name\n"
			<< "5. Edit category weight\n"
			<< "0. Return to main menu" << std::endl;

		input = promptIntRange(0, 5);
		std::cout << std::endl;

		switch (input) {
		case 0: return; // exit
		case 1: { // display categories
			gb.getCategories(categories);

			std::cout << "Categories (Name, Weight)" << std::endl;

			// Loop through categories, get name and weight
			if (size_t len = categories.size()) {
				for (size_t i = 0; i < len; ++i) {
					std::cout << categories[i].first << ", "
						<< categories[i].second << std::endl;
				}
			}
			else {
				std::cout << "None." << std::endl;
			}

			break;
		}
		case 2: { // create category
			std::cout << "Enter full category name: ";

			buffer = promptLine();

			if (gb.categoryExists(buffer)) {
				std::cout << "Category " << buffer << " already exists.";
				break;
			}

			std::cout << "Enter category weight as a decimal percentage: ";

			do { // prompt for weight until valid
				std::cin >> weight; clearcin();
				if (weight < 0.0 || weight > 1.0) {
					std::cout << "Invalid. Must be between 0.0 and 1.0" << std::endl;
				}
			} while (weight < 0.0 || weight > 1.0);

			// Create category and output result
			gb.createCategory(buffer, weight);
			std::cout << "Category created: (" << buffer << ", " << weight << ')' << std::endl;

			break;
		}
		case 3: { // remove category
			std::cout << "Enter full category name: ";

			buffer = promptLine();

			if (gb.categoryExists(buffer)) {
				std::cout << "Confirm removal of " << buffer << " [Y/N]: ";

				if (promptYesNo()) {
					gb.removeCategory(buffer);
					std::cout << "Category removed." << std::endl;
				}
			}
			else {
				std::cout << "Category does not exist by that name." << std::endl;
			}

			break;
		}
		case 4: { // edit category name
			std::cout << "Enter full name of category to rename: ";

			buffer = promptLine();

			if (gb.categoryExists(buffer)) {
				std::cout << "Enter new name of category: ";

				buffer2 = promptLine();

				// Edit and output result
				gb.editCategoryName(buffer, buffer2);
				std::cout << "Category has been renamed." << std::endl;
			}
			else {
				std::cout << "Category does not exist." << std::endl;
			}

			break;
		}
		case 5: { // edit category weight
			std::cout << "Enter full name of category to edit: ";

			buffer = promptLine();

			if (gb.categoryExists(buffer)) {
				std::cout << "Enter new weight of category: ";

				do { // prompt for weight until valid
					std::cin >> weight; clearcin();
					if (weight < 0.0 || weight > 1.0) {
						std::cout << "Invalid. Must be between 0.0 and 1.0" << std::endl;
					}
				} while (weight < 0.0 || weight > 1.0);

				// Change weight and output result
				gb.setCategoryWeight(buffer, weight);
				std::cout << "Category weight has been adjusted." << std::endl;
			}
			else {
				std::cout << "Category does not exist." << std::endl;
			}

			break;
		}
		} // switch (input)
		system("pause");
	} // for (;;)
}

// display assignment options
void enterAssignmentMenu(GradeBook &gb) {
	long int input;
	bool invalid;
	std::string buffer;
	double maxPoints;
	std::vector<AssignmentID> assignments;

	for (;;) {
		std::cout << "\nAssignment Menu\n"
			<< "1. Display all assignments\n"
			<< "2. Display assignments for a category\n"
			<< "3. Create assignments for a category\n"
			<< "4. Remove assignment\n"
			<< "5. Edit assignment name\n"
			<< "6. Edit assignment max points\n"
			<< "0. Return to main menu" << std::endl;

		input = promptIntRange(0, 6);
		std::cout << std::endl;

		switch (input) {
		case 0: return; // exit
		case 1: { // display all
			gb.getAllAssignments(assignments);

			std::cout << "Assignments (Name, ID, MaxPoints)" << std::endl;

			if (size_t len = assignments.size()) {
				// Loop through each assignment and output info
				for (size_t i = 0; i < len; ++i) {
					gb.getAssignmentInfo(assignments[i], buffer, maxPoints);

					std::cout << buffer << ", "
						<< assignments[i] << ", "
						<< maxPoints << std::endl;
				}
			}
			else {
				std::cout << "None." << std::endl;
			}

			break;
		}
		case 2: { // display category
			std::cout << "Enter category name: ";

			buffer = promptLine();

			if (gb.categoryExists(buffer)) {
				gb.getAssignmentsFromCategory(buffer, assignments);

				std::cout << "Assignments (Name, ID, MaxPoints)" << std::endl;

				if (size_t len = assignments.size()) {
					// Loop through each assignment for category and display info
					for (size_t i = 0; i < len; ++i) {
						gb.getAssignmentInfo(assignments[i], buffer, maxPoints);

						std::cout << buffer << ", "
							<< assignments[i] << ", "
							<< maxPoints << std::endl;
					}
				}
				else {
					std::cout << "None." << std::endl;
				}
			}
			else {
				std::cout << "Category does not exist." << std::endl;
			}

			break;
		}
		case 3: { // create
			std::cout << "Enter category to create assignment for: ";

			buffer = promptLine();

			if (!gb.categoryExists(buffer)) {
				std::cout << "Category does not exist." << std::endl;
				break;
			}

			std::string cat = buffer;

			do {
				std::cout << "Enter name for new assignment or 0 to go back: ";

				buffer = promptLine();

				if (buffer != "0") {

					std::cout << "Enter max points for assignment: ";

					do { // prompt for points until valid
						std::cin >> maxPoints; clearcin();
						if (maxPoints < 0.0) {
							std::cout << "Max points must be positive" << std::endl;
						}
					} while (maxPoints < 0.0);

					// Create assignment and output results
					gb.createAssignment(cat, buffer, maxPoints);
					std::cout << "Assignment created.\n" << std::endl;
				}

			} while (buffer != "0");

			break;
		}
		case 4: { // remove
			std::cout << "Enter ID of assignment to remove: ";

			input = promptPositiveInt();

			if (gb.assignmentExists(input)) {
				std::cout << "Confirm removal of assignment [Y/N]: ";

				if (promptYesNo()) {
					gb.removeAssignment(input);
					std::cout << "Assignment removed" << std::endl;
				}
			}
			else {
				std::cout << "Assignment does not exist." << std::endl;
			}

			break;
		}
		case 5: { // edit name
			std::cout << "Enter ID of assignment to rename: ";

			input = promptPositiveInt();

			if (gb.assignmentExists(input)) {
				std::cout << "Enter new name for assignment or 0 to return: ";

				buffer = promptLine();
				if (buffer == "0") break;

				// Update name and output result
				std::string name = buffer;
				gb.getAssignmentInfo(input, buffer, maxPoints);
				gb.editAssignment(input, name, maxPoints);
				std::cout << "Assignment has been updated." << std::endl;
			}
			else {
				std::cout << "Assignment does not exist." << std::endl;
			}

			break;
		}
		case 6: { // edit max points
			std::cout << "Enter ID of assignment to edit: ";

			input = promptPositiveInt();

			if (gb.assignmentExists(input)) {
				std::cout << "Enter new max points for assignment or a negative value to return: ";
				// Get max points or return if negative
				std::cin >> maxPoints; clearcin();
				if (maxPoints < 0) break;

				// Update points and output result
				double trash;
				gb.getAssignmentInfo(input, buffer, trash);
				gb.editAssignment(input, buffer, maxPoints);
				std::cout << "Assignment has been updated." << std::endl;
			}
			else {
				std::cout << "Assignment does not exist." << std::endl;
			}

			break;
		}
		} // switch (input)
		system("pause");
	} // for (;;)
}

// display grading options
void enterGradeMenu(GradeBook &gb) {
	int input;
	double points;
	char c;

	for (;;) {
		std::cout << "\nGrade Menu\n"
			<< "1. Display student's grades\n"
			<< "2. Set a student's points for an assignment\n"
			<< "3. Remove a students points for an assignment\n"
			<< "4. Set all incomplete scores for an assignment to 0\n"
			<< "0. Return to main menu" << std::endl;

		input = promptIntRange(0, 4);
		std::cout << std::endl;

		switch (input) {
		case 0: return; // main menu
		case 1: { // display grades
			std::cout << "Enter student ID: ";

			// Get valid id and print grades
			std::cin >> input; clearcin();
			if (!gb.studentExists(input)) {
				std::cout << "Invalid id." << std::endl;
				break;
			}

			printGrades(gb, input);

			break;
		}
		case 2: { // set score
			std::cout << "Enter student ID: ";
			std::cin >> input; clearcin();

			if (input < 1 || !gb.studentExists(input)) {
				std::cout << "Invalid id." << std::endl;
				break;
			}

			StudentID studentID = input;

			std::cout << "Enter assignment ID: ";
			std::cin >> input; clearcin();

			if (input < 1 || !gb.assignmentExists(input)) {
				std::cout << "Invalid id." << std::endl;
				break;
			}

			AssignmentID assignmentID = input;

			std::string name;
			double max;

			gb.getAssignmentInfo(assignmentID, name, max);
			std::cout << name << " (Max: " << max << ")\nEnter number of points: ";

			do { // prompt for points until valid
				std::cin >> points; clearcin();
				if (points < 0.0) {
					std::cout << "Must be a non-negative value." << std::endl;
				}
			} while (points < 0.0);

			// Set student score for assignment and output results
			gb.setScore(assignmentID, studentID, points);
			std::cout << "Score has been set." << std::endl;

			break;
		}
		case 3: { // remove score
			std::cout << "Enter student ID: ";
			std::cin >> input; clearcin();

			if (input < 1 || !gb.studentExists(input)) {
				std::cout << "Invalid id." << std::endl;
				break;
			}

			StudentID studentID = input;

			std::cout << "Enter assignment ID: ";
			std::cin >> input; clearcin();

			if (input < 1 || !gb.assignmentExists(input)) {
				std::cout << "Invalid id." << std::endl;
				break;
			}

			AssignmentID assignmentID = input;

			std::string name;
			double max;

			gb.getAssignmentInfo(assignmentID, name, max);
			std::cout << name << "\nConfirm removal [Y/N]: ";

			if (promptYesNo()) {
				gb.removeScore(assignmentID, studentID);
				std::cout << "Score has been removed.";
			}

			break;
		}
		case 4: {// set incomplete
			std::cout << "Enter assignment ID: ";
			std::cin >> input; clearcin();

			if (input < 1 || !gb.assignmentExists(input)) {
				std::cout << "Invalid id." << std::endl;
				break;
			}

			std::string name;
			double max;

			gb.getAssignmentInfo(input, name, max);
			std::cout << name << "\nConfirm setting incomplete scores to 0 [Y/N]: ";

			if (promptYesNo()) {
				gb.setIncompleteToZero(input);
				std::cout << "Scores set to 0 for incomplete." << std::endl;
			}

			break;
		}
		}
		system("pause");
	} // for (;;)
}

// Displays information about a students grades
void printGrades(const GradeBook &gb, StudentID studentID) {
	if (!gb.studentExists(studentID)) {
		std::cout << "Invalid student" << std::endl;
	}

	/* -- Pseudocode minus console output -- */
	// declare overallfinal, overallrunning

	// for each category
		// declare catfinal, catrunning
		// get category weight
		// get assignment count

		// for each assignment
			// get assignment max points
			// if student has a score
				// get their score
				// increment complete count
				// add score to running score

		// catfinal = catrunning / assignmentCount
		// catrunning /= completedCount

		// overallfinal += catfinal * catweight
		// overallrunning += catrunning * catweight

	std::cout << std::fixed << std::setprecision(2);

	std::vector<std::pair<std::string, double>> categories;
	gb.getCategories(categories);

	double overallFinal = 0.0;
	double overallRunning = 0.0;

	size_t catCount = categories.size();
	for (size_t i = 0; i < catCount; ++i) {
		std::string catName = categories[i].first;
		double catWeight = categories[i].second;

		double catFinal = 0.0;
		double catRunning = 0.0;

		std::vector<AssignmentID> assignments;
		gb.getAssignmentsFromCategory(catName, assignments);

		size_t completedAssignmentCount = 0;

		std::cout << "\nCategory: " << catName << ", Weight: " << catWeight << std::endl;
		size_t assignmentCount = assignments.size();
		for (size_t j = 0; j < assignmentCount; ++j) {
			AssignmentID assignmentID = assignments[j];

			std::string assignmentName;
			double assignmentMaxPoints;
			double studentPoints;

			gb.getAssignmentInfo(assignmentID, assignmentName, assignmentMaxPoints);
			
			std::cout << "Assignment: " << assignmentID << ' ' << assignmentName
				<< "\n  Score: ";
			if (gb.hasScore(assignmentID, studentID)) {
				studentPoints = gb.getScore(assignmentID, studentID);
				++completedAssignmentCount;
				catRunning += studentPoints / assignmentMaxPoints * 100.0;

				std::cout << studentPoints / assignmentMaxPoints
					<< " (" << studentPoints << '/' << assignmentMaxPoints << ')' << std::endl;
			}
			else {
				std::cout << "None" << std::endl;
			}
		}

		if (catRunning) {
			catFinal = catRunning / assignmentCount;
			catRunning /= completedAssignmentCount;

			overallFinal += catFinal * catWeight;
			overallRunning += catRunning * catWeight;
		}

		std::cout << "Category running: " << catRunning
			<< "\nCategory current final: " << catFinal << std::endl;
	}

	std::cout << "\nOverall running: " << overallRunning
		<< "\nOverall current final: " << overallFinal << std::endl << std::endl;
}

// Clears input buffer for input control
void clearcin() {
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

bool promptYesNo() {
	char c;
	do {
		std::cin >> c; clearcin();
		c = MyFunctions::toLower(c);
	} while (c != 'y' && c != 'n');
	return c == 'y';
}

int promptPositiveInt() {
	int input;
	do {
		std::cin >> input; clearcin();
		if (input < 1) {
			std::cout << "Must be positive value.";
		}
	} while (input < 1);
	return input;
}

int promptIntRange(int min, int max) {
	int input;
	do {
		std::cin >> input; clearcin();
	} while (input < min || max < input);
	return input;
}

std::string promptLine() {
	std::string buffer;
	do {
		std::getline(std::cin, buffer);
		buffer = MyFunctions::trim(buffer);
	} while (buffer.empty());
	return buffer;
}
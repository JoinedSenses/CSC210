/*
 * Program Name: Dice Roller
 * Description: Allows user to roll multiple dice of their choosing
 * Programmer: Arron Vinyard
 * Last Edit: 2019.08.31
 */

#include "diceType.h"
#include <iostream>
#include <vector>

// Clears cin buffer and ignores until newline to control input
void clearcin() {
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

int main(void) {
	std::vector<DiceType> dice;
	bool invalid = false;
	size_t count = 0;
	int input;

	std::cout << "This program rolls dice!\n" << std::endl;

	// Run until exit or close.
	do {
		// Prompt user with menu options
		std::cout << "Select an option:"
			<< "\n0. Exit"
			<< "\n1. Choose new dice to roll." << std::endl;
		if (count) { // If they have already chosen dice, prompt for roll
			std::cout << "2. Roll " << count << (count > 1 ? " dice" : " die") << ":\n   ";

			// Display each die, 5 per line
			for (size_t i = 0; i < count; ++i) {
				std::cout << 'D' << dice[i].getSides() << ' ';
				if (i % 5 == 4) {
					std::cout << "\n   ";
				}
			}

			std::cout << std::endl;
		}

		do { // Loop until valid input
			std::cin >> input; clearcin();
		} while (input < 0 || input > (count ? 2 : 1));

		std::cout << std::endl;

		switch (input) {
		case 1: // Choose new dice
			do { // Prompt for die count
				invalid = false;

				std::cout << "Enter number of die: ";
				std::cin >> input; clearcin();

				if (input < 1) {
					invalid = true;
					std::cout << "Input must be greater than 0." << std::endl;
				}
			} while (invalid);

			count = input;
			dice.clear();

			// Loop through each die, set sides, push to vector
			for (size_t i = 0; i < count; ++i) {
				do {
					invalid = false;

					std::cout << "#" << i + 1 << ". Enter number of sides: ";
					std::cin >> input; clearcin();

					if (input < 1) {
						invalid = true;
						std::cout << "Input must be greater than 0." << std::endl;
					}
				} while (invalid);

				dice.emplace_back(input);
			}

			std::cout << std::endl;
			break;

		case 2: // Roll current die
			// Loop through each die, roll, and output result
			for (size_t i = 0; i < count; ++i) {
				std::cout << "#" << i + 1 << " D" << dice[i].getSides()
					<< ": Rolled a " << dice[i].roll() << "!\n";
			}

			std::cout << std::endl;
			system("pause"); // Pause to give user a chance to see results.
			break;
		}
	} while (input);

	return 0;
}

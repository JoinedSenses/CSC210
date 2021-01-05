#include "diceType.h"
#include <numeric> // srand() and rand()
#include <ctime> // time()

/* Desc: Constructs diceType
 * Pre: s is a valid unsigned int or empty (default: 6)
 * Post: sides initialized to s and value initialized to 0 */
DiceType::DiceType(unsigned int s) {
	sides = s;
	value = 0;
}

/* Desc: Sets the numer of die sides to s
 * Pre: s is a valid unsigned int
 * Post: sides has been modified and is positive */
void DiceType::setSides(unsigned int s) {
	sides = s;
}

/* Desc: Returns the number of die sides
 * Pre: Sides initialized through constructor or setSides()
 * Post: Returns number of die sides */
int DiceType::getSides(void) const {
	return sides;
}

/* Desc: Returns value from last roll; 
 * Pre: Die has been rolled
 * Post: Returns last roll value */
int DiceType::getRoll(void) const {
	return value;
}

/* Desc: Rolls the die.
 * Pre: None
 * Post: Returns and sets roll value */
int DiceType::roll(void) const {
	// Set random seed once based on time.
	static bool set = false;
	if (!set) { srand(time(0)); set = true; }

	// Generate random roll
	return value = rand() % sides + 1;
}
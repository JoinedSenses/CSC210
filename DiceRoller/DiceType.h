#pragma once

class DiceType {
private:
	unsigned int sides; // side count
	mutable unsigned int value; // last roll value;
public:
	DiceType(unsigned int s = 6);
	void setSides(unsigned int s);
	int getSides(void) const;
	int getRoll(void) const;
	int roll(void) const;
};
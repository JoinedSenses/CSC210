/* BigIntTester
 * A program to test features of the BigInt class */

#include <iostream>
#include <string>
#include <limits.h> /* INT_MAX */
#include <exception>
#include "BigInt.hpp"

using namespace std;

int main(void) {
	BigInt arr[] = { -100, 150, 100, -150 };


	for (size_t i = 0; i < sizeof arr / sizeof arr[0]; ++i) {
		for (size_t j = 0; j < sizeof arr / sizeof arr[0]; ++j) {
			cout << '(' << i << ',' << j << ')' << endl; // Display index

			// Output compare result
			cout << arr[i] << " is ";
			switch (arr[i].compare(arr[j])) {
			case -1: cout << "less than "; break;
			case 0: cout << "equal to "; break;
			case 1: cout << "greater than "; break;
			}
			cout << arr[j] << endl;

			// Output addition and subtraction
			cout << arr[i] << " + " << arr[j] << " = " << arr[i] + arr[j] << endl;
			cout << arr[i] << " - " << arr[j] << " = " << arr[i] - arr[j] << endl << endl;
		}
	}

	// Output addition/subtraction assignment
	cout << (BigInt(10) += 5) << endl; // 15
	cout << (BigInt(10) -= 5) << endl; // 5

	cout << endl;

	// Work with some really big numbers and show results for each operation
	BigInt e("-1231023850234534630463482374082730840700823482156342346575544530001230980121241952509120396794579347945898457");
	BigInt f("23452345234523452672457022402343457349829348887857684586");

	BigInt result;

	result = e + f;
	cout << (result == BigInt("-1231023850234534630463482374082730840700823482156342323123199295477778307664219550165663046965230460088213871")) << ' ' << result << endl;

	result = e - f;
	cout << (result == BigInt("-1231023850234534630463482374082730840700823482156342370027889764524683652578264354852577746623928235803583043")) << ' ' << result << endl;

	result = -e + f;
	cout << (result == BigInt("1231023850234534630463482374082730840700823482156342370027889764524683652578264354852577746623928235803583043")) << ' ' << result << endl;

	result = -e - f;
	cout << (result == BigInt("1231023850234534630463482374082730840700823482156342323123199295477778307664219550165663046965230460088213871")) << ' ' << result << endl;


	cout << endl << (result = BigInt("100000000000000000000000000000000000000000000000000") - BigInt("99999999999999999999999999999999999999999999999999")) << endl; // 1
	cout << result++ << endl; // 1 (Post Incr);
	cout << ++result << endl; // 3 (Pre Inc)
	cout << endl;

	// Test input
	cout << endl << "Enter a value to test BigInt input: ";
	while (!(cin >> result)) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid input. Try again: ";
	}
	cout << "Result: " << result << endl << endl;

	// Test invalid string throw with try/catch
	try {
		BigInt thisWillThrow("abc");
	}
	catch (exception &e) {
		cout << "Purposefully threw exception: " << e.what();
	}
	cout << endl;

	return 0;
}

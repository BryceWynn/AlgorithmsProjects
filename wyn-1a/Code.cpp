/*constructor for the code class
code class stores the user guess, as well as creates and stores the master value
also handles checking the user input value to the master guess
BW, 19SEP16
*/

#include "Code.h"
#include <vector>
#include <string>
#include <iostream>
#define SEED 12

using namespace std;
Code::Code() {

}

Code::Code(vector<int> userInput) {
	// creates the user input code from the user input vector
	// copies the terms one at a time
	// exception handling happens in the uyser input stage in main

	for (int x = 0; x < PASSCODELENGTH; x++) {
		if (generatedCode.size() != PASSCODELENGTH) {
			generatedCode.push_back(userInput.at(x));
		}
		else generatedCode.at(x) = userInput.at(x);
	}
}
void Code::secretCode() {
	// function to create secret password
	//for loop creates random value from 0  to PASSCODERANGE
	// repeats process for PASSCODELENGTH
	// SEED used to determine seed for random number, currently hardcoded as a constant
	
	srand(SEED);
	for (int y = 0; y< PASSCODELENGTH; y++) {
		generatedCode.push_back((rand() % PASSCODERANGE));
		std::cout << generatedCode.at(y) << ", "; // prints secret code
	}
	std::cout << "\n"; // adds an llinebreak after printing the code
}

int Code::checkCorrect(Code &passedCode) {
	// function to check for values in the correct place and location
	// compares the user input vector to the secret code and returns accordingly
	// uses constant PASSCODELENGTH instead of sizing the vector to save computations	
	correct = 0; // counter for number of correct numbers
				 //loops through both vectors simultaneously to compare values in same place
	for (int x = 0; x < PASSCODELENGTH; x++) { //
		if (generatedCode.at(x) == passedCode.generatedCode.at(x)) correct++;
	}
	return(correct);
}
// creates a copy of the passCode to check against user input values			
// alters the copy of the passcode to ensure that no value is counted twice
int Code::checkIncorrect(Code &passedCode) {
	incorrect = 0;

	int w = 0; // needed because every value of passcode must be checked against z
	bool resetW = false;
			   // for loop ensures that all of z is searched through, even though z is never directly incremented
			   // if an incorrectly located value is found, or if all of passCode copy is searched, z is incremented
			   // repeats until all z terms have been searched
	
	// first for loop ensures that no correct answers are interpreted as incorrect answers
	for  (int x = 0; x < PASSCODELENGTH; x++){
		if (generatedCode.at(x) == passedCode.generatedCode.at(x)) passedCode.generatedCode.at(x) = PASSCODERANGE + 1;
	}
	// next loop searches all values for similar numbers in disimalr spaces
	
	for (int z = 0; z < PASSCODELENGTH; w++) {
		// resetW used due to w always incrementing to at least 1 at the start of the loop
		if (resetW == true) {
			w = 0;
			 resetW = false;
		}

		if (generatedCode.at(z) == passedCode.generatedCode.at(w)) {
			if (w != z) { // makes sure value isn't in correct place as well as value
				passedCode.generatedCode.at(w) = PASSCODERANGE + 1; // ensures this value can never be considered true again
				resetW = true; // sets w to 0 on next loop
				z++; // increments z
				incorrect++; // increments correct
				w = 0;
			}
		}
		else if (w >= PASSCODELENGTH-1) { // if none of the code values matched the passcode
			resetW = true;
			z++;
		}
	}

	return(incorrect); // returns final values
}

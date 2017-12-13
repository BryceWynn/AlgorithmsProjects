/*
class mastermind controls all necessary functions to run the game mastermind
dependent on both Code.h and response.h
handles functions for user input, and rules for the game
also handles checking to see if the user has succesfully guessed the passcode
BW 19SEP16
*/


#include "Mastermind.h"
#include <vector>
#include "d_except.h"
#include "Code.h"

using namespace std;
Code Mastermind::humanGuess() {
	// read user value in and then creates a code with that value as the stored vector
	// first announce to user what is needed
	cout << "please enter your guess of a passcode that is " << PASSCODELENGTH
		<< " numbers long and goes from 0 to " << (PASSCODERANGE - 1)
		<< "\n Numbers should be seperated by an enter command. \n";
	vector<int> userInput; // initalize vector used for user input
	int number = 0;
	while (userInput.size() < PASSCODELENGTH) { // using while loop for this ensures the proper number of charecters are read in
		cin >> number;
		if (number >= PASSCODERANGE || number < 0) throw rangeError("input value is outisde of code range");
		else userInput.push_back(number);
	}
	// no throw for too many terms because loop ensures 4 terms are submitted
	Code currentGuess(userInput);
	return(currentGuess);
}

Response Mastermind::getResponse(Code code1, Code code2) {
// takes two codes and creates a response data type for how many correct numbers were entered
// uses the built in code functions to produce the data and then creates and returns a resonse data type	
	int correct = 0;
	int  incorrect = 0;
	correct = code1.checkCorrect(code2);
	incorrect = code1.checkIncorrect(code2);
	Response currentResponse;
	//lastResponse = currentResponse;
	currentResponse.changeValues(correct, incorrect);
	return(currentResponse);
}

void Mastermind::playGame() {
	// handles all the rules of gameplay
	Code passCode; // creates code datatype for secret code
	passCode.secretCode(); // generates passcode
	for (int x = 0; x < NUMBEROFGUESSES; x++) { // sets maximum number of attempts for user
		try {
			currentResponse = getResponse(humanGuess(), passCode); // inside try function to ensure user entry is within bounds
		}
		catch (rangeError &ex) { // error handler
			cout << " exception error: ";
			cerr << ex.what() << endl;
		}
		if (isSolved(currentResponse) == true) { // checks to see if correct answers == possible correct answers and triggers winstate
			cout << "you Guessed the Code \n \n";
			return;
		}
		currentResponse.printResponse(); // prints number of correct and incorrect answers
		x++;
	}
	cout << "You Failed to Guess the code"; // if the user uses more attempts than number of guesses end the game
	return;


}

bool Mastermind::isSolved(Response &currentResponse) {
	//checks to see if user  has won the game
	return (currentResponse.returnCorrect() == PASSCODELENGTH);
}
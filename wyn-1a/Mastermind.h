#pragma once
#include "Response.h" // response.h includes code.h, so code.h not included here
#include "Code.h"

#define NUMBEROFGUESSES 10 // sets maximmum number of guesses before "codemaker" wins

class Mastermind {
public:
	Mastermind() {};
	Code userGuess;
	Code humanGuess();
	Response getResponse(Code code1, Code code2);
	bool isSolved(Response &response);
	void playGame();

private:
	int correct = 0;
	int incorrect = 0;
	Response lastResponse;
	Response currentResponse;
};
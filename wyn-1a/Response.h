// class response used for mastermind games
// stores correct and incorrect guesses as well as printing them
// also stores a command to compare responses that is never used
// BW 19SEP16

#pragma once
#include <iostream>

using namespace std;
class Response {
public:
	Response() {}; // bare constructor
	Response(int numberCorrect, int numberIncorrect) {//constructor when given values
		correct = numberCorrect;
		incorrect = numberIncorrect;
	}
	void printResponse() { //output of both values
		cout << correct << " Numbers are correct and properly postioned, "
			<< incorrect << " Numbers are correct and in the improper position \n";
	}

	bool checkSame (Response const &response1, Response const &response2) {
		return (response1.correct == response2.correct
			&& response1.incorrect == response2.correct);
	}

	void changeValues(const int &newCorrect, const int &newIncorrect) {
		correct = newCorrect;
		incorrect = newIncorrect;
	}

	int returnCorrect() {
		return(correct);
	}

private:
	int correct, incorrect;
};
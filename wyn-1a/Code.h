#pragma once
#include <vector>
#define PASSCODELENGTH 4 // number of terms in passcode
#define PASSCODERANGE 5 // number of terms possible in passcode, including 0 (ex 5 means 0-4 possible)

using namespace std;

class Code {
public:
	Code();
	Code(vector<int> userInput);
	void secretCode();
	int checkCorrect(Code &passedCode);
	int checkIncorrect(Code &hiddenCode);


private:
	vector<int> generatedCode;
	int correct = 0;
	int incorrect = 0;
};


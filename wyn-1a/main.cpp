// contains a file type mastermind and runs play game to execute the program
// also contains getchar() in order to hold screen on victory or defeat scenes after playing
// created using microsoft visual studio on windows 10

#include "stdafx.h"
#include "Code.h"
#include <iostream>
#include "Response.h"
#include "Mastermind.h"

int main()
{
	Mastermind m;
	m.playGame();
	getchar();
    return 0;
}


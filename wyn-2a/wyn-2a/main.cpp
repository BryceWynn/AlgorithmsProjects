/* function to run Deck and Card
*  Currently only creates a linked list of 1 standard deck and then prints using Deck function and prints using overloaded operator
* no exception class is included due to no user input being used in the function
* BW 26Sep16
*/ 


#include "Deck.h"

int main()
{
	Deck gameDeck(NUMBEROFDECKS); // NUMBERDECKS defined as int 1
	gameDeck.cardPrinter();
	getchar();
    return 0;
}


/* function to run Deck and Card
*  Currently only creates a linked list of 1 standard deck and then prints using Deck function and prints using overloaded operator
* no exception class is included due to no user input being used in the function
* BW 26Sep16
*
*Modified for project 2b
*deck printer is no loner used, game is now played based on global function playgame
*Also includes all other listed changes in Deck and Card header files
*BW 03OCT16
*/


#include "Deck.h"
#include "d_except.h"
using namespace std;

int score = 0; // score to be reported;

void playGame(Deck &deckForGame) {
	int * scorePtr = &score; // used to save time with scoring function
	int userInput = 1; // set to 1 so game enters feedback loop first time through the code
	int deltCards = 0; // tracks total cards delt
	char number;
	char suit;
	Card deltCard;
	deckForGame.shuffle();
	cout << "welcome to flipPlayer" << endl << endl;
	cout << "to play, flip over cards and try to get a hi-score" << endl;
	cout << "you get 10 points for an Ace, and 5 for a face Card" << endl;
	cout << "you lose half your points for a 7, and all of your points for 2-6" << endl;
	cout << "you also get one extra point for a heart" << endl << endl << endl;
	cout << "type a 0 then press enter to deal a card, or enter a 1 to stop" << endl;
	cout << " your first card will be dealt at the start of the game" << endl;
	while (userInput == 1) {
		deltCards++;
		deltCard = deckForGame.deal();
		number = deltCard.number;
		suit = deltCard.suit;
		cout << " the top Card was a  " << number << "of " << suit << endl;
		if (number == 'A') score = score + 10;
		else if (number == 'K' || number == 'Q' || number == 'J') score = score + 5;
		else if (number == '7') score = floor((score) / 2);
		else if (number == '8' || number == '9' || number == 'T');
		else score = 0;
		if (suit == 'H') (score)++;
		cout << "this makes your Score " << score << endl;
		cin >> userInput;
		if (deltCards >= NUMBEROFDECKS*NUMBERSUITS*NUMBERCARDS) throw rangeError("Deck is out of cards");
		if (userInput != 1) {
			if (userInput != 0) {
				cout << endl;
				throw rangeError("Input was not either a 1 or a 0");
			}
		}
	}
}


int main()
{
	Deck gameDeck(NUMBEROFDECKS); // NUMBERDECKS defined as int 1
	try {
		playGame(gameDeck);
	}
	catch (rangeError &ex) {
		cout << "except error" << endl;
		cerr << ex.what() << endl << endl;
	}
	cout << "your final score is " << score << endl;
	getchar();
	return 0;
}






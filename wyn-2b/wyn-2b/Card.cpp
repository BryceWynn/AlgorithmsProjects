/*Card Class Functions for Flip card Game
* contains the constructors and destructors for the Card class used for linked lists
*also overloads the output operator (<<) to create an easier way to print ccard values
*contains set and get functions due to that being specified in project requirements
* - These are not used due to the values being public for linked lists
*BW 26SEP16
*
*copy constructor and overloaded assignment operator added
*BW 03OCT16
*/



#include "card.h"
#pragma once
using namespace std;

Card::Card() {

}

// primary constructor, passed suit and number value and creates card w/ null pointer
Card::Card(char &cardNumber, char &cardSuit) {
	suit = cardSuit;// sets values to thesuit
	number = cardNumber; // sets value to the number
	nextCard = nullptr; // initalizes the pointer null
}

// copy constructor, makes identical version of card including the ptr
Card::Card(const Card &cardToCopy):suit(cardToCopy.suit), number(cardToCopy.number),nextCard(cardToCopy.nextCard) {}

// get function for card ptr, not used due to ptr being public
Card* Card::getCardPtr() {
	return (nextCard);
}
// set function for the number of the card, not used due to class info being public
void Card::setNumber(char &changeNumber) {
	number = changeNumber;
}

// set function for the ptr of the card, not used due to class info being public
void Card::setPtr(Card *cardPtr) {
	nextCard = cardPtr;
}

// get function for the suit of the card, not used due to class info being public
void Card::setSuit(char &changeSuit) {
	suit = changeSuit;
}

// get function for the number of the card, not used due to class info being public
char Card::getNumber() {
	return (number);
}

//overload for cout function
ostream& operator<< (ostream& ostr, const Card &cardPtr) {
	ostr << cardPtr.suit << " " << cardPtr.number << endl; // prints the data stored in the card
	return ostr; // returns
}

// overloaded assignment operator of the function
void Card::operator= (const Card &cardToCopy) { // takes the passed card
	suit = cardToCopy.suit; // sets the suit equal to passed card suit
	number = cardToCopy.number; // sets the number equal to the passed cards number
	nextCard = nullptr; // initalizes the new cards ptr as null
}

//get  function for suit of card, not used due to suit being public
char Card::getSuit() {
	return (suit);
}


/*Card Class Functions for Flip card Game
* contains the constructors and destructors for the Card class used for linked lists
*also overloads the output operator (<<) to create an easier way to print ccard values
*contains set and get functions due to that being specified in project requirements
* - These are not used due to the values being public for linked lists
*/



#include "card.h"
#pragma once
using namespace std;

Card::Card() {

}

Card::~Card() {
	delete nextCard;
}

// primary constructor
Card::Card(char &cardNumber, char &cardSuit) {
	suit = cardSuit;// sets values to thesuit
	number = cardNumber; // sets value to the number
	nextCard = nullptr; // initalizes the pointer null
}

void Card::newCard(char &newNumber, char &newSuit) {
	nextCard = &Card(newNumber, newSuit); 
}

Card* Card::getCardPtr() {
	return (nextCard);
}

void Card::setNumber(char &changeNumber) {
	number = changeNumber;
}

void Card::setPtr(Card *cardPtr) {
	nextCard = cardPtr;
}

void Card::setSuit(char &changeSuit) {
	suit = changeSuit;
}

char Card::getNumber() {
	return (number);
}

//overload for cout function
ostream& operator<< (ostream& ostr, const Card &cardPtr) {
	ostr << cardPtr.suit << " " << cardPtr.number << endl; // prints the data stored in the card
	return ostr;
}


char Card::getSuit() {
	return (suit);
}


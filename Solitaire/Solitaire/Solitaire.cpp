﻿// Solitaire.cpp by Tyler Schacht
// 
// Purpose: To practice C++ fundamentals
// I know it is bad practice to have everything in one file
// but.. as stated this is just to reteach myself C++
//

#include <iostream>
#include <vector>
#include <random>
using namespace std;

class Card {
	private:
        int rank;
        char suit;
		bool isRed;
		bool faceUp;
		
	public:
		Card (int _rank = 1, char _suit = 'S') {
			rank = _rank;
			suit = _suit;
			if (suit > 90)
				suit -= 32;
			faceUp = false;
		}
		int getRank() {
			return rank;
		}
		char getSuit() {
			return suit;
		}
		bool isFaceUp() {
			return faceUp;
		}
		void setRank(int _rank) {
			rank = _rank;
		}
		void setSuit(char _suit) {
			suit = _suit;
			if (suit > 90)
				suit -= 32;
		}
		void flipFaceUp(bool _faceUp = true) {
			faceUp = _faceUp;
		}
		void copyCard(Card cardToCopy) {
			rank = cardToCopy.getRank();
			suit = cardToCopy.getSuit();
			faceUp = cardToCopy.isFaceUp();
		}
		void printCard() {
			if (!faceUp) {
				cout << "****";
				return;
			}
			
			switch (rank) {
				case 1:	 cout << ' ' << 'A';
					break;
				case 10: cout << rank;
					break;
				case 11: cout << ' ' << 'J';
					break;
				case 12: cout << ' ' << 'Q';
					break;
				case 13: cout << ' ' << 'K';
					break;
				default: cout << ' ' << rank;
			}
			cout << ' ' << suit;
			return;
		}
};

void AddCardsAndShuffleDeck(vector<Card> &Deck);

int main()
{
	vector<Card> Deck;
	AddCardsAndShuffleDeck(Deck);


	// Debugging displays every card within the deck from back to front
	for (int deckIndex = Deck.size()-1; deckIndex >= 0; deckIndex--) {
		Deck.at(deckIndex).flipFaceUp();
		Deck.at(deckIndex).printCard();
		std::cout << endl;
	}
	std::cout << endl << endl;

	return 0;
}

void AddCardsAndShuffleDeck(vector<Card> &Deck) {

	// Takes in a vector of Cards and adds a standard set of 52 playing cards
	// it will then shuffle the deck by going from the back of the vector and randomly selecting
	// another card in the vector to swap places with it.  Random seed used by the current time.

	// Was originally intended to be used to create a single deck, but with a few tweaks it is now
	// able to just add a standard 52 cards to the array and shuffle them all together for future 
	// games that require two or more decks.


	// This uses for loops to generate the correct cards.
	// for loop i is used to create the 4 different suits.
	// the nested for loop j is used to create each suit's 13 ranks.
	char tempSuit;
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0: tempSuit = 'S';
			break;
		case 1: tempSuit = 'H';
			break;
		case 2: tempSuit = 'C';
			break;
		case 3: tempSuit = 'D';
			break;
		default: tempSuit = 'X';
		}
		for (int j = 1; j <= 13; j++) {
			Deck.push_back(Card(j, tempSuit));
		}
	}

	// Shuffling the deck
	Card tempCard;

	// Setting the random seed to the current time
	srand((int)time(0));
	int randInt;

	// Creates a one value for the deck size so the array function .size() isn't needed
	// to be used multiple times.
	int deckSize = Deck.size();

	// Going through each card and randomly choosing another card in the deck
	// and swap places with the 2nd chosen card
	for (int deckIndex = deckSize -1; deckIndex >= 0; deckIndex--) {
		randInt = rand() % deckSize;
		tempCard.copyCard(Deck.at(deckIndex));
		Deck.at(deckIndex).copyCard(Deck.at(randInt));
		Deck.at(randInt).copyCard(tempCard);
	}
}

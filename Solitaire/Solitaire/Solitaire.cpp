// Solitaire.cpp by Tyler Schacht
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

int main()
{
	vector<Card> Deck;

	// Creating the deck of cards
	// Would be best to have it as its own standalone funciton.

	char tempSuit;
	for (int i = 0; i < 4; i++){
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
		for (int j = 0; j < 13; j++) {
			Deck.push_back(Card (j + 1, tempSuit));
		}
	}

	// Shuffling the deck
	Card tempCard;

	// Setting the random seed to the current time
	srand((int)time(0));
	int randInt;

	// Going through each card and randomly choosing another card in the deck
	// and swap places with the 2nd chosen card
	for (int deckIndex = 51; deckIndex >= 0; deckIndex--) {
		randInt = rand() % 52;
		tempCard.copyCard(Deck.at(deckIndex));
		Deck.at(deckIndex).copyCard(Deck.at(randInt));
		Deck.at(randInt).copyCard(tempCard);
	}

	for (int deckIndex = 51; deckIndex >= 0; deckIndex--) {
		Deck.at(deckIndex).flipFaceUp();
		Deck.at(deckIndex).printCard();
		cout << endl;
	}
	cout << endl << endl;

	return 0;
}

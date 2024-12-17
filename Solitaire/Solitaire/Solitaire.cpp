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
		bool red;
		bool faceUp;
		
	public:
		Card (int _rank = 1, char _suit = 'S') {
			rank = _rank;
			suit = _suit;

			// For simplicity's sake, it is easier for the cards to be default face down
			faceUp = false;

			// Checks to see if the inputted character for suit
			// is lowerCase and changes it to upperCase if needed
			if (suit > 90)
				suit -= 32;

			// Checks the suit to see if the card should be red or not
			if (suit == 'D' || suit == 'H') {
				red = true;
			} else {
				red = false;
			}
		}

		#pragma region Get & Set Commands
		
		int getRank() {
			return rank;
		}

		char getSuit() {
			return suit;
		}

		bool isFaceUp() {
			return faceUp;
		}

		bool isRed() {
			return red;
		}
		void setRank(int _rank) {
			rank = _rank;
		}
		void setSuit(char _suit) {
			suit = _suit;

			// Checks to see if the inputted character for suit
			// is lowerCase and changes it to upperCase if needed
			if (suit > 90)
				suit -= 32;
		}
		void flipFaceUp(bool _faceUp = true) {
			faceUp = _faceUp;
		}

		#pragma endregion


		// Inputs a Card variable that is already filled out
		// and changes this Card's values to the input's values
		void copyCard(Card cardToCopy) {
			rank = cardToCopy.getRank();
			suit = cardToCopy.getSuit();
			faceUp = cardToCopy.isFaceUp();
			red = cardToCopy.isRed();
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

class Tableau {
	public:
	vector<Card> stack;
	Tableau() {
	
	}
	
	void updateLastCard() {
		stack.back().flipFaceUp(true);
	}
	
	int size() {
		return (int)stack.size();
	}
	
	void PrintTableau(int row) {
		if (stack.size() > row) {
			stack[row].printCard();
		}
		else {
			cout << "    ";
		}
			cout << "  ";
	}
};

class SolitaireBoard{
	private:
	vector<Tableau> tableaus = {Tableau(), Tableau(), Tableau(), Tableau(), Tableau(), Tableau(), Tableau()};
	vector<Card> inHand;
	vector<Card> drawPile;
	vector<Card> discardPile;


	void AddCardToTableau(int index, vector<Card>& Deck) {
		tableaus.at(index).stack.push_back(Card(Deck[Deck.size() -1].getRank(), Deck[Deck.size()-1].getSuit()));
		Deck.pop_back();
	}

public:
	SolitaireBoard(){
	}
	void Setup(vector<Card> &Deck) {

		Card tempCard;
		for (int tableauIndex = 0; tableauIndex < 7; tableauIndex++) {
			switch (tableauIndex) {
			case 0: AddCardToTableau (0, Deck);
			case 1: AddCardToTableau (1, Deck);
			case 2: AddCardToTableau (2, Deck);
			case 3: AddCardToTableau (3, Deck);
			case 4: AddCardToTableau (4, Deck);
			case 5: AddCardToTableau (5, Deck);
			case 6: AddCardToTableau (6, Deck);
			break;
			default:
				Deck[tableauIndex].printCard();
			break;
			}
		}
	}

	void PrintBoard() {
		// Need to print DrawPile, Discard Pile, and Build Piles
		cout << "****   ";
		int maxSize = 0;
		for (int tableauIndex = 0; tableauIndex < 7; tableauIndex++) {
			tableaus[tableauIndex].updateLastCard();
			if (tableaus[tableauIndex].size() > maxSize) { maxSize = tableaus[tableauIndex].size(); }
		}
		for (int row = 0; row < maxSize; row++) {
			for (int tabIndex = 0; tabIndex < 7; tabIndex++) {
				tableaus[tabIndex].PrintTableau(row);
			}
			cout << endl;
		}
	}
};

void AddCardsAndShuffleDeck(vector<Card> &Deck);

void PrintDeck(vector<Card> &Deck);

void SetupSolitaire(vector<Card> &Deck);

int main()
{
	vector<Card> Deck;
	AddCardsAndShuffleDeck(Deck);

	SolitaireBoard board;
	board.Setup(Deck);

	board.PrintBoard();

	//PrintDeck(Deck);
	
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
	int deckSize = (int)Deck.size();

	// Going through each card and randomly choosing another card in the deck
	// and swap places with the 2nd chosen card
	for (int deckIndex = deckSize -1; deckIndex >= 0; deckIndex--) {
		randInt = rand() % deckSize;
		tempCard.copyCard(Deck.at(deckIndex));
		Deck.at(deckIndex).copyCard(Deck.at(randInt));
		Deck.at(randInt).copyCard(tempCard);
	}
}

void PrintDeck(vector<Card>& Deck) {
	// Debugging displays every card within the deck from back to front
	for (int deckIndex = Deck.size() - 1; deckIndex >= 0; deckIndex--) {
		Deck.at(deckIndex).flipFaceUp();
		Deck.at(deckIndex).printCard();
		std::cout << endl;
	}
}

void SetupSolitaire(vector<Card>& Deck) {
	
}

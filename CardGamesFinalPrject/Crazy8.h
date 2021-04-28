/***********************************************************
*Crazy8.h
*By: Julian Stanton
*
*
*Program Description:
*	A class to play crazy 8s
*************************************************************/

#ifndef CRAZY8_H
#define CRAZY8_H

#include "deckOfCards.h"
#include "player.h"

//TODO
//Test test
//clean up;
//remove some couts<<

using namespace std;

class CrazyEight{
public:
	CrazyEight(int numPlayers);
	~CrazyEight();

	void playGame();
	void simGame();



private:
	deckOfCards* deck;

	int numPlayers;
	bool vsPC;
	Player *players;

	CardList c8Deck;
	CardList c8Discard;
	cardNode discardTop;

	bool validMove(cardNode a, cardNode b);
	void loadDeck();
	void dealCards();
	void play();
	bool playerTurn(int player);
	bool goAI(int player);
	void sim();
	int getValidInput(int min, int max);
	void mixBackIn();


};

void CrazyEight::sim(){

	loadDeck();
	dealCards();

	cardNode* playersCards;
	bool gametime = true;
	int currPlayer = 0;
	int currPlaycardCount;


	string topCard;


	do{
		c8Deck.shuffleCards();
		topCard = c8Deck.displayTop();
		cout << endl;
	} while (topCard[0] == '8');

	discardTop.face = topCard[0];
	discardTop.suit = topCard[1];
	c8Discard.addItem(c8Deck.takeTop());

	cout << "SIM!" << endl;
	while (gametime){

		cout << "Deck remaining :" << c8Deck.getQuantity() << endl;
		cout << "Discard:" << c8Discard.getQuantity() << endl;
		cout << " _______ " << endl;
		cout << "|       |" << endl;
		cout << "| " << discardTop.face << "     |" << endl;
		cout << "|   " << discardTop.suit << "   |" << endl;
		cout << "|     " << discardTop.face << " |" << endl;
		cout << "|_______|" << std::endl;


		currPlaycardCount = players[currPlayer].getCardCount();
		playersCards = new cardNode[currPlaycardCount];
		players[currPlayer].getHand(playersCards, players[currPlayer].getCardCount());

		cout << "Player " << currPlayer + 1 << "'s turn. What Card to play? (1 through " << players[currPlayer].getCardCount() << ") or "
			<< currPlaycardCount + 1 << " to draw new card. 0 to exit" << endl;

		players[currPlayer].showAllCards();

		cout << currPlaycardCount + 1 << ") Draw" << endl;

		goAI(currPlayer);

		if (!players[currPlayer].getCardCount()){
			cout << "Player " << currPlayer + 1 << " wins!" << endl;
			gametime = false;
		}

		currPlayer++;
		if (currPlayer >= numPlayers){
			currPlayer = 0;
		}


		delete[] playersCards;
	}

}

int CrazyEight::getValidInput(int min, int max){
	int input;
	bool valid;

	do	{
		cin >> input;

		if (cin.fail() || input<min || input >max){
			cout << "invalid entry! Try again" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			valid = false;
		} else{
			valid = true;
		}

	} while (!valid);


	return input;
}


void CrazyEight::play(){

	loadDeck();
	dealCards();

	cardNode* playersCards;
	bool gametime = true;
	int currPlayer = 0;
	int currPlaycardCount;


	string topCard;


	do	{
		c8Deck.shuffleCards();
		topCard = c8Deck.displayTop();
		cout << endl;
	} while (topCard[0]=='8');

	discardTop.face = topCard[0];
	discardTop.suit = topCard[1];
	c8Discard.addItem(c8Deck.takeTop());


	while (gametime){
		system("cls");
		cout <<"Deck remaining :" << c8Deck.getQuantity() << endl;
		cout << "Discard:" << c8Discard.getQuantity() << endl;
		cout << " _______ " <<endl;
		cout << "|       |" <<endl;
		cout << "| "<< discardTop.face <<"     |" <<endl;
		cout << "|   " << discardTop.suit <<"   |" <<endl;
		cout << "|     " << discardTop.face <<" |" << endl;
		cout << "|_______|" << std::endl;


		currPlaycardCount = players[currPlayer].getCardCount();
		playersCards = new cardNode[currPlaycardCount];
		players[currPlayer].getHand(playersCards, players[currPlayer].getCardCount());

		cout << "Player " << currPlayer + 1 << "'s turn. What Card to play? (1 through " << players[currPlayer].getCardCount() << ") or "
			<< currPlaycardCount + 1 << " to draw new card. 0 to exit" << endl;

		players[currPlayer].showAllCards();

		cout << currPlaycardCount + 1 << ") Draw" << endl;

		if (vsPC){

			if (currPlayer==1)	{
				goAI(currPlayer);

			} else{
				if (!playerTurn(currPlayer)){
					cout << "bye" << endl;
					return;
				}
			}

		} else	{

			if (!playerTurn(currPlayer)){
				cout << "bye" << endl;
				return;
			}

		}

		if (!players[currPlayer].getCardCount()){
			cout << "Player " << currPlayer + 1 << " wins!" << endl;
			gametime = false;
		}

		currPlayer++;
		if (currPlayer >= numPlayers){
			currPlayer = 0;
		}


		delete[] playersCards;
	}
	cout << "Hope you enjoyed crazy eights!";

}

void CrazyEight::mixBackIn(){

	cout << "Mixing discard back in" << endl;

	cardNode save;
	save = c8Discard.takeTop();

	while (c8Discard.getQuantity()){
		c8Deck.addItem(c8Discard.takeTop());
	}

	c8Discard.addItem(save);


}

bool CrazyEight::goAI(int currPlayer){

	cardNode* playersCards;
	cardNode chosenCard;
	int cardCount = players[currPlayer].getCardCount();
	int vCardCount = 0;
	int eightIndex;
	bool validCard;
	int suitCount[4] = {0};
	int bestSuit;
	int bestSuitIndex;
	playersCards = new cardNode[cardCount];

	players[currPlayer].getHand(playersCards, cardCount);


	eightIndex = -1;
	validCard = false;
	for (int i = 0; i < cardCount; i++)	{

		if (validMove(discardTop, playersCards[i]))	{
			chosenCard = playersCards[i];
			validCard = true;
		} else if(playersCards[i].face == '8') {
			eightIndex = i;
		}
		suitCount[playersCards[i].suit - 3]++;

	}

	if (validCard)	{
		players[currPlayer].removeCard(chosenCard);
		c8Discard.addItem(chosenCard);
		discardTop = chosenCard;
		cout << "Playing: " << chosenCard.face << chosenCard.suit << endl;
		return true;
	}


	if (eightIndex>=0)	{
		bestSuit = -1;

		for (int i = 0; i < 4; i++){

			if (bestSuit < suitCount[i])	{
				bestSuit = suitCount[i];
				bestSuitIndex = i;
			}
		}

		chosenCard = playersCards[eightIndex];

		discardTop = chosenCard;
		discardTop.suit = bestSuitIndex + 3;
		cout << "Playing an 8, chaging suit to " << discardTop.suit << endl;
		players[currPlayer].removeCard(chosenCard);
		c8Discard.addItem(chosenCard);

		return true;
	}


	if (!validCard && eightIndex < 0){
		cout << "Drawing Card" << endl;
		if (c8Deck.getQuantity() < 1){
			mixBackIn();
		}

		players[currPlayer].addCard(c8Deck.takeTop());
		return true;
	}

	delete[] playersCards;


	return false;
}

bool CrazyEight::playerTurn(int currPlayer){

	int playerIn;
	int cardCount = players[currPlayer].getCardCount();
	cardNode* playersCards = new cardNode[cardCount];
	cardNode chosenCard;
	bool crazy8 = false;

	players[currPlayer].getHand(playersCards, players[currPlayer].getCardCount());


	playerIn = getValidInput(0, cardCount + 1);

	if (playerIn == 0){
		return false;
	}

	if (playerIn>0&&playerIn <= cardCount){
		cout << playersCards[playerIn - 1].face<< playersCards[playerIn - 1].suit<<endl;
		chosenCard = playersCards[playerIn - 1];

		if (chosenCard.face == '8')	{
			crazy8 = true;

		} else if (validMove(chosenCard, discardTop)){
			players[currPlayer].removeCard(chosenCard);
			c8Discard.addItem(chosenCard);
			discardTop = chosenCard;
			delete[] playersCards;
			return true;

		} else	{
			cout << "oops, please try agian" << endl;
			delete[] playersCards;
			return 	playerTurn(currPlayer);
		}
	} else if (playerIn == cardCount+1)	{
		cout << "Draw Card" << endl;
		if (c8Deck.getQuantity()<1){
			mixBackIn();
		}

		players[currPlayer].addCard(c8Deck.takeTop());
		delete[] playersCards;

		return true;
	}


	if (crazy8)	{
		cout << "You played an 8, choose new suit!" << endl;
		cout << "1)" << char(HEARTS) << " 2)" << char(DIOMONDS) << " 3)" << char(CLUBS) << " 4)" << char(SPADES) << endl;


		playerIn = getValidInput(1, 4);

		players[currPlayer].removeCard(chosenCard);
		c8Discard.addItem(chosenCard);
		discardTop = chosenCard;
		discardTop.suit = playerIn + 2;
		delete[] playersCards;
		return true;

	}
	return false;
}

void CrazyEight::loadDeck(){

	deck->shuffleDeck();

	string newCardData;
	cardNode newCard;

	do{
		newCardData = deck->takeCard();
		if (newCardData != ""){
			newCard.face = newCardData[0];
			newCard.suit = newCardData[1];
			c8Deck.addItem(newCard);
		}

	} while (newCardData != "");

	c8Deck.shuffleCards();

}

bool CrazyEight::validMove(cardNode a, cardNode b){


	if (a.face==b.face || a.suit == b.suit)	{
		return true;
	}
	return false;
}

void CrazyEight::dealCards(){

	cout << "Dealing Cards" << endl;

	int delt = 0;
	int p = 0;

	while (delt < players[p].getHandSize()*numPlayers)	{

		players[p++].addCard(c8Deck.takeTop());
		if (p>=numPlayers)	{
			p = 0;
		}
		delt++;
	}

}

CrazyEight::CrazyEight(int numPlayers){
	this->numPlayers = numPlayers;

	int handSize;
	int numDecks;
	int numCards;
	discardTop.face = 'X';

	if (this->numPlayers == 1){
		numDecks = 1;
		handSize = 7;
		vsPC = true;
		this->numPlayers = 2;
	} else if (this->numPlayers == 2){
		numDecks = 1;
		handSize = 7;
		vsPC = false;
	} else if (this->numPlayers < 9){
		numDecks = 2;
		handSize = 5;
		vsPC = false;
	} else{
		numDecks = 3;
		handSize = 5;
		vsPC = false;
	}

	deck = new deckOfCards(numDecks);
	players = new Player[this->numPlayers];

	numCards = 52 * numDecks;

	for (int i = 0; i < this->numPlayers; i++)		{
		players[i].createPlayer(handSize , numCards);
	}



}

CrazyEight::~CrazyEight(){

	delete [] players;
	delete deck;
}

void CrazyEight::simGame(){
	sim();
	cout << "Thanks for invoking Crazy Eights!" << endl;
	system("pause");

}

void CrazyEight::playGame(){
	play();
	cout << "Thanks for invoking Crazy Eights!" << endl;
	system("pause");
}

#endif

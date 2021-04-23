/***********************************************************
*Player.h
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


class CrazyEight{
public:
	CrazyEight(int numPlayers);
	~CrazyEight();

private:
	deckOfCards* deck;
	int numPlayers;
	void play();
	Player *players;
	void dealCards();
	Player discardPile;
	bool validMove(card a, card b);

};

void CrazyEight::play(){
	cout << "Play" << endl;
	dealCards();
	players[0].showAllCards();
	cout << endl;
	players[1].showAllCards();

	bool endOfGame = false;
	int playerIn;
	int curPlayersTurn =0;

	discardPile.addCard(deck->takeCard());

	while (!endOfGame){
		cout << "Player " << curPlayersTurn << "'s turn. What would you like to do?" << endl;

		cout << "1) ShowHand" << endl;
		cout << "2) Play Card" << endl;
		cout << "0) Exit" << endl;

		cout << "Discard Pile: ";
		discardPile.showFirstCard();
		cout << endl;


		cin >> playerIn;

		if (playerIn ==0 )	{
			endOfGame = true;
		}

	}


}

bool CrazyEight::validMove(card a, card b){

}


void CrazyEight::dealCards(){
	cout << "Dealing Cards" << endl;
	for (int p = 0; p < numPlayers; p++)		{
		for (int i = 0; i < players[p].getHandSize(); i++){
			players[p].addCard(deck->takeCard());
		}

	}

}

CrazyEight::CrazyEight(int numPlayers){
	this->numPlayers = numPlayers;

	players = new Player[numPlayers];
	
	int handSize =7;
	int numDecks =1;

	if (this->numPlayers == 1){
		cout << "Sorry you cant play by yourself at the moment" << endl;
	} else if (this->numPlayers == 2){
		numDecks = 1;
		handSize = 7;
	} else if (this->numPlayers < 20){
		numDecks = 2;
		handSize = 5;
	} else{
		numDecks = 3;
		handSize = 5;
	}

	deck = new deckOfCards(numDecks);
	
	deck->shuffleDeck();


	for (int i = 0; i < numPlayers; i++)		{
		players[i].createPlayer(handSize , 52*numDecks);
	}

	discardPile.createPlayer(handSize, 52 * numDecks, true);

	play();


}

CrazyEight::~CrazyEight(){

	delete [] players;
	delete deck;
}

#endif
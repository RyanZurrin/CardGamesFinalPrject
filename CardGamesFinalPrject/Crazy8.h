#pragma once
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

};

void CrazyEight::play(){
	cout << "Play" << endl;
	dealCards();
	players[0].showAllCards();
}

void CrazyEight::dealCards(){
	cout << "Deal" << endl;
	for (int p = 0; p < numPlayers; p++)		{
	//	cout << "Player " << p << endl;
		for (int i = 0; i < players[p].getHandSize(); i++){
		//	cout << "Add" << endl;
			players[0].addCard(deck->takeCard());
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

	play();


}

CrazyEight::~CrazyEight(){

	delete [] players;
	delete deck;
}
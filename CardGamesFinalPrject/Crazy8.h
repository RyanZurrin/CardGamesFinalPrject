#pragma once
#include "cards.h"

class Player{
public:
	Player();

	~Player();

private:
	int handSize;
	card* hand;


};

Player::Player(){
}

Player::~Player(){
}



class CrazyEight{
public:
	CrazyEight(int numPlayers);
	~CrazyEight();

private:
	deckOfCards *deck;
	int numplayers;
	void play();

	void dealCards();

};



}

CrazyEight::CrazyEight(int numPlayers){
	

	if (numPlayers == 1){
		cout << "Sorry you cant play by yourself at the moment" << endl;
	} else if (numPlayers == 2){
		deck = new deckOfCards(1);
	} else if (numPlayers < 20){
		deck = new deckOfCards(2);
	} else{
		deck = new deckOfCards(3);
	}
}

CrazyEight::~CrazyEight(){


	delete deck;
}
#pragma once
#include "deckOfCards.h"
using namespace std;

class CrazyEight: private deckOfCards{
public:
	CrazyEight(int numPlayers);
	~CrazyEight();

private:
	deckOfCards *deck;
	int numplayers;
	void play();
};

void CrazyEight::play(){

}

CrazyEight::CrazyEight(int numPlayers){
	
	deck = NULL;
	//deckOfCards deck(1);
	//deck = new deckOfCards(1);

	if (numPlayers == 1){
		cout << "Sorry you cant play by yourself at the moment" << endl;
	} else if (numPlayers == 2){
		deck = new deckOfCards(1);
	} else if (numPlayers < 20){
		deck = new deckOfCards(2);
	} else{
		deck = new deckOfCards(3);
	}

	deck->displayDeck();





}

CrazyEight::~CrazyEight(){


	delete deck;
}
#pragma once
#include "deckOfCards.h"


using namespace std;
class Player{
public:

	Player();
	Player(int handSize, bool hidden = false);
	~Player();

	bool addCard(card card);
	bool removeCard(card card);
	void showTopCard();
	void showAllCards();

private:
	int handSize;
	int cardCount;
	bool hidden;
	card* hand;


};

bool Player::addCard(card card){
	
	if (cardCount < handSize)	{
		hand[cardCount++] = card;
		return true;
	}
	return false;
}

void Player::showAllCards(){
	for (int i = 0; i < cardCount; i++)	{
		cout << hand[i].face<< hand[i].suit << endl;
	}
}



Player::Player(int handSize, bool hidden){
	this->hidden = hidden;
	this->handSize = handSize;
	this->cardCount = 0;

	hand = new card[handSize];


}

Player::Player(){
	this->hidden = false;
	this->handSize = 7;
	this->cardCount = 0;

	hand = new card[handSize];

}

Player::~Player(){

	delete[] hand;

}



class CrazyEight{
public:
	CrazyEight(int numPlayers);
	~CrazyEight();

private:
	deckOfCards* deck;
	int numplayers;
	void play();
	Player *players;
	void dealCards();

};

void CrazyEight::dealCards(){
	players[0].addCard(deck->takeCard());

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

	players = new Player[numplayers];

}

CrazyEight::~CrazyEight(){

	delete [] players;
	delete deck;
}
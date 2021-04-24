/***********************************************************
*Player.h
*By: Julian Stanton
*
*
*Program Description:
*	A class to keep track of a players atributes
*************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "deckOfCards.h"
#include "CardList.h"

using namespace std;
class Player{
public:

	Player();
	void createPlayer(int handSize, int max, bool hidden = false);
	~Player();

	bool addCard(cardNode card);
	bool removeCard(cardNode card);
	void showAllCards();

	int getHandSize();
	void showFirstCard();


private:
	int handSize;
	int maxCards;
	int cardCount;
	bool hidden;
	CardList hand;


};

void Player::showFirstCard(){

	hand.displayTop();


}

int Player::getHandSize(){
	return handSize;
}

bool Player::addCard(cardNode card){
	if (cardCount < maxCards){
		return hand.addItem(card);


	}
	return false;
}


//not tested yet just guessing
bool Player::removeCard(cardNode card){

	bool found = false;

	return 	hand.removeItem(card);


	return false;
}


void Player::showAllCards(){

	if (!hidden){
		hand.displayAll();
	}


}



void Player::createPlayer(int handSize, int maxCards, bool hidden){

	this->hidden = hidden;
	this->handSize = handSize;
	this->cardCount = 0;
	this->maxCards = maxCards;



}

Player::Player(){
	cout << "Creating Player with default Values" << endl;
	this->hidden = false;
	this->handSize = 7;
	this->cardCount = 0;
	this->maxCards = 52;


}

Player::~Player(){


}

#endif
/***********************************************************
*player.h
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
	void createPlayer(int handSize, int maxCards, int score = 0);
	~Player();

	bool addCard(cardNode card);
	bool removeCard(cardNode card);
	void showAllCards();

	int getHandSize();
	int getCardCount();
	void showFirstCard();
	void addScore(int score);
	int getScore();
	bool getHand(cardNode cards[], int size);


private:
	int handSize;
	int maxCards;
	int cardCount;
	int score;
	CardList hand;


};

void Player::showFirstCard(){
	hand.displayTop();
}

void Player::addScore(int score){
	this->score += score;
}

int Player::getScore(){
	return score;
}

bool Player::getHand(cardNode cards[], int size){

	return hand.getCards(cards, size);

}

int Player::getHandSize(){
	return handSize;
}

int Player::getCardCount(){
	return cardCount;
}

bool Player::addCard(cardNode card){
	if (cardCount < maxCards){
		cardCount++;
		return hand.addItem(card);


	}
	return false;
}

bool Player::removeCard(cardNode card){

	cardCount--;

	return 	hand.removeItem(card);

}

void Player::showAllCards(){

	hand.displayAll();

}


//sets values for player
void Player::createPlayer(int handSize, int maxCards, int score){

	this->handSize = handSize;
	this->cardCount = 0;
	this->maxCards = maxCards;

}

Player::Player(){

	this->handSize = 7;
	this->cardCount = 0;
	this->maxCards = 52;
	this->score = 0;

}

Player::~Player(){

}

#endif

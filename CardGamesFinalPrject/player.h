#pragma once
#include "deckOfCards.h"


using namespace std;
class Player{
public:

	Player();
	void createPlayer(int handSize, int max, bool hidden = false);
	~Player();

	bool addCard(card card);
	bool removeCard(card card);
	void showTopCard();
	void showAllCards();

	int getHandSize();


private:
	int handSize;
	int maxCards;
	int cardCount;
	bool hidden;
	card* hand;

};

int Player::getHandSize(){
	return handSize;
}

bool Player::addCard(card card){
	//cout <<"Adding: "<< card.face <<card.suit<< endl;
	if (cardCount < maxCards){
		hand[cardCount++] = card;

		return true;
	}
	return false;
}


//not tested yet just guessing
bool Player::removeCard(card card){

	bool found = false;

	for (int i = 0; i < cardCount; i++){
		if (hand[i] == card){
			found = true;

		}
		if (found){
			hand[i] = hand[++i];
		}

		//	cout << hand[i].face << hand[i].suit << endl;
	}

	return false;
}

void Player::showTopCard(){
	cout << hand[0].face << hand[0].suit << endl;
}

void Player::showAllCards(){

	if (!hidden){
		for (int i = 0; i < cardCount; i++){
			cout << hand[i].face << hand[i].suit << endl;
		}
	}


}



void Player::createPlayer(int handSize, int maxCards, bool hidden){

	delete[] hand;
	hand = NULL;

	this->hidden = hidden;
	this->handSize = handSize;
	this->cardCount = 0;
	this->maxCards = maxCards;
	hand = new card[maxCards];


}

Player::Player(){
	cout << "Creating Player with default Values" << endl;
	this->hidden = false;
	this->handSize = 7;
	this->cardCount = 0;
	this->maxCards = 52;
	hand = new card[maxCards];

	card a;
	card b;

}

Player::~Player(){

	delete[] hand;

}

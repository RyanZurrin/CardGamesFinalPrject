/***********************************************************
*CardList.h
*By: Julian Stanton
*
*
*Program Description:
*	an unsored list of cards to use as player hand or as a
	discard pile
*************************************************************/

#ifndef CARD_LIST_H
#define CARD_LIST_H


#include "cardNode.h"
#include <iostream>
using namespace std;

class CardList {

private:
	cardNode* head;
	int quanity;
	int max;


public:
	CardList();
	bool addItem(cardNode c);
	bool removeItem(cardNode c);
	bool isEmpty();
	bool clearList();

	bool isFull();

	int getQuantity();

	void displayAll();

	string displayTop();

	bool getCards(cardNode cards[], int amount);

	cardNode takeTop();

	~CardList();


	void shuffleCards();

};

void CardList::shuffleCards(){
	cardNode* temp;
	cardNode card;
	CardList shuffledList;

	int random;
	int quant = this->getQuantity();
	temp = new cardNode[quant];

	this->getCards(temp, quant);

	while (this->getQuantity()){
		this->getCards(temp, quant);
		random = rand() % this->getQuantity();
		card = temp[random];
		if (card.face != 'X'){
			shuffledList.addItem(card);
			this->removeItem(card);
		}
		temp[random].face = 'X';

	}

	while (shuffledList.getQuantity()){

		this->addItem(shuffledList.takeTop());
	}

	delete[] temp;
}

bool CardList::getCards(cardNode cards[], int amount){

	cardNode* curr = head;

	if (curr == NULL){
		return false;
	}

	if (amount>quanity)	{
		amount = quanity;
	}

	for (int i = 0; i < amount; i++){
		cards[i] = *curr;
		curr = curr->next;
	}

	return true;
}

cardNode CardList::takeTop(){

	cardNode top;
	top.face = 'X';
	if (head==NULL)	{
		return top;
	}

	top = *head;

	delete head;
	head = top.next;
	quanity--;
	return top;
}

CardList::CardList(){
	head = NULL;
	max = INT_MAX;
	quanity = 0;
}

bool CardList::addItem(cardNode c){

	if (isFull()){
		return false;
	}

	cardNode* newNode;
	newNode = new cardNode;
	newNode->face = c.face;
	newNode->suit = c.suit;
	newNode->next = head;
	head = newNode;
	quanity++;

	return true;

}

bool CardList::removeItem(cardNode c){
	cardNode* cur;
	cardNode* prev = NULL;

	if (isEmpty()){
		return true;
	}

	for (cur = head; cur != NULL; cur = cur->next){

		if (cur->face == c.face && cur->suit == c.suit){

			if (prev == NULL){

				head = cur->next;
				delete cur;
				quanity--;
				return true;

			} else if (cur->next == NULL){

				prev->next = NULL;
				delete cur;
				quanity--;
				return true;
			}

			prev->next = cur->next;
			delete cur;
			quanity--;
			return true;


		}
		prev = cur;
	}

	return false;
}

bool CardList::isEmpty(){

	if (head == NULL)
		return true;

	return false;
}

bool CardList::clearList(){

	cardNode* temp;
	while (head){

		temp = head;
		head = head->next;
		delete temp;
		quanity--;

	}

	head = NULL;
	return true;

}

bool CardList::isFull(){
	if (quanity >= max){
		return true;
	}

	return false;
}

int CardList::getQuantity(){
	return quanity;
}

void CardList::displayAll(){

	cardNode* cur;
	int count = 1;
	for (cur = head; cur != NULL; cur = cur->next){
		cout << count++<<") "<<cur->face << cur->suit << endl;
	}
}

string CardList::displayTop(){
	string temp;
	cout << head->face << head->suit;

	temp = head->face;
	temp+= head->suit;
	return temp;
}

CardList::~CardList(){

	clearList();
	delete head;
}


#endif

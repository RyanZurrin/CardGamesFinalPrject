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

	void displayTop();


	~CardList();

};

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

			cout << "Removing " << cur->face << cur->suit << endl;
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

	for (cur = head; cur != NULL; cur = cur->next)
		cout << cur->face << cur->suit << endl;


	cout << endl;

}

void CardList::displayTop(){

	cout << head->face << head->suit;

}

CardList::~CardList(){

	clearList();
	delete head;
}


#endif

#ifndef USLLIMP_H
#define USLLIMP_H

#include "usll.h"

usll::usll() {
	head = NULL;
	max = INT_MAX;
	quanity = 0;
}

bool usll::addItem(int val) {

	if (isFull()) {
		return false;
	}

	Node* newNode;
	newNode = new Node;
	newNode->val = val;
	newNode->next = head;
	head = newNode;
	quanity++;

	return true;

}

bool usll::removeItem(int val) {
	Node* cur;
	Node* prev = NULL;

	if (isEmpty()) {
		return true;
	}

	for (cur = head; cur != NULL; cur = cur->next) {


		if (cur->val == val) {

			cout << "Removing " << cur->val << endl;
			if (prev == NULL) {

				head = cur->next;
				delete cur;
				quanity--;
				return true;

			} else if (cur->next == NULL) {

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

bool usll::isEmpty() {

	if (head == NULL)
		return true;

	return false;
}

bool usll::clearList() {


	Node* temp;
	while (head) {

		temp = head;
		head = head->next;
		delete temp;
		quanity--;

	}
	return true;

}

bool usll::isFull() {
	if (quanity >= max) {
		return true;
	}

	return false;
}

int usll::getQuantity() {
	return quanity;
}

void usll::displayAll() {

	Node* cur;

	for (cur = head; cur != NULL; cur = cur->next)
		cout << cur->val << ", ";


	cout << endl;

}

Node* usll::findItem(int val) {

	Node* cur;


	if (isEmpty()) {
		return NULL;
	}

	for (cur = head; cur != NULL; cur = cur->next) {

		if (cur->val == val) {

			return cur;
		}

	}

	return NULL;


}

usll::~usll() {

	clearList();
	delete head;
}



#endif

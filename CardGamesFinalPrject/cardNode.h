#pragma once

struct cardNode{
	char suit;
	char face;
	cardNode* next;

	//overide just checks suit and face, not address
	bool operator==(cardNode a){
		if (a.suit == suit && a.face == face)
			return true;
		else
			return false;
	}

};
#pragma once

struct card{
	char suit;
	char face;
	card* next;

	//overide just checks suit and face, not address
	bool operator==(card a){
		if (a.suit == suit && a.face == face)
			return true;
		else
			return false;
	}

};
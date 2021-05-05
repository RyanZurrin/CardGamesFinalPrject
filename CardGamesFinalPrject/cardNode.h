/***********************************************************
*cardNode.h
*By: Julian Stanton
*
*
*Program Description:
*	Card related structs
*************************************************************/

#ifndef CRAD_NODE_H
#define CRAD_NODE_H

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

	bool operator!=(cardNode a){
		if (a.suit != suit || a.face != face)
			return true;
		else
			return false;
	}

};

#endif

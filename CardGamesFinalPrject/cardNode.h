/***********************************************************
*cardNode.h
*By: Julian Stanton
*
*
*Program Description:
*	Card related structs
*************************************************************/

#pragma once

//type cast to char to display Suit cout<<char(DIOMONDS)
typedef enum Suits{
	HEARTS = 3, DIOMONDS, CLUBS, SPADES
}Suit;

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
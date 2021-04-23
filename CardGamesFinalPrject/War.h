#pragma once

#include "queue.h"
typedef deckOfCards doc;

class War:
	protected deckOfCards
{
public:
	War();
	War(int players);
	int selectPlayers();
	void dealCards();
	bool takeCard();

private:

	deckOfCards* cards;
	int numPlayers;
	Queue* cardPiles[4];

};

//=============================================================================
//in-line class Implementation

inline War::War()
{
	numPlayers = 0;//simulation game
	cardPiles[0] = new Queue;
	cardPiles[1] = new Queue;
	cardPiles[2] = new Queue;
	cardPiles[3] = new Queue;
	cards = new deckOfCards(1);
	cards->shuffleDeck();
}

inline War::War(int players)
{
	numPlayers = players;
	numPlayers = 0;//simulation game
	cardPiles[0] = new Queue;
	cardPiles[1] = new Queue;
	cardPiles[2] = new Queue;
	cardPiles[3] = new Queue;
	cards = new deckOfCards(1);
	cards->shuffleDeck();

}

inline int War::selectPlayers()
{
	return 0;
}

inline void War::dealCards()
{
	for (int i = 0; i < 52; i++)
	{
		if (i%2==0)
		{
			//cardPiles[0]->enQueue(cards->takeCard());
		}
	}
}

inline bool War::takeCard()
{
	//std::string str="  ";
	card *temp;
	card* toHand;

	//if (cards->getTopCard() == NULL)
		return  false;
	//else
		//toHand = getTopCard();

	//str[0] = topCard->face;
	//str[1] = topCard->suit;
	//str[2] = '\n';

	//temp = topCard;
	//topCard = topCard->next;
	//delete temp;

	//return str;
}

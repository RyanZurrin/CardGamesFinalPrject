#pragma once

#include "queue.h"
#include "player.h"
typedef deckOfCards doc;

class War:
	protected deckOfCards
{
public:
	War();
	War(int players);
	int selectPlayers();
	void dealCards();
	bool compare(string p1, string p2);
	void run();

private:

	deckOfCards* cards;
	int numPlayers;
	Queue<string>* cardPiles[4];

};

//=============================================================================
//in-line class Implementation

inline War::War()
{
	numPlayers = 0;//simulation game
	cardPiles[0] = new Queue<string>;
	cardPiles[1] = new Queue<string>;
	cardPiles[2] = new Queue<string>;
	cardPiles[3] = new Queue<string>;
	cards = new deckOfCards(1);
	cards->shuffleDeck();
}

inline War::War(int players)
{
	numPlayers = players;
	numPlayers = 0;//simulation game
	cardPiles[0] = new Queue<string>;
	cardPiles[1] = new Queue<string>;
	cardPiles[2] = new Queue<string>;
	cardPiles[3] = new Queue<string>;
	cards = new deckOfCards(1);
	cards->shuffleDeck();

}

inline int War::selectPlayers()
{
	return 0;
}

inline void War::dealCards()
{
	//cards->shuffleDeck();
	for (int i = 0; i < 52; i++)
	{
		if (i % 2 == 0)
		{
			//cards->shuffleDeck();
			cardPiles[0]->enQueue(cards->takeCard());
		}
		else
			//cards->shuffleDeck();
			cardPiles[1]->enQueue(cards->takeCard());
	}
	std::cout << "player 1's cards" << endl;
	cardPiles[0]->displayQueue();

	std::cout << "player 2's cards" << endl;
	cardPiles[1]->displayQueue();
}

inline bool War::compare(string p1, string p2)
{
	return false;
}

inline void War::run()
{
	cards->displayDeck();
	dealCards();
}


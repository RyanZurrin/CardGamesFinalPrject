#pragma once
#include <iostream>
#include <string>

struct card
{
	char suit;
	char face;
	card * next;
};

class deckOfCards
{
	private:
		card *topCard;
		int numOfDecks;
	public:
		deckOfCards(int = 0);
		~deckOfCards();
		std::string takeCard();
		bool shuffleDeck();
		void displayDeck();//function only used for testing purposes
	private:
		void loadDeck();
		void deleteDeck();
};
//////////////////////////////////////////////////////////////////////////////
/////////// deckOfCards Member Function Declarations  ////////////////////////
//////////////////////////////////////////////////////////////////////////////
deckOfCards::deckOfCards(int decks)
{
	topCard = NULL;
	numOfDecks = (decks < 1 ? 1 : decks);
	loadDeck();
}
//////////////////////////////////////////////////////////////////////////////
std::string deckOfCards::takeCard()
{
	std::string str="  ";
	card *temp;

	if(topCard == NULL)
		return  "";

	str[0] = topCard->face;
	str[1] = topCard->suit;
	str[2] = '\n';

	temp = topCard;
	topCard = topCard->next;
	delete temp;

	return str;
}
//////////////////////////////////////////////////////////////////////////////
void deckOfCards::displayDeck()
{
	for(card *scan=topCard; scan != NULL; scan = scan->next)
		std::cout << scan->face <<  scan->suit << "  ";
	std::cout << std::endl << std::endl;
}
//////////////////////////////////////////////////////////////////////////////
bool deckOfCards::shuffleDeck()
{
	//this part collects all the cards and reshuffles them after play has started
	deleteDeck();
	loadDeck();

	srand(clock());

	int numOfCards = numOfDecks * 52;
	int cardToFind;

	card *scan;
	card *back;
	card *tempTopCard = NULL;

	for(int times = rand() % 10 + 1; times > 0 ; times--)
		while(topCard != NULL)
		{
			cardToFind = rand() % numOfCards + 1;
			numOfCards--;

			//create a pointer to the card to be removed
			for(scan = topCard; cardToFind != 1; cardToFind--)
			{
				back = scan;
				scan = scan->next;
			}

			//remove the card from the main deck
			if(scan == topCard) //remove the first card
				topCard = scan->next;
			else
				back->next = scan->next;

			//add to temporary deck
			scan->next = tempTopCard;
			tempTopCard = scan;
		}

	topCard = tempTopCard;

	return true;
}
//////////////////////////////////////////////////////////////////////////////
void deckOfCards::loadDeck()
{
	int s; // 003, 004, 005 & 006 ascii values for the suit
	int c;
	card *temp; //to hold a new card

	for(int decks=1; decks <= numOfDecks; decks++) //create one or more decks
		for(s=3;s <= 6; s++) // create all four suits
			for(c=13; c >= 1; c--) //create 13 cards per suit
			{
				temp = new card;
				temp->suit = s;

				switch (c)
				{
					case 1:  temp->face = 'A';
							 break;
					case 10: temp->face = 'T';
							 break;
					case 11: temp->face = 'J';
							 break;
					case 12: temp->face = 'Q';
							 break;
					case 13: temp->face = 'K';
							 break;
					default: temp->face = c + 48;
				};

				temp->next = topCard;
				topCard = temp;
			}
}
//////////////////////////////////////////////////////////////////////////////
void deckOfCards::deleteDeck()
{
	for(card *temp; topCard != NULL; )
	{
		temp = topCard;
		topCard = topCard->next;
		//cout << temp->suit;
		delete temp;
	}
}
//////////////////////////////////////////////////////////////////////////////
deckOfCards::~deckOfCards()
{
	deleteDeck();
}

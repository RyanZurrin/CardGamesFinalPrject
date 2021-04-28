//	bst.h
//	Josh Jarvis
//	HW #7
//	04/22/2021
//	Header file for Bst class

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include "player.h"
#include "CardList.h"

using namespace std;

class Blackjack
{
private:
	int playerVal;
	int dealerVal;
	int pSoftAceCount;
	int dSoftAceCount;
	deckOfCards deck;
	CardList playerCards;
	CardList dealerCards;
	void dealerHit();
	void display(bool);
	//player p;
	//player dealer;
public:
	Blackjack();
	int hit();
	void dealCards();
	void clearHands();
	void stand();
	void playGame();
	~Blackjack();
};

Blackjack::Blackjack()
{
	playerVal = 0;
	dealerVal = 0;
	pSoftAceCount = 0;
	dSoftAceCount = 0;
	deck.shuffleDeck();
}

void Blackjack::playGame()
{
	string input;
	int pVal;
	bool gameOver;
	do
	{
		clearHands();
		dealCards();
		gameOver = false;
		
		if(playerVal == 21)
		{
			if(dealerVal < 21)
			{
				cout << "Blackjack! You win!" << endl;
				gameOver = true;
			}
			
		}
		
		while(!gameOver)
		{
			do
			{
				cout << "[h] to hit, [st] to stand, [sp] to split: ";
				cin >> input;
				if (input != "h" && input != "st")// && input != "sp")
					cout << "Invalid choice. Please try again" << endl;

			} while (input != "h" && input != "st");// && input != "sp");

			if (input == "h")
			{
				pVal = hit();
				display(false);
				if (pVal > 21)
				{
					cout << "Bust! You lose!" << endl;
					gameOver = true;
				}
			}
			else if (input == "st")
			{
				stand();
				gameOver = true;
				if (playerVal > dealerVal || dealerVal > 21)
					cout << "You win!" << endl;
				else if (playerVal == dealerVal)
					cout << "You tied!" << endl;
				else
					cout << "You lose!" << endl;
			}
		}
		cout << "Press 'n' to quit, or any other key to play again" << endl;
		cin >> input;
	}while (input != "n" && input != "N");
}

void Blackjack::stand()
{
	while (dealerVal < 17)
	{
		dealerHit();
	}
	display(true);
}

int Blackjack::hit()
{
	string str = deck.takeCard();
	cardNode c;
	c.face = str[0];
	c.suit = str[1];
	playerCards.addItem(c);
	switch (c.face)
	{
		case '1':
			playerVal += 1;
			break;
		case '2':
			playerVal += 2;
			break;
		case '3':
			playerVal += 3;
			break;
		case '4':
			playerVal += 4;
			break;
		case '5':
			playerVal += 5;
			break;
		case '6':
			playerVal += 6;
			break;
		case '7':
			playerVal += 7;
			break;
		case '8':
			playerVal += 8;
			break;
		case '9':
			playerVal += 9;
			break;
		case 'T':
		case 'J':
		case 'Q':
		case 'K':
			playerVal += 10;
			break;
		case 'A':
			playerVal += 11;
			pSoftAceCount++;
			break;
	}

	if (playerVal > 21 && pSoftAceCount > 0)
	{
		playerVal -= 10;
		pSoftAceCount--;
	}
		return playerVal;
}

void Blackjack::dealerHit()
{
	string str = deck.takeCard();
	cardNode c;
	c.face = str[0];
	c.suit = str[1];
	dealerCards.addItem(c);
	switch (c.face)
	{
	case '1':
		dealerVal += 1;
		break;
	case '2':
		dealerVal += 2;
		break;
	case '3':
		dealerVal += 3;
		break;
	case '4':
		dealerVal += 4;
		break;
	case '5':
		dealerVal += 5;
		break;
	case '6':
		dealerVal += 6;
		break;
	case '7':
		dealerVal += 7;
		break;
	case '8':
		dealerVal += 8;
		break;
	case '9':
		dealerVal += 9;
		break;
	case 'T':
	case 'J':
	case 'Q':
	case 'K':
		dealerVal += 10;
		break;
	case 'A':
		dealerVal += 11;
		dSoftAceCount++;
		break;
	}

	if (dealerVal > 21 && dSoftAceCount > 0)
	{
		dealerVal -= 10;
		dSoftAceCount--;
	}
}

void Blackjack::dealCards()
{
	dealerHit();
	dealerHit(); //Deals 2 cards to dealer
	hit();
	hit(); //Deals 2 cards to player
	display(false);
}

void Blackjack::clearHands()
{
	playerCards.clearList();
	dealerCards.clearList();
	playerVal = dealerVal = 0;
	pSoftAceCount = dSoftAceCount = 0;
	deck.shuffleDeck();
}

void Blackjack::display(bool showAll)
{
	system("cls");
	cout << "Dealer hand:" << endl;
	if (showAll)
		dealerCards.displayAll();
	else
	{
		cout << "1) ";
		dealerCards.displayTop();
		cout << endl << "2) ??" << endl << endl;
	}
	
	cout << "Player hand: " << endl;
	playerCards.displayAll();
}

Blackjack::~Blackjack()
{
	clearHands();
}

#endif

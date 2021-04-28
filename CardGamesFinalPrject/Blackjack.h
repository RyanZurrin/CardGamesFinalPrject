//	Blackjack.h
//	Josh Jarvis
//	04/27/2021
//	Header file for Blackjack class

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include "player.h"
#include "CardList.h"

using namespace std;

class Blackjack
{
private:
	int playerVal[5];
	int pSoftAceCount[5];
	bool isBlackjack[5];
	int dealerVal;
	int dSoftAceCount;
	int numPlayers;
	deckOfCards deck;
	CardList playerCards[5];
	CardList dealerCards;
	//CardList splitHand;
	//bool split();
	int hit(int);
	void dealCards();
	void clearHands();
	void stand();
	void dealerHit();
	void display(bool);
public:
	Blackjack();
	Blackjack(int);
	void playGame();
	~Blackjack();
};

Blackjack::Blackjack()
{
	playerVal[0] = 0;
	dealerVal = 0;
	pSoftAceCount[0] = 0;
	dSoftAceCount = 0;
	numPlayers = 1;
	deck.shuffleDeck();
	playGame();
}

Blackjack::Blackjack(int p)
{
	for(int i = 0; i < 5; i++)
	{
		playerVal[i] = 0;
		pSoftAceCount[i] = 0;
		isBlackjack[i] = false;
		
	}
	dealerVal = 0;
	dSoftAceCount = 0;
	numPlayers = p;
	deck.shuffleDeck();
	playGame();
}

void Blackjack::playGame()
{
	string input;
	int pVal;
	bool gameOver[numPlayers];
	do
	{
		clearHands();
		dealCards();
		for(int i = 0; i < numPlayers; i++)
		{
			gameOver[i] = false;
			
			if(playerVal[i] == 21)
			{
				gameOver[i] = true;
				
			}
			
			while(!gameOver[i])
			{
				do
				{
					cout << "Player " << i + 1 << "'s turn:" << endl;
					cout << "[h] to hit, [s] to stand"; //, [/] to split: ";
					cin >> input;
					if (input != "h" && input != "s")// && input != "/")
						cout << "Invalid choice. Please try again" << endl;
	
				} while (input != "h" && input != "s");// && input != "/");
	
				if (input == "h")
				{
					pVal = hit(i);
					display(false);
					if (pVal >= 21)
					{
						gameOver[i] = true;
						display(false);
					}
				}
				else if (input == "s")
				{
					gameOver[i] = true;
					display(false);
				}
				/*
				else if (input == "/")
				{
					isSplit = split(i); //Function call
				}
				*/
			}
		}
		
		stand();
		for(int i = 0; i < numPlayers; i++)
		{
			if((playerVal[i] < dealerVal && dealerVal <= 21) || playerVal[i] > 21)
				cout << "Player " << i + 1 << " lost!" << endl;
			else if (playerVal[i] > dealerVal || dealerVal > 21)
				cout << "Player " << i + 1 << " won!" << endl;
			else
				cout << "Player " << i + 1 << " tied!" << endl;
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

int Blackjack::hit(int p)
{
	string str = deck.takeCard();
	cardNode c;
	c.face = str[0];
	c.suit = str[1];
	playerCards[p].addItem(c);
	switch (c.face)
	{
		case '1':
			playerVal[p] += 1;
			break;
		case '2':
			playerVal[p] += 2;
			break;
		case '3':
			playerVal[p] += 3;
			break;
		case '4':
			playerVal[p] += 4;
			break;
		case '5':
			playerVal[p] += 5;
			break;
		case '6':
			playerVal[p] += 6;
			break;
		case '7':
			playerVal[p] += 7;
			break;
		case '8':
			playerVal[p] += 8;
			break;
		case '9':
			playerVal[p] += 9;
			break;
		case 'T':
		case 'J':
		case 'Q':
		case 'K':
			playerVal[p] += 10;
			break;
		case 'A':
			playerVal[p] += 11;
			pSoftAceCount[p]++;
			break;
	}

	if (playerVal[p] > 21 && pSoftAceCount[p] > 0)
	{
		playerVal[p] -= 10;
		pSoftAceCount[p]--;
	}
		return playerVal[p];
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
	for(int i = 0; i < numPlayers; i++)
	{
		hit(i);
		hit(i); //Deals 2 cards to player
	}
	display(false);
}

void Blackjack::clearHands()
{
	for(int i = 0; i < numPlayers; i++)
	{
		playerCards[i].clearList();
		playerVal[i] = 0;
		pSoftAceCount[i] = 0;
	}
	dealerCards.clearList();
	dealerVal = 0;
	dSoftAceCount = 0;
	deck.shuffleDeck();
}

void Blackjack::display(bool showAll)
{
	system("cls");
	
	if (showAll)
	{
		cout << "Dealer hand: " << dealerVal << endl;
		dealerCards.displayAll();
	}
	else
	{
		cout << "Dealer hand: ??" << endl;
		cout << "1) ";
		dealerCards.displayTop();
		cout << endl << "2) ??" << endl << endl;
	}
	
	for(int i = 0; i < numPlayers; i++)
	{
		cout << "Player " << i + 1 << " hand: " << playerVal[i] << endl;
		playerCards[i].displayAll();
	}
}

Blackjack::~Blackjack()
{
	clearHands();
}

#endif

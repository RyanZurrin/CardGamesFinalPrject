//	Blackjack.h
//	Josh Jarvis
//	04/27/2021
//	Header file for Blackjack class

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include "CardList.h"
#include "deckOfCards.h"

using namespace std;

class Blackjack
{
private:
	int playerVal[5];
	int splitVal[5];
	int pSoftAceCount[5];
	int spSoftAceCount[5];
	//bool isBlackjack[5];
	bool isSplit[5];
	int dealerVal;
	int dSoftAceCount;
	int numPlayers;
	deckOfCards deck;
	CardList playerCards[5];
	CardList dealerCards;
	CardList splitHand[5];
	
	bool split(int i);
	int hit(int, int);
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
		splitVal[i] = 0;
		spSoftAceCount[i] = 0;
		isSplit[i] = false;
		//isBlackjack[i] = false;
		
	}
	dealerVal = 0;
	dSoftAceCount = 0;
	if(numPlayers > p)
	{
		cout << "The maximum player count is 5" << endl;
		numPlayers = 5;
	}
	else
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
					cout << "[h] to hit, [s] to stand, [/] to split: ";
					cin >> input;
					if (input != "h" && input != "s" && input != "/")
						cout << "Invalid choice. Please try again" << endl;
	
				} while (input != "h" && input != "s" && input != "/");
	
				if (input == "h")
				{
					pVal = hit(i, 1);
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
				
				else if (input == "/")
				{
					if(isSplit[i])
						cout << "Hand is already split. Can't split again" << endl;
					else
					{
						isSplit[i] = split(i); 
						display(false);
					}
				}
			}
			if(isSplit[i])
			{
				gameOver[i] = false;
				
				while(!gameOver[i])
				{
					do
					{
						cout << "Player " << i + 1 << "'s turn:" << endl;
						cout << "[h] to hit, [s] to stand";
						cin >> input;
						if (input != "h" && input != "s")
							cout << "Invalid choice. Please try again" << endl;
		
					} while (input != "h" && input != "s");
		
					if (input == "h")
					{
						pVal = hit(i, 2);
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
				}
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
				
			if(isSplit[i])
			{
				if((splitVal[i] < dealerVal && dealerVal <= 21) || splitVal[i] > 21)
					cout << "Player " << i + 1 << " lost the 2nd hand!" << endl;
				else if (splitVal[i] > dealerVal || dealerVal > 21)
					cout << "Player " << i + 1 << " won the 2nd hand!" << endl;
				else
					cout << "Player " << i + 1 << " tied the 2nd hand!" << endl;
			}
		}
		
		cout << "Press 'x' to quit, or any other key to play again" << endl;
		cin >> input;
	}while (input != "x" && input != "X");
}

void Blackjack::stand()
{
	while (dealerVal < 17)
	{
		dealerHit();
	}
	display(true);
}

int Blackjack::hit(int p, int handNum)
{
	int val = 0;
	int ace = 0;
	string str = deck.takeCard();
	cardNode c;
	c.face = str[0];
	c.suit = str[1];
	
	if(handNum == 1)
		playerCards[p].addItem(c);
	else
		splitHand[p].addItem(c);
		
	switch (c.face)
	{
		case '1':
			val = 1;
			break;
		case '2':
			val = 2;
			break;
		case '3':
			val = 3;
			break;
		case '4':
			val = 4;
			break;
		case '5':
			val = 5;
			break;
		case '6':
			val = 6;
			break;
		case '7':
			val = 7;
			break;
		case '8':
			val = 8;
			break;
		case '9':
			val = 9;
			break;
		case 'T':
		case 'J':
		case 'Q':
		case 'K':
			val = 10;
			break;
		case 'A':
			val = 11;
			ace = 1;
			break;
	}
	
	if(handNum == 1)
	{
		playerVal[p] += val;
		pSoftAceCount[p] += ace;
		
		if (playerVal[p] > 21 && pSoftAceCount[p] > 0)
		{
			playerVal[p] -= 10;
			pSoftAceCount[p]--;
		}
			return playerVal[p];
	}
	else
	{
		splitVal[p] += val;
		spSoftAceCount[p] += ace;
		
		if (splitVal[p] > 21 && spSoftAceCount[p] > 0)
		{
			splitVal[p] -= 10;
			spSoftAceCount[p]--;
		}
			return splitVal[p];
	}
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

bool Blackjack::split(int i)
{
	if(playerCards[i].getQuantity() == 2)
	{
		cardNode temp[2];
		playerCards[i].getCards(temp, 2);
		if(temp[0].face == temp[1].face)
		{
			if(temp[1].face != 'A')
			{
				splitHand[i].addItem(temp[1]);
				playerCards[i].removeItem(temp[1]);
				playerVal[i] /= 2;
				splitVal[i] = playerVal[i];
			}
			else
			{
				splitHand[i].addItem(temp[1]);
				playerCards[i].removeItem(temp[1]);
				splitVal[i] = playerVal[i] = 11;
				pSoftAceCount[i] = spSoftAceCount[i] = 1;
			}
			hit(i, 1);
			hit(i, 2);
			return true;
		}
		else
		{
			cout << "You can only split when you have 2 cards with the same value" << endl;
			return false;
		}
	}
	else
	{
		cout << "You can only split when you have 2 cards with the same value" << endl;
	}
}

void Blackjack::dealCards()
{
	dealerHit();
	dealerHit(); //Deals 2 cards to dealer
	for(int i = 0; i < numPlayers; i++)
	{
		hit(i, 1);
		hit(i, 1); //Deals 2 cards to each player
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
		splitHand[i].clearList();
		splitVal[i] = 0;
		spSoftAceCount[i] = 0;
		isSplit[i] = false;
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
		if(!isSplit[i])
		{
			cout << "Player " << i + 1 << " hand: " << playerVal[i] << endl;
			playerCards[i].displayAll();
		}
		else
		{
			cout << "Player " << i + 1 << " hand 1: " << playerVal[i] << endl;
			playerCards[i].displayAll();
			cout << "Player " << i + 1 << " hand 2: " << splitVal[i] << endl;
			splitHand[i].displayAll();
		}
	}
}

Blackjack::~Blackjack()
{
	clearHands();
}

#endif

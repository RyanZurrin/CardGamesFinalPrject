#pragma once
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
	bool isBlackjack[5];
	bool isSplit[5];
	bool dBlackjack;
	int dealerVal;
	int dSoftAceCount;
	int numPlayers;
	double playerMoney[5];
	int playerBet[5];
	double dealerMoney;
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
	playerMoney[0] = 200.00;
	playerBet[0] = 0;
	dealerMoney = 200.00;
	dSoftAceCount = 0;
	numPlayers = 1;
	isBlackjack[0] = false;
	dBlackjack = false;
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
		playerMoney[i] = 200.00;
		playerBet[i] = 0;
		spSoftAceCount[i] = 0;
		isSplit[i] = false;
		isBlackjack[i] = false;
	}
	
	dealerVal = 0;
	dSoftAceCount = 0;
	dealerMoney = 200.00;
	dBlackjack = false;
	
	if(p > 5)
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
	int totalBet;
	//const int playerCount = numPlayers;
	//bool gameOver[playerCount]; //changed by JS delete at bottom
	bool* gameOver = new bool[numPlayers];

	do
	{
		clearHands();
		totalBet = 0;
		
		for(int i = 0; i < numPlayers; i++)
		{
			if(playerMoney[i] < 5)
			{
				playerBet[i] = 0;
				cout << "Player " << i+1 << "does not have enough money to play" << endl;
			}
			else
			{
				bool isValid;
				system("cls");
				do
				{
					cout << "Player " << i+1 << ": $" << playerMoney[i] << endl;
					cout << "Choose your bet" << endl;
					cout << "[1] = $5" << endl;
					cout << "[2] = $10" << endl;
					cout << "[3] = $20" << endl;
					cin >> input;
					
					if(input == "1")
					{
						isValid = true;
						playerBet[i] = 5;
					}
					else if(input == "2")
					{
						if(playerMoney[i] < 10)
						{
							isValid = false;
							cout << "Player " << i + 1 << "only has $" << playerMoney[i] << endl;
						}
						else
						{
							isValid = true;
							playerBet[i] = 10;
						}
					}
					else if(input == "3")
					{
						if(playerMoney[i] < 20)
						{
							isValid = false;
							cout << "Player " << i+1 << "only has $" << playerMoney[i] << endl;
						}
						else
						{
							isValid = true;
							playerBet[i] = 20;
						}
					}
					else
					{
						isValid = false;
						cout << "Invalid choice. Please try again" << endl;
					}	
				}while(!isValid);
				totalBet += playerBet[i];
			}
			
		}
		
		if(dealerMoney >= totalBet && totalBet > 0)
		{
			dealCards();
			for(int i = 0; i < numPlayers; i++)
			{
				if(playerBet[i] != 0)
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
								
								if(isSplit[i])
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
				
			}
	
			stand();
			for(int i = 0; i < numPlayers; i++)
			{
				if((playerVal[i] < dealerVal && dealerVal <= 21) || playerVal[i] > 21)
				{
					playerMoney[i] -= playerBet[i];
					dealerMoney += playerBet[i];
					cout << "Player " << i + 1 << " lost $" << playerBet[i] << endl;
				}	
				else if (playerVal[i] > dealerVal || dealerVal > 21)
				{
					playerMoney[i] += playerBet[i];
					dealerMoney -= playerBet[i];
					cout << "Player " << i + 1 << " won! $" << playerBet[i] << endl;
				}		
				else
				{
					cout << "Player " << i + 1 << " tied!" << endl;
				}
	
				if(isSplit[i])
				{
					if((splitVal[i] < dealerVal && dealerVal <= 21) || splitVal[i] > 21)
					{
						playerMoney[i] -= playerBet[i];
						dealerMoney += playerBet[i];
						cout << "Player " << i + 1 << " lost $" << playerBet[i] << " from the 2nd hand!" << endl;
					}				
					else if (splitVal[i] > dealerVal || dealerVal > 21)
					{
						playerMoney[i] += playerBet[i];
						dealerMoney -= playerBet[i];
						cout << "Player " << i + 1 << " won $" << playerBet[i] << " from the 2nd hand!" << endl;
					}	
					else
					{
						cout << "Player " << i + 1 << " tied the 2nd hand!" << endl;
					}
						
				}
			}
			
			cout << endl;
			cout << "Dealer: $" << dealerMoney << endl;
			
			//Loop to display player's money after game
			for(int i = 0; i < numPlayers; i++)
			{
				cout << "Player " << i+1 << ": $" << playerMoney[i] << endl;
			}
			
			cout << "Press 'x' to quit, or any other key to play again" << endl;
			cin >> input;
		}
		else
		{
			if(dealerMoney < totalBet)
				cout << "The dealer does not have enough money to keep playing." << endl;
			else
				cout << "The players do not have enough money to keep playing." << endl;
			cout << "Press enter to exit" << endl;
			cin >> input;
			input = "x";
		}
		
	}while (input != "x" && input != "X");


	delete [] gameOver;

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
	if(playerBet[i] * 2 > playerMoney[i])
	{
		cout << "Player does not have enough money to split" << endl;
		return false;
	}
	
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
		return false;
	}
}

void Blackjack::dealCards()
{
	dealerHit();
	dealerHit(); //Deals 2 cards to dealer
	for(int i = 0; i < numPlayers; i++)
	{
		if(playerBet[i] != 0)
		{
			hit(i, 1);
			hit(i, 1); //Deals 2 cards to each player
		}
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
		playerBet[i] = 0;
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
		if(playerVal != 0)
		{
			if(!isSplit[i])
			{
				cout << "Player " << i + 1 << " hand: " << playerVal[i] << endl;
				playerCards[i].displayAll();
				cout << endl;
			}
			else
			{
				cout << "Player " << i + 1 << " hand 1: " << playerVal[i] << endl;
				playerCards[i].displayAll();
				cout << endl;
				cout << "Player " << i + 1 << " hand 2: " << splitVal[i] << endl;
				splitHand[i].displayAll();
				cout << endl;
			}
		}
		
	}
}

Blackjack::~Blackjack()
{
	clearHands();
}

#endif

#pragma once
/**
 * @FileName War.h
 * @Details Class War is a designed class that uses two additional ADT's that
 * were custom built earlier on in my data structrues class, the stack and queue.
 * together with those this class is built to play the card game War. It will
 * allow for 1 or 2 player mode as well as a simulation mode.
 * @Author Ryan Zurrin
 * @DateBuilt  4/22/2021
 * @lastModified 4/26/2021
 */
#include "queue.h"
#include "stack.h"
#include <iostream>
#include <string>
typedef deckOfCards doc;

const bool TOP = false;

class War:
	protected deckOfCards
{
public:
	War();
	War(int);
	void warMenu();
	void showAllCards()const;
	~War();
private:
	doc* _cards;
	int numPlayers;
	int totalRounds;
	bool endGame;
	bool winner;
	bool displayMenu;
	bool checkForWinner();
	void runOnePlayer();
	void runTwoPlayer();
	void runSim();
	void dealCards()const;
	void playRound(std::string&, std::string&);
	void discardCurrentCards()const;
	void flip1();
	void flip2();
	void flip0();
	static int rank(char );
	static void delayGame(int t = 1000000);
	struct players
	{
		struct p1
		{
			Queue<std::string>* pile1;
			Stack<std::string>* discard1;
			p1()
			{
				pile1    = new Queue<std::string>(52);
				discard1 = new Stack<std::string>(52);
			}
			~p1()
			{
				delete pile1;
				delete discard1;
			}
			void playCard()const
			{
				std::string topCard;
				pile1->deQueue(topCard);
				discard1->push(topCard);
			}
		}p1_;
		struct p2
		{
			Queue<std::string>* pile2;
			Stack<std::string>* discard2;
			p2()
			{
				pile2    = new Queue<std::string>(52);
				discard2 = new Stack<std::string>(52);
			}
			~p2()
			{
				delete pile2;
				delete discard2;
			}
			void playCard()const
			{
				std::string topCard;
				pile2->deQueue(topCard);
				discard2->push(topCard);
			}
		}p2_;
	}_p_;
};//end class War

/******************************************************************************
 in-line class Implementation ************************************************/

inline War::War()
{
	numPlayers = 0;
	totalRounds = 0;
	_cards = new deckOfCards(1);
	endGame = false;
	displayMenu = true;
	winner = false;
}

inline War::War(int players)
{
	numPlayers = players;
	totalRounds = 0;
	_cards = new deckOfCards(1);
	endGame = false;
	displayMenu = true;
	winner = false;

}//end War overloaded constructor

inline void War::warMenu()
{
	int pick = 0;

	while (!endGame)
	{
		if (displayMenu)
		{
			std::cout << "\n/================================\\"<< std::endl;
			std::cout << "||         Game Of WAR          ||" << std::endl;
			std::cout << "|| ---------------------------- ||" << std::endl;
			std::cout << "|| 1.) One player vs. Computer  ||" << std::endl;
			std::cout << "|| 2.) Player 1 vs. Player 2    ||" << std::endl;
			std::cout << "|| 3.) Simulation Game          ||" << std::endl;
			std::cout << "|| 4.) Exit to main menu        ||" << std::endl;
			std::cout << "\\================================/" << std::endl;
		}
		std::cout << "\nEnter Menu Option\n>>";
		std::cin >> pick;
		if (pick >= 1 && pick <= 4)
		{
			winner = false;
			totalRounds = 0;
			switch (pick)
			{
			case 1:
				std::cout << "one player game selected\n";
				displayMenu = false;
				numPlayers = 1;
				runOnePlayer();
				break;
			case 2:
				std::cout << "two player game selected\n";
				displayMenu = false;
				numPlayers = 2;
				runTwoPlayer();
				break;
			case 3:
				std::cout << "simulation game selected\n";
				displayMenu = false;
				numPlayers = 0;
				runSim();
				break;
			case 4:
				std::cout << "exiting to main menu\n";
				endGame = true;
				break;
			default:
				break;
			}
		}
		else {
			std::cout << "Invalid choice\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
	}
}//end method warMenu

inline void War::showAllCards()const
{
	std::cout << "player one play pile:\n";
	_p_.p1_.pile1->displayQueue();
	std::cout << "player one discard pile:\n";
	_p_.p1_.discard1->displayStack();
	std::cout << "player two play pile:\n";
	_p_.p2_.pile2->displayQueue();
	std::cout << "player two discard pile:\n";
	_p_.p2_.discard2->displayStack();
}//end method showAllCards

inline void War::dealCards()const
{
	this->_cards->shuffleDeck();
	int test = 0;
	for (int i = 0; i < 52; i++)
	{
		if (i % 2 == 0)
		{
			_p_.p1_.pile1->enQueue(_cards->takeCard());
		}
		else
		{
			_p_.p2_.pile2->enQueue(_cards->takeCard());
		}

	}
}//end method dealCards

inline void War::playRound(std::string& p1Card, std::string& p2Card)
{
	bool tieHand = false;
	int recur = 0;
	if (!checkForWinner())
	{
		int p1Play = rank(p1Card[0]);
		int p2Play = rank(p2Card[0]);
		if (p1Play > p2Play )
		{
			std::string wonCard;
			if (numPlayers == 1 || numPlayers == 2)
			{
				std::cout << "\nplayer one won that round\n";
				while (!_p_.p2_.discard2->isEmpty()||!_p_.p1_.discard1->isEmpty())
				{
					_p_.p1_.discard1->pop(wonCard);
					_p_.p1_.pile1->enQueue(wonCard);
					_p_.p1_.pile1->getBack()->faceUp = false;
					_p_.p2_.discard2->pop(wonCard);
					_p_.p1_.pile1->enQueue(wonCard);
					_p_.p1_.pile1->getBack()->faceUp = false;
				}
			}
			else
			{
				std::cout << "\ncomputer player won that round\n";
				delayGame();
				while (!_p_.p2_.discard2->isEmpty()||!_p_.p1_.discard1->isEmpty())
				{
					_p_.p1_.discard1->pop(wonCard);
					_p_.p1_.pile1->enQueue(wonCard);
					_p_.p1_.pile1->getBack()->faceUp = false;
					_p_.p2_.discard2->pop(wonCard);
					_p_.p1_.pile1->enQueue(wonCard);
					_p_.p1_.pile1->getBack()->faceUp = false;
				}
			}

		}
		else if (p1Play < p2Play)
		{
			std::string wonCard;
			if (numPlayers == 1)
			{
				std::cout << "\nthe computer won that round\n";
				while (!_p_.p2_.discard2->isEmpty()||!_p_.p1_.discard1->isEmpty())
				{
					_p_.p2_.discard2->pop(wonCard);
					_p_.p2_.pile2->enQueue(wonCard);
					_p_.p2_.pile2->getBack()->faceUp = false;
					_p_.p1_.discard1->pop(wonCard);
					_p_.p2_.pile2->enQueue(wonCard);
					_p_.p2_.pile2->getBack()->faceUp = false;
				}
			}
			else if (numPlayers == 2)
			{
				std::cout << "\nplayer two won that round\n";
				while (!_p_.p2_.discard2->isEmpty()||!_p_.p1_.discard1->isEmpty())
				{
					_p_.p2_.discard2->pop(wonCard);
					_p_.p2_.pile2->enQueue(wonCard);
					_p_.p2_.pile2->getBack()->faceUp = false;
					_p_.p1_.discard1->pop(wonCard);
					_p_.p2_.pile2->enQueue(wonCard);
					_p_.p2_.pile2->getBack()->faceUp = false;
				}
			}
			else
			{
				std::cout << "\ncomputer player two won that round\n";
				delayGame();
				while (!_p_.p2_.discard2->isEmpty()||!_p_.p1_.discard1->isEmpty())
				{
					_p_.p2_.discard2->pop(wonCard);
					_p_.p2_.pile2->enQueue(wonCard);
					_p_.p2_.pile2->getBack()->faceUp = false;
					_p_.p1_.discard1->pop(wonCard);
					_p_.p2_.pile2->enQueue(wonCard);
					_p_.p2_.pile2->getBack()->faceUp = false;
				}
			}
		}
		else if (p1Play == p2Play)
		{
			if (numPlayers == 1)
			{
				std::cout << "\nPlayer one tied the computer player that round\n";
				std::cout << "\nturning one card face down\n";
				_p_.p1_.playCard();
				_p_.p2_.playCard();
				recur++;
				flip1();

			}
			else if (numPlayers == 2)
			{
				std::cout << "player one and player two tied that round\n";
				_p_.p1_.playCard();
				_p_.p2_.playCard();
				recur++;
				flip2();
			}
			else
			{
				std::cout << "computer one and computer player two tied that round\n";
				delayGame();
				_p_.p1_.playCard();
				_p_.p2_.playCard();
				recur++;
				flip0();
			}
		}
		else
			std::cout << "something went wrong\n";
	}
	if ((numPlayers == 1 || numPlayers == 2) && recur == 0 )
	{
		system("pause");
	}

}//end method playRound

inline void War::discardCurrentCards()const
{
	_p_.p1_.pile1->makeEmpty();
	_p_.p1_.discard1->makeEmpty();
	_p_.p2_.pile2->makeEmpty();
	_p_.p2_.discard2->makeEmpty();
}//end method discardCurrentCards

inline void War::flip1()
{
	system("CLS");
	char flip_;
	totalRounds++;
	showAllCards();
	std::string p1;
	std::string p2;
	std::cout << "\nPlayer 1 press [F/f] to flip a card or [Q/q] "
			  << "to quit game\n>>";
	std::cin >> flip_;
	if (flip_ =='f' || flip_ == 'F' || flip_ == 'q' || flip_ == 'Q')
	{
		if (flip_ == 'f' || flip_ == 'F')
		{
			_p_.p1_.playCard();
			_p_.p1_.discard1->peek(p1);
			_p_.p1_.discard1->getTop()->faceUp = true;
			std::cout << "\nplayer one flipped a   : " << p1 << std::endl;
			_p_.p2_.playCard();
			_p_.p2_.discard2->peek(p2);
			_p_.p2_.discard2->getTop()->faceUp = true;
			std::cout << "the computer flipped a : " << p2 << std::endl;
			playRound(p1, p2);

		}
		if (flip_ == 'q' || flip_ == 'Q')
		{
			winner = true;
			displayMenu = true;
		}
	}
	else {
		std::cout << "Invalid choice\n" << std::endl;
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}

}//end method flip1

inline void War::flip2()
{
	system("CLS");
	totalRounds++;
	char flip_;
	std::string p1;
	std::string p2;
	showAllCards();
	std::cout << "\nPlayer 1 press [F/f] or [L/l] to flip a card or [Q/q] "
			  << "to quit game\n>>";
	std::cin >> flip_;
	if (flip_ =='f' || flip_ == 'F' || flip_ == 'l' || flip_ == 'L' ||
		flip_ == 'q' || flip_ == 'Q')
	{
		if (flip_ == 'f' || flip_ == 'F' || flip_ == 'l' || flip_ =='L')
		{

			_p_.p1_.playCard();
			_p_.p1_.discard1->peek(p1);
			_p_.p1_.discard1->getTop()->faceUp = true;
			std::cout << "\nPlayer one flipped a   : " << p1 << std::endl;
		}
		if (flip_ == 'q' || flip_ == 'Q')
		{
			winner = true;
			displayMenu = true;
			return;
		}

	}
	else {
		std::cout << "Invalid choice\n" << std::endl;
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
	//////////////////////////////////////////////////////////////////////////
	std::cout << "\nPlayer 2 press [F/f] or [L/l] to flip a card or [Q/q]"
			  << "to quit game\n>>";
	std::cin >> flip_;
	if (flip_ =='f' || flip_ == 'F' || flip_ == 'l' || flip_ == 'L' ||
		flip_ == 'q' || flip_ == 'Q')
	{
		if (flip_ == 'f' || flip_ == 'F' || flip_ == 'l' || flip_ =='L')
		{
			_p_.p2_.playCard();
			_p_.p2_.discard2->peek(p2);
			_p_.p2_.discard2->getTop()->faceUp = true;
			std::cout << "\nPlayer two flipped a   : " << p2 << std::endl;
			playRound(p1, p2);

		}
		if (flip_ == 'q' || flip_ == 'Q')
		{
			winner = true;
			displayMenu = true;
		}

	}
	else {
		std::cout << "Invalid choice\n" << std::endl;
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}


}//end method flip2

inline void War::flip0()
{
	totalRounds++;
	showAllCards();
	std::string p1;
	std::string p2;
	_p_.p1_.playCard();
	_p_.p1_.discard1->peek(p1);
	_p_.p1_.discard1->getTop()->faceUp = true;
	std::cout << "\nplayer one flipped a   : " << p1 << std::endl;
	_p_.p2_.playCard();
	_p_.p2_.discard2->peek(p2);
	_p_.p2_.discard2->getTop()->faceUp = true;
	std::cout << "the computer flipped a : " << p2 << std::endl;
	playRound(p1, p2);

}//end method flip0

inline bool War::checkForWinner()
{
	if (_p_.p1_.pile1->getQty() == 0)
	{
		std::cout << "\nPlayer 2 has won the game in "<< totalRounds
				  << " rounds!!\n";
		winner = true;
		displayMenu = true;
		return true;
	}
	else if (_p_.p2_.pile2->getQty() == 0)
	{
		std::cout << "\nPlayer 1 has won the game in " << totalRounds
				  << " rounds!!\n";
		winner = true;
		displayMenu = true;
		return true;
	}
	else
		return false;
}//end method checkForWinner

inline void War::runOnePlayer()
{

	discardCurrentCards();
	dealCards();
	do
	{
		flip1();
	}
	while (!winner);
}//end method runOnePlayer

inline void War::runTwoPlayer()
{
	discardCurrentCards();
	dealCards();
	do
	{
		flip2();
	}
	while (!winner);
}//end method runTwoPlayer

inline void War::runSim()
{
	discardCurrentCards();

	dealCards();
	do
	{
		flip0();
	}
	while (!winner);
}//end method run threePlayer

inline int War::rank(char p1)
{
	switch (p1)
	{
		case '2':return 2;break;
		case '3':return 3;break;
		case '4':return 4;break;
		case '5':return 5;break;
		case '6':return 6;break;
		case '7':return 7;break;
		case '8':return 8;break;
		case '9':return 9;break;
		case 'T':return 10;break;
		case 'J':return 11;break;
		case 'Q':return 12;break;
		case 'K':return 13;break;
		case 'A':return 14;break;
		default: return 0;
	}

}//end method rank


inline War::~War()
{
	discardCurrentCards();
	delete _cards;

}//end War destructor

inline void War::delayGame(int t)
{
	for (int i = 0; i < t; i++)
	{

	}
}

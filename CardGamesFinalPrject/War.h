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
#ifndef WAR_H
#define WAR_H
#include "deckOfCards.h"
#include <iostream>
#include "discardPile.h"
#include "playPile.h"


// using typedef to make the long long unsigned int shorter to use in the sim
// speed variable
typedef unsigned long long int ulli;

/// <summary>
/// The sim speed adjusts how fast the simulation plays, the lower the value
/// the faster the speed of simulation the higher the slower.
/// inputs from 0 to 18446744073709551615
/// </summary>
const ulli SIM_SPEED = 1000000;

/// <summary>
/// C++ class used to play the card game war. Along with three additional ADT's,
/// one being a deck class provided by the instructor and the other two are a
/// stack and queue which were built by me and then converted to template class
/// implementation so that they could handle the strings being used in the the
/// take card method provided my the deckOfCards class.
/// </summary>
/// <seealso cref="deckOfCards" />
class War
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="War"/> class.
	/// </summary>
	War();

	/// <summary>
	/// Initializes a new instance of the <see cref="War"/> class.
	/// </summary>
	/// <param name="players">The number of players can be set from here
	/// ifs should anyone ever build a implementation to go that route.</param>
	War(int players);

	/// <summary>
	/// a public method to the main menu of the game which allows the user to
	/// pick which way they would want to play. 1 player vs computer, player vs
	/// player, or a full simulation.
	/// </summary>
	void playWar();

	/// <summary>
	/// Finalizes an instance of the <see cref="War"/> class.
	/// </summary>
	~War();

private:
	/// <summary>
	/// Pointer to the deck of cards that is used to play
	/// </summary>
	deckOfCards* _cards;

	/// <summary>
	/// The number players {0,1,2}
	/// </summary>
	int numPlayers;

	/// <summary>
	/// The total rounds played
	/// </summary>
	int totalRounds;

	/// <summary>
	/// The total wars won by player 1
	/// </summary>
	int p1WarWins;

	/// <summary>
	/// The total wars wond by player 2
	/// </summary>
	int p2WarWins;

	/// <summary>
	/// The end game keeps running the game if not true
	/// </summary>
	bool endGame; // boolean that

	/// <summary>
	/// when winner is found winner is set to true and this breaks the flip cycle
	/// </summary>
	bool winner;

	/// <summary>
	/// At war is set to true during a war so the proper message can be displayed
	/// at the end of the war.
	/// </summary>
	bool atWar;

	/// <summary>
	/// Method that is used to show all the card for both players piles.
	/// </summary>
	void showAllCards()const;

	/// <summary>
	/// Checks for winner.
	/// </summary>
	/// <returns></returns>
	bool checkForWinner();

	/// <summary>
	/// Runs the one player game mode.
	/// </summary>
	void runOnePlayer();

	/// <summary>
	/// Runs the two player game mode.
	/// </summary>
	void runTwoPlayer();

	/// <summary>
	/// Runs the simulation game mode
	/// </summary>
	void runSim();

	/// <summary>
	/// Deals the cards.
	/// </summary>
	void dealCards()const;

	/// <summary>
	/// Plays the round comparing the played card from each player
	/// </summary>
	/// <param name="p1Card">The card played by player one.</param>
	/// <param name="p2Card">The card played by player two.</param>
	void playRound(std::string& p1Card, std::string& p2Card);

	/// <summary>
	/// Discards the current cards.
	/// </summary>
	void discardCurrentCards()const;

	/// <summary>
	/// Flip method used in the one player game mode.
	/// </summary>
	void flip1();

	/// <summary>
	/// Flip method used in the two player game mode.
	/// </summary>
	void flip2();

	/// <summary>
	/// Flip method used in the simulation game mode.
	/// </summary>
	void flip0();

	/// <summary>
	/// takes a char from the card and returns a integer value to represent its
	/// rank in the game.
	/// </summary>
	/// <param name="c">The char to rank.</param>
	/// <returns>integer value from 2 to 14, ace being a 14</returns>
	static int rank(char c);

	/// <summary>
	/// Delays the game as needed and is used to control the simulation speed
	/// as well.
	/// </summary>
	/// <param name="t">The amount of times a loop will increment to slow
	/// down the process.</param>
	static void delayGame(ulli t = 100000000);

	/// <summary>
	/// nested structures to hold the players and their card piles and discard
	/// piles, as well as a play a card method for each which allows them to take
	/// a card from their pile and put it into discard face up, or down if is a
	/// war situation.
	/// </summary>
	struct players
	{
		/// <summary>
		///	structure for player 1
		/// </summary>
		struct p1
		{
			PlayPile<std::string>* pile1;
			DiscardPile<std::string>* discard1;
			p1()
			{
				pile1    = new PlayPile<std::string>(52);
				discard1 = new DiscardPile<std::string>(52);
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
		/// <summary>
		///	structure for player 2
		/// </summary>
		struct p2
		{
			PlayPile<std::string>* pile2;
			DiscardPile<std::string>* discard2;
			p2()
			{
				pile2    = new PlayPile<std::string>(52);
				discard2 = new DiscardPile<std::string>(52);
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
#endif


/******************************************************************************
 in-line class Implementation ************************************************/

inline War::War()
{
	numPlayers = 0;
	totalRounds = 0;
	p1WarWins = 0;
	p2WarWins = 0;
	_cards = new deckOfCards(1);
	endGame = false;
	winner = false;
	atWar = false;
}

inline War::War(int players)
{
	numPlayers = players;
	totalRounds = 0;
	p1WarWins = 0;
	p2WarWins = 0;
	_cards = new deckOfCards(1);
	endGame = false;
	winner = false;
	atWar = false;

}//end War overloaded constructor

inline void War::playWar()
{
	int pick = 0;

	while (!endGame)
	{
		if (true)
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
				numPlayers = 1;
				runOnePlayer();
				break;
			case 2:
				std::cout << "two player game selected\n";
				numPlayers = 2;
				runTwoPlayer();
				break;
			case 3:
				std::cout << "simulation game selected\n";
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
				if (atWar)
				{
					std::cout << "\nPlayer one won the War!\n";
					delayGame();
					p1WarWins++;
					atWar = false;
				}
				else
				{
					std::cout << "\nPlayer one won that round\n";
				}
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
				if (atWar)
				{
					std::cout << "\nThe computer SIM 1 won that war!";
					atWar = false;
					p1WarWins++;
					delayGame(SIM_SPEED*100);
				}
				else
				{
					std::cout << "\nThe computer SIM 1 won that round\n";
				}
				delayGame(SIM_SPEED);
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
				if (atWar)
				{
					std::cout << "\nThe Computer won that war!\n";
					delayGame();
					p2WarWins++;
					atWar = false;
				}
				else
				{
					std::cout << "\nThe computer won that round\n";
				}
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
				if (atWar)
				{
					std::cout << "\nPlayer two won that war!\n";
					delayGame();
					p2WarWins++;
					atWar = false;
				}
				else
				{
					std::cout << "\nplayer two won that round\n";
				}
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
				if (atWar)
				{
					std::cout << "\nThe computer SIM 2 won that war!\n";
					atWar = false;
					p2WarWins++;
					delayGame(SIM_SPEED*100);
				}
				else
				{
					std::cout << "\nThe computer SIM 2 won that round\n";
				}
				delayGame(SIM_SPEED);
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
				std::cout << "\npress a key to turn cards face down\n";
				system("pause");
				delayGame();
				atWar = true;
				_p_.p1_.playCard();
				_p_.p2_.playCard();
				recur++;
				flip1();

			}
			else if (numPlayers == 2)
			{
				std::cout << "\nPlayer one and Player two tied that round\n";
				std::cout << "\npress a key to turn cards face down\n";
				system("pause");
				delayGame();
				atWar = true;
				_p_.p1_.playCard();
				_p_.p2_.playCard();
				recur++;
				flip2();
			}
			else
			{
				std::cout << "\nComputer SIM 1 and Computer SIM 2 tied that round\n";
				delayGame(SIM_SPEED);
				atWar = true;
				_p_.p1_.playCard();
				_p_.p2_.playCard();
				recur++;
				flip0();
			}
		}
		else
			std::cout << "\n\nsomething went wrong\n";
	}
	if ((numPlayers == 1 || numPlayers == 2) && recur == 0 )
	{
		delayGame(1000000000);
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
		}
	}
	else {
		std::cout << "Invalid choice\n" << std::endl;
		std::cin.clear();
		std::cin.ignore(100, '\n');
		delayGame();
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
			return;

		}
	}
	else
	{
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
	system("CLS");
	totalRounds++;
	showAllCards();
	if (atWar)
	{
		delayGame(SIM_SPEED);

	}
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
	if (_p_.p1_.pile1->getQty() == 0&&_p_.p2_.pile2->getQty() == 0)
	{//both run out of cards and the game is a dray
		std::cout << "\nThis game was a draw, No one Won\n";
	}
	if (_p_.p1_.pile1->getQty() == 0)
	{//player one runs out of cards and player two is the winner
		if (numPlayers == 2)
		{
			std::cout << "\nPlayer 2 has won the game in " << totalRounds
				<< " rounds having " << p1WarWins + p2WarWins << " wars total\n"
				<< "and winning a total of " << p2WarWins
				<< " of those wars!" << std::endl;
		}
		else if (numPlayers == 1)
		{
			std::cout << "\nThe Computer opponent won this game in "
					  << totalRounds <<" rounds having " << p1WarWins+p2WarWins
					  << " wars total\nand winning a total of " << p2WarWins
					  << " of those wars!" << std::endl;
		}
		else
		{
			std::cout << "\nComputer SIM 2 has Won this game in "
					  << totalRounds <<" rounds having " << p1WarWins+p2WarWins
					  << " wars total\nand winning a total of " << p2WarWins
					  << " of those wars!" << std::endl;
		}
		winner = true;
		return true;
	}
	else if (_p_.p2_.pile2->getQty() == 0)
	{
		if (numPlayers == 2 || numPlayers == 1)
		{
			std::cout << "\nPlayer 1 has won the game in "<< totalRounds
					  << " rounds having " << p1WarWins+p2WarWins
					  << " wars total\nand winning a total of " << p1WarWins
					  << " of those wars!" << std::endl;
		}
		else
		{
			std::cout << "\nComputer SIM 1 has Won this game in "
					  << totalRounds <<" rounds having " << p1WarWins+p2WarWins
					  << " wars total\nand winning a total of " << p1WarWins
					  << " of those wars!" << std::endl;
		}
		winner = true;
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

inline int War::rank(char c)
{
	switch (c)
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

inline void War::delayGame(ulli t)
{
	for (int i = 0; i < t; i++){}
}

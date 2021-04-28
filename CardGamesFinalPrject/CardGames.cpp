
/***********************************************************
*CardGameProject.cpp
*By: Julian Stanton, Ryan Zurrin, and Josh Jarvis
*
*
*Program Description:
*	A driver program to play card games
*************************************************************/

#include "Crazy8.h"
#include "War.h"
#include "Blackjack.h"
#include <iostream>


int main(){
	srand(static_cast<unsigned>(time(0)));
	bool playing = true;
	bool displayMenu = true;
	bool goodPick;
	bool randPick = false;
	int game = 0;
	int playerCount = 2;
	int gameType = 1;
	do
	{
		if (displayMenu && !randPick)
		{
			char h = 006;
			std::cout << "\n+-------------------------------+"<< std::endl;
			std::cout << "|      pick a Game to play      |" << std::endl;
			std::cout << "|                     _______   |" << std::endl;
			std::cout << "|  1.)  Crazy Eights |       |  |" << std::endl;
			std::cout << "|  2.)  Black Jack   | A     |  |" << std::endl;
			std::cout << "|  3.)  War          |   "<<h<<"   |  |" << std::endl;
			std::cout << "|  4.)  Random Game  |     A |  |" << std::endl;
			std::cout << "|  5.)  Exit Program |_______|  |" << std::endl;
			std::cout << "+-------------------------------+" << std::endl;
		}
		if (!randPick)
		{
			std::cout << "Pick a game to play\n>>";
			std::cin >> game;
		}
		if (game >= 1 && game <= 5)
		{
			if (game == 1)
			{
				//Julian's Game Crazy Eights
				std::cout << "Crazy Eights selected\n" << std::endl;
				do
				{
					goodPick = true;
					std::cout << "Select how many players will be playing"
							  << " or use 0 to run simulation mode\n>>";
					std::cin >> playerCount;
					if (playerCount >= 1 && playerCount <= 8)
					{
						CrazyEight c8(playerCount);
						c8.playGame();

					}
					else if (playerCount == 0)
					{
						CrazyEight c8(playerCount);
						c8.simGame();
					}
					else
					{
						goodPick = false;
						std::cout << "Invalid Player selection, enter a value"
								  << " between 1 and 8\n" << std::endl;
						std::cin.clear();
						std::cin.ignore(100, '\n');
					}
				}while (!goodPick);
				randPick = false;
			}
			else if (game == 2)
			{
				//Josh's Game of Black Jack
				std::cout << "Black Jack Selected\n" << std::endl;
				do
				{
					goodPick = true;
					std::cout << "Select how many players will be playing"
							  << " Black Jack\n>>";
					std::cin >> playerCount;
					if (playerCount >= 1 && playerCount <= 5)
					{
						Blackjack newGame(playerCount);
						newGame.playGame();
					}
					else
					{
						goodPick = false;
						std::cout << "Invalid Player selection, enter a value"
								  << " between 1 and 5\n" << std::endl;
						std::cin.clear();
						std::cin.ignore(100, '\n');
					}
				}while (!goodPick);
				randPick = false;
			}
			else if (game == 3)
			{
				//Ryan's game of War
				std::cout << "Game of War was selected\n" << std::endl;
				War newWar;
				newWar.playWar();
				randPick = false;
			}
			else if (game == 4)
			{
				//Game Randomizer
				randPick = true;
				game = rand() % 3 + 1;
			}
			else
			{
				std::cout << "Exiting game now. Thank you Good bye!\n";
				playing = false;
			}
		}
		else
		{
			std::cout << "Invalid choice\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
	}while (playing);
	return 0;
}

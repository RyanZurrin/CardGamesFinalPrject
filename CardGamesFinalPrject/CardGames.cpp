

#include "Crazy8.h"
#include "War.h"
#include <iostream>


int main(){

	bool playing = true;
	bool displayMenu = true;
	int game = 0;
	int playerCount = 2;
	int gameType = 1;
	do
	{
		if (displayMenu)
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
		std::cout << "Pick a game to play\n>>";
		std::cin >> game;
		if (game >= 1 && game <= 5)
		{
			if (game == 1)
			{
				//Julian's Game Crazy Eights
				std::cout << "Crazy Eights selected?" << std::endl;
				//std::cin >> playerCount;
				//CrazyEight c8(playerCount);
			}
			else if (game == 2)
			{
				//Josh's Game
				std::cout << "Black Jack Selected" << std::endl;
			}
			else if (game == 3)
			{
				War newWar;
				newWar.warMenu();
			}
			else if (game == 4)
			{
				//Game Randomizer
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

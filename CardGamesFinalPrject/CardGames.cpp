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

int getValidInput(int min, int max);

using namespace std;

typedef enum GameNames{

	CRAZY_EIGHTS = 1,
	BLACK_JACK,
	WAR,
	RANDOM_GAME,
	EXIT,
};

int main(){
	srand(static_cast<unsigned>(time(0)));
	bool playing = true;
	int gameSelect;
	int userIn;
	int sim;

	gameSelect = 0;
	do	{

		if (gameSelect == 0){
			system("cls");
			cout << "\n+-------------------------------+" << endl;
			cout << "|      pick a Game to play      |" << endl;
			cout << "|                     _______   |" << endl;
			cout << "|  1.)  Crazy Eights |       |  |" << endl;
			cout << "|  2.)  Black Jack   | A     |  |" << endl;
			cout << "|  3.)  War          |   " << char(6) << "   |  |" << endl;
			cout << "|  4.)  Random Game  |     A |  |" << endl;
			cout << "|  5.)  Exit Program |_______|  |" << endl;
			cout << "+-------------------------------+" << endl;

			cout << "Pick a game to play\n>>";

			gameSelect = getValidInput(1, 5);
		}

		switch (gameSelect){
		case CRAZY_EIGHTS:
			{
			    cout << "Crazy Eights selected "<< endl;
				cout << "Select how many players will be playing?"
					<< " or use 0 to run simulation mode\n>>";
				userIn = getValidInput(0, 20);
				sim = false;
				if (userIn == 0){
					cout << "How many players to sim?" << endl;
					userIn = getValidInput(0, 20);
					sim = true;
				}
				CrazyEight c8(userIn);

				if (sim)	{
					c8.simGame();
				} else	{
					c8.playGame();
				}
				gameSelect = 0;
			}

			break;
		case BLACK_JACK:
			{
				cout << "Black Jack selected" << endl;
				cout << "Select how many players will be playing?" << endl;
				userIn = getValidInput(0, 5);
				Blackjack newGame(userIn);
				gameSelect = 0;
			}
			break;
		case WAR:
		{
			cout << "Way selected" << endl;
			War newWar;
			newWar.playWar();
			gameSelect = 0;
			break;
		}
		case RANDOM_GAME:
			gameSelect = rand() % 3 + 1;
			break;
		case EXIT:
		default:
			playing = false;
			break;
		}
	} while (playing);
	return 0;
}


int getValidInput(int min, int max){
	int input;
	bool valid;
	do{
		cin >> input;
		if (cin.fail() || input<min || input >max){
			cout << "invalid entry! Try again" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			valid = false;
		} else{
			valid = true;
		}
	} while (!valid);	
	return input;
}

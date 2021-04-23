#include "Crazy8.h"
#include <iostream>
using namespace std;

int main(){


	int game = 1;
	int playerCount = 2;
	cout << "What Game?";
	//cin >> game;


	if (game==1){
		cout << "players?" << endl;
		cin >> playerCount;
		CrazyEight c8(playerCount);

	} else	if (game == 2){
		//add your game
	}
	else if (game == 3){
		//add your game
	}


	return 0;
}

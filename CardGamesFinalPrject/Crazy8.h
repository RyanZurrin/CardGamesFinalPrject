/***********************************************************
*Crazy8.h
*By: Julian Stanton
*
*
*Program Description:
*	A class to play crazy 8s
*************************************************************/

#ifndef CRAZY8_H
#define CRAZY8_H

#include "deckOfCards.h"
#include "player.h"

//TODO
//shufle discard back in
//if fist discard is 8 shuffle back in
// AI
//test multi draw
using namespace std;

class CrazyEight{
public:
	CrazyEight(int numPlayers, bool multyDraw = true);
	~CrazyEight();

private:
	deckOfCards* deck;
	int numPlayers;
	void play();
	void playAI();
	Player *players;
	void dealCards();
	Player discardPile;
	cardNode drawCard();
	bool validMove(cardNode a, cardNode b);
	void drawScreen();
	int currentPlayer;
	int numCards;
	int crazySuit;
	bool multyDraw;

	bool AIgo(cardNode* playersCards, cardNode discardTop);

	void sim();

};

void CrazyEight::sim(){


	bool endOfGame = false;
	int playerIn;
	int curPlayersTurn = 0;
	dealCards();
	discardPile.addCard(drawCard());

	cardNode* playersCards = new cardNode[numCards];
	cardNode chosenCard;
	cardNode discardTop[1];

	char crazySuit = 0;

	//3 → ♥//4 → ♦//5 → ♣//6 → ♠

	bool endTurn = false;
	bool valid = true;

	while (!endOfGame){

		if (currentPlayer >= numPlayers){
			currentPlayer = 0;
		}

		//	system("cls");

		players[currentPlayer].getHand(playersCards, players[currentPlayer].getCardCount());


		discardPile.getHand(discardTop, 1);
		cout << "Player " << currentPlayer + 1 << "'s turn. What Card to play? (1 through " << players[currentPlayer].getCardCount() << ") or "
			<< players[currentPlayer].getCardCount() + 1 << " to draw new card" << endl;

		players[currentPlayer].showAllCards();

		cout << "Discard Pile: ";
		if (crazySuit){
			discardTop[0].suit = crazySuit;
		}
		cout << discardTop[0].face << discardTop[0].suit;
		cout << endl;

		if (AIgo(playersCards, discardTop[0])){
			endTurn = true;
		}

		if (endTurn){
			if (players[currentPlayer].getCardCount() == 0){
				endOfGame = true;
			}
			if (valid){
				currentPlayer++;
			}
			endTurn = false;
		}

	}

	cout << "Congrats player " << currentPlayer << " You Won!";

	delete[] playersCards;

}

bool CrazyEight::AIgo(cardNode* playersCards, cardNode discardTop){

	cardNode* validCards;
	cardNode chosenCard;
	validCards = new cardNode[players[currentPlayer].getCardCount()];
	int cardIndex;
	int crazyEightIndex;
	int suitCount[4];
	int bestSuit;
	int bestSuitIndex;

	cardIndex = 0;
	crazyEightIndex = -1;


	for (int i = 0; i < 4; i++){
		suitCount[i] = 0;
	}

	for (int i = 0; i < players[currentPlayer].getCardCount(); i++){

		if (validMove(playersCards[i], discardTop)){
			if (playersCards[i].face != '8'){
				validCards[cardIndex++] = playersCards[i];
				chosenCard = playersCards[i]; //just set it to a valid card.. who needs strategy?
			} else{
				crazyEightIndex = i;
				cout << "Found an 8" << endl;
			}
			cout << "Valid: " << playersCards[i].face << playersCards[i].suit << endl;

		}
		suitCount[playersCards[i].suit - 3]++;
	}

	if (cardIndex){
		cout << "Playing: " << chosenCard.face << chosenCard.suit << endl;

		players[currentPlayer].removeCard(chosenCard);
		discardPile.addCard(chosenCard);
		crazySuit = 0;
		return true;

	} else if (crazyEightIndex >= 0){
		cout << "Only 8" << endl;
		bestSuit = 0;
		bestSuitIndex = 0;
		for (int i = 0; i < 4; i++){
			cout << suitCount[i] << ":" << char(i + 3) << endl;
			if (suitCount[i] > bestSuit){
				bestSuit = suitCount[i];
				bestSuitIndex = i;
			}
		}
		cout << "best Suit =" << bestSuitIndex << endl;

		players[currentPlayer].removeCard(chosenCard);
		discardPile.addCard(chosenCard);
		crazySuit = bestSuitIndex + 2;

	} else{
		cout << "No valid move?" << endl;
		cout << "Drawing card" << endl;
		players[currentPlayer].addCard(drawCard());
		if (multyDraw){
			return false;
		}
	}


	delete[] validCards;

	return true;


}

void CrazyEight::playAI(){

	bool endOfGame = false;
	int playerIn;
	int curPlayersTurn = 0;
	dealCards();
	discardPile.addCard(drawCard());

	cardNode* playersCards = new cardNode[numCards];
	cardNode chosenCard;
	cardNode discardTop[1];

	char crazySuit = 0;

	//3 → ♥//4 → ♦//5 → ♣//6 → ♠

	bool endTurn = false;
	bool valid = true;

	while (!endOfGame){

		if (currentPlayer >= numPlayers){
			currentPlayer = 0;
		}

	//	system("cls");

		players[currentPlayer].getHand(playersCards, players[currentPlayer].getCardCount());


		discardPile.getHand(discardTop, 1);
		cout << "Player " << currentPlayer + 1 << "'s turn. What Card to play? (1 through " << players[currentPlayer].getCardCount() << ") or "
			<< players[currentPlayer].getCardCount() + 1 << " to draw new card" << endl;

		players[currentPlayer].showAllCards();

		cout << "Discard Pile: ";
		if (crazySuit){
			discardTop[0].suit = crazySuit;
		}
		cout << discardTop[0].face << discardTop[0].suit;
		cout << endl;


		if (currentPlayer==0){

			if (!valid){
				cout << chosenCard.face << chosenCard.suit << endl;
				cout << "Not Valid!" << endl << "Select a different card" << endl;
			}

			valid = true;
			cin >> playerIn;

			if (playerIn > 0 && playerIn < players[currentPlayer].getCardCount() + 1){
				chosenCard = playersCards[playerIn - 1];

				cout << chosenCard.face << chosenCard.suit << endl;

				if (chosenCard.face == '8'){
					cout << "Its an 8, choose new suit" << endl;
					cout << "1)" << char(HEARTS) << " 2)" << char(DIOMONDS) << " 3)" << char(CLUBS) << " 4)" << char(SPADES) << endl;
					playerIn = 0;

					players[currentPlayer].removeCard(chosenCard);
					discardPile.addCard(chosenCard);

					while (playerIn <= 0 || playerIn > 4){
						cin >> playerIn;
					}
					playerIn += 2;
					crazySuit = playerIn;
					endTurn = true;

				} else if (validMove(chosenCard, discardTop[0])){
					cout << "Valid" << endl;
					players[currentPlayer].removeCard(chosenCard);
					discardPile.addCard(chosenCard);
					crazySuit = 0;
					endTurn = true;

				} else{
					valid = false;
					endTurn = true;

				}
			} else if (playerIn == players[currentPlayer].getCardCount() + 1){
				players[currentPlayer].addCard(drawCard());
				if (multyDraw){
					continue;
				}
				endTurn = true;
			}

		} else	{

			//AI
			if (AIgo(playersCards,discardTop[0])){
				endTurn = true;
			}

		}

		if (endTurn)	{
			if (players[currentPlayer].getCardCount() == 0){
				endOfGame = true;
			}
			if (valid){
				currentPlayer++;
			}
			endTurn = false;
		}

	}

	cout << "Congrats player " << currentPlayer << " You Won!";

	delete[] playersCards;

}

void CrazyEight::play(){

	bool endOfGame = false;
	int playerIn;
	int curPlayersTurn =0;
	dealCards();
	discardPile.addCard(drawCard());

	cardNode* PlayersCards = new cardNode[numCards];

	cardNode chosenCard;
	cardNode discardTop[1];

	char crazySuit = 0;

	//3 → ♥//4 → ♦//5 → ♣//6 → ♠

	bool valid = true;

	while (!endOfGame){

		if (currentPlayer>=numPlayers)	{
			currentPlayer = 0;
		}
		system("cls");
		players[currentPlayer].getHand(PlayersCards, players[currentPlayer].getCardCount());


		discardPile.getHand(discardTop, 1);
		cout << "Player " << currentPlayer+1 << "'s turn. What Card to play? (1 through " << players[currentPlayer].getCardCount() << ") or "
			<< players[currentPlayer].getCardCount() + 1 << " to draw new card" << endl;

		players[currentPlayer].showAllCards();

		cout << "Discard Pile: ";
		if (crazySuit){
			discardTop[0].suit = crazySuit;
		}
		cout << discardTop[0].face << discardTop[0].suit;
		crazySuit = 0;
		cout << endl;

		if (!valid)	{
			cout << chosenCard.face << chosenCard.suit << endl;
			cout << "Not Valid!" << endl<< "Select a different card"<<endl;
		}
		valid = true;
		cin >> playerIn;

		if (playerIn > 0 && playerIn < players[currentPlayer].getCardCount() + 1){
			chosenCard = PlayersCards[playerIn - 1];

			cout << chosenCard.face << chosenCard.suit << endl;

			if (chosenCard.face == '8'){
				cout << "Its an 8, choose new suit" << endl;
				cout << "1)" << char(HEARTS) << " 2)" << char(DIOMONDS) << " 3)" << char(CLUBS) << " 4)" << char(SPADES) << endl;
				playerIn = 0;

				players[currentPlayer].removeCard(chosenCard);
				discardPile.addCard(chosenCard);

				while (playerIn <=0 || playerIn > 4)	{
					cin >> playerIn;
				}
				playerIn+=2;
				crazySuit = playerIn;
				goto endOfTurn;

			}

			if (validMove(chosenCard, discardTop[0])){
				cout << "Valid" << endl;
				players[currentPlayer].removeCard(chosenCard);
				discardPile.addCard(chosenCard);
				goto endOfTurn;

			} else{
				valid = false;
				goto endOfTurn;

			}
		} else if (playerIn == players[currentPlayer].getCardCount() + 1){
			players[currentPlayer].addCard(drawCard());
			if (multyDraw){
				continue;
			}
			goto endOfTurn;
		}

	endOfTurn:
		if (players[currentPlayer].getCardCount()==0)	{
			endOfGame = true;
		}
		if (valid)	{
			currentPlayer++;
		}


	}

	cout << "Congrats player " << currentPlayer << " You Won!";

	delete [] PlayersCards;
}

void CrazyEight::drawScreen(){
	system("cls");

	cout << "Player " << currentPlayer << "'s turn. What Card to play? (1 through "<< players[currentPlayer].getCardCount() <<") or "
		<< players[currentPlayer].getCardCount()+1 <<" to draw new card"<< endl;

	players[currentPlayer].showAllCards();

	cout << "Discard Pile: ";
	discardPile.showFirstCard();
	cout << endl;
}

cardNode CrazyEight::drawCard(){
	cardNode temp;

	string str = deck->takeCard();
	temp.face = str[0];
	temp.suit = str[1];
	return temp;
}

bool CrazyEight::validMove(cardNode a, cardNode b){


	if (a.face==b.face || a.suit == b.suit)	{
		return true;
	}
	return false;
}



void CrazyEight::dealCards(){

	cout << "Dealing Cards" << endl;

	int delt =0;
	int p = 0;
	while (delt< players[p].getHandSize()*numPlayers)	{

		players[p++].addCard(drawCard());
		if (p>=numPlayers)	{
			p = 0;
		}
		delt++;

	}
}

CrazyEight::CrazyEight(int numPlayers, bool multyDraw){
	this->numPlayers = numPlayers;
	this->multyDraw = multyDraw;

	bool AI = false;

	int handSize = 7;
	int numDecks =1;

	currentPlayer = 0;
	if (this->numPlayers == 1){
		numDecks = 1;
		handSize = 7;
		AI = true;
		this->numPlayers = 2;
	} else if (this->numPlayers == 2){
		numDecks = 1;
		handSize = 7;
	} else if (this->numPlayers < 20){
		numDecks = 2;
		handSize = 5;
	} else{
		numDecks = 3;
		handSize = 5;
	}

	deck = new deckOfCards(numDecks);
	players = new Player[this->numPlayers];

	deck->shuffleDeck();

	numCards = 52 * numDecks;

	for (int i = 0; i < this->numPlayers; i++)		{
		players[i].createPlayer(handSize , numCards);
	}

	discardPile.createPlayer(0, numCards);

	if (AI)	{
		playAI();
	}
	else{
		play();
	}




}

CrazyEight::~CrazyEight(){

	delete [] players;
	delete deck;
}

#endif

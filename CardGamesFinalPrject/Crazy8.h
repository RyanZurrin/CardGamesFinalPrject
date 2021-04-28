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
//AI
//test multi draw

using namespace std;

class CrazyEight{
public:
	CrazyEight(int numPlayers);
	~CrazyEight();

private:
	deckOfCards* deck;

	int numPlayers;

	Player *players;

	CardList c8Deck;
	CardList c8Discard;
	cardNode discardTop;

	cardNode drawCard();
	bool validMove(cardNode a, cardNode b);

	void dealCards();
	void play();
	bool playerTurn(int player);

	void loadDeck();

	void mixBackIn();

	bool goAI(int player);


};
/*
void CrazyEight::sim(){
	bool endOfGame = false;
	int playerIn;
	int curPlayersTurn = 0;
	dealCards();
	c8Discard.addItem(c8Deck.takeTop())
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
void play2(){
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
*/


void CrazyEight::play(){

	loadDeck();
	dealCards();

	cardNode* playersCards;
	bool gametime = true;
	int currPlayer = 0;
	int currPlaycardCount;


	string topCard;


	do	{
		c8Deck.shuffleCards();
		topCard = c8Deck.displayTop();
		cout << endl;
	} while (topCard[0]=='8');

	discardTop.face = topCard[0];
	discardTop.suit = topCard[1];
	c8Discard.addItem(c8Deck.takeTop());


	while (gametime){
	//	system("cls");
		cout <<"Deck remaining :" << c8Deck.getQuantity() << endl;
		cout << "Discard:" << c8Discard.getQuantity() << endl;
		cout << " _______ " <<endl;
		cout << "|       |" <<endl;
		cout << "| "<< discardTop.face <<"     |" <<endl;
		cout << "|   " << discardTop.suit <<"   |" <<endl;
		cout << "|     " << discardTop.face <<" |" << endl;
		cout << "|_______|" << std::endl;


		currPlaycardCount = players[currPlayer].getCardCount();
		playersCards = new cardNode[currPlaycardCount];
		players[currPlayer].getHand(playersCards, players[currPlayer].getCardCount());

		cout << "Player " << currPlayer + 1 << "'s turn. What Card to play? (1 through " << players[currPlayer].getCardCount() << ") or "
			<< currPlaycardCount + 1 << " to draw new card. 0 to exit" << endl;

		players[currPlayer].showAllCards();

		cout << currPlaycardCount + 1 << ") Draw" << endl;

		if (goAI(currPlayer))	{

			if (!players[currPlayer].getCardCount()){
				cout << "Player " << currPlayer + 1 << " wins!" << endl;
				gametime = false;
			}

			currPlayer++;
			if (currPlayer >= numPlayers)	{
				currPlayer = 0;
			}
		} else{
			gametime = false;
		}

		delete [] playersCards;
	}
	cout << "Hope you enjoyed crazy eights!";

}

void CrazyEight::mixBackIn(){

	cout << "Mixing discard back in" << endl;

	cardNode save;
	save = c8Discard.takeTop();

	while (c8Discard.getQuantity()){
		c8Deck.addItem(c8Discard.takeTop());
	}

	c8Discard.addItem(save);


}

bool CrazyEight::goAI(int currPlayer){

	cardNode* validCards;
	cardNode* playersCards;
	cardNode chosenCard;
	int cardCount = players[currPlayer].getCardCount();
	int vCardCount = 0;
	int eightIndex;


	validCards = new cardNode[cardCount];
	playersCards = new cardNode[cardCount];

	players[currPlayer].getHand(playersCards, cardCount);


	eightIndex = -1;
	for (int i = 0; i < cardCount; i++)	{

		if (validMove(discardTop, playersCards[i]))	{
			validCards[vCardCount++] = playersCards[i];
			chosenCard = playersCards[i];
		} else if(playersCards[i].face == '8') {
			eightIndex = i;
		}

	}


	for (int i = 0; i < vCardCount; i++){
		cout << validCards[i].face << validCards[i].suit << endl;
	}
	if (eightIndex>0)	{
		cout << playersCards[eightIndex].face << playersCards[eightIndex].suit << endl;
	}


	delete[] playersCards;
	delete[] validCards;

	return false;
}


bool CrazyEight::playerTurn(int currPlayer){

	int playerIn;
	int cardCount = players[currPlayer].getCardCount();
	cardNode* playersCards = new cardNode[cardCount];
	cardNode choosenCard;
	bool crazy8 = false;

	players[currPlayer].getHand(playersCards, players[currPlayer].getCardCount());

	cin >> playerIn;

	while (playerIn <= 0 || playerIn > cardCount+1){
		cin >> playerIn;
	}

	if (playerIn>0&&playerIn <= cardCount){
		cout << playersCards[playerIn - 1].face<< playersCards[playerIn - 1].suit<<endl;
		choosenCard = playersCards[playerIn - 1];

		if (choosenCard.face == '8')	{
			crazy8 = true;

		} else if (validMove(choosenCard, discardTop)){
			players[currPlayer].removeCard(choosenCard);
			c8Discard.addItem(choosenCard);
			discardTop = choosenCard;
			delete[] playersCards;
			return true;

		} else	{
			cout << "oops, please try agian" << endl;
			delete[] playersCards;
			return 	playerTurn(currPlayer);
		}
	} else if (playerIn == cardCount+1)	{
		cout << "Draw Card" << endl;
		if (c8Deck.getQuantity()<1){

			mixBackIn();

		}

		players[currPlayer].addCard(c8Deck.takeTop());
		delete[] playersCards;

		return true;
	}


	if (crazy8)	{
		cout << "You played an 8, choose new suit!" << endl;
		cout << "1)" << char(HEARTS) << " 2)" << char(DIOMONDS) << " 3)" << char(CLUBS) << " 4)" << char(SPADES) << endl;
		playerIn = 0;

		while (playerIn <= 0 || playerIn > 4){
			cin >> playerIn;
		}

		players[currPlayer].removeCard(choosenCard);
		c8Discard.addItem(choosenCard);
		discardTop = choosenCard;
		discardTop.suit = playerIn + 2;
		delete[] playersCards;
		return true;

	}
	return false;
}

void CrazyEight::loadDeck(){

	deck->shuffleDeck();

	string newCardData;
	cardNode newCard;

	do{
		newCardData = deck->takeCard();
		if (newCardData != ""){
			newCard.face = newCardData[0];
			newCard.suit = newCardData[1];
			c8Deck.addItem(newCard);
		}

	} while (newCardData != "");

	c8Deck.displayAll();
}

bool CrazyEight::validMove(cardNode a, cardNode b){


	if (a.face==b.face || a.suit == b.suit)	{
		return true;
	}
	return false;
}

void CrazyEight::dealCards(){

	cout << "Dealing Cards" << endl;

	int delt = 0;
	int p = 0;

	while (delt < players[p].getHandSize()*numPlayers)	{

		players[p++].addCard(c8Deck.takeTop());
		if (p>=numPlayers)	{
			p = 0;
		}
		delt++;
	}

}

CrazyEight::CrazyEight(int numPlayers){
	this->numPlayers = numPlayers;

	bool AI;
	int handSize;
	int numDecks;
	int numCards;

	if (this->numPlayers == 1){
		numDecks = 1;
		handSize = 7;
		AI = true;
		this->numPlayers = 2;
	} else if (this->numPlayers == 2){
		numDecks = 1;
		handSize = 7;
		AI = false;
	} else if (this->numPlayers < 20){
		numDecks = 2;
		handSize = 5;
		AI = false;
	} else{
		numDecks = 3;
		handSize = 5;
		AI = false;
	}

	deck = new deckOfCards(numDecks);
	players = new Player[this->numPlayers];

	numCards = 52 * numDecks;

	for (int i = 0; i < this->numPlayers; i++)		{
		players[i].createPlayer(handSize , numCards);
	}

	play();

	return;

	//if (AI)	{
	//	playAI();
	//}
	//else{
	//	play();
	//}




}

CrazyEight::~CrazyEight(){

	delete [] players;
	delete deck;
}

#endif

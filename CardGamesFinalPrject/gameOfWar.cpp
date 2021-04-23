#include "deckOfCards.h"
typedef deckOfCards doc;


using namespace std;

int main(){
	doc test;
	test.displayDeck();
	test.shuffleDeck();
	test.displayDeck();


	return 0;
}

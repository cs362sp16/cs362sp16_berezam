#include "dominion.h"
#include "myassert.h"
#include <time.h>
#include <stdlib.h>

#define PLAYERS 2

//Tests the shuffle function

int failed = 0;

int main() {
	int player;
	struct gameState state;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int oldDeckState[MAX_DECK];	//Stores deck state as it was before shuffling
	int i;
	int oldDeckCount;	//Stores old deck size
	int differentDeck = 0;	//0 means the deck is exactly the same as before shuffling, 1 means it isn't
	
	initializeGame(PLAYERS, k , 5, &state);
	
	srand(time(NULL));
	player = rand() % PLAYERS;
	oldDeckCount = state.deckCount[player];
	
	//Stores old deck state
	for (i = 0; i < state.deckCount[player]; i++) {
		oldDeckState[i] = state.deck[player][i];
	}
	
	//Runs shuffle and checks error code
	failed = myassert(shuffle(player, &state) == 0, "Checking if the function runs.", failed);
	
	//Deck size should remain the same
	failed = myassert(state.deckCount[player] == oldDeckCount, "Checking if the deck size is the same.", failed);
	
	//Checks cards position by position, a single different card triggers the differentDeck flag
	for (i = 0; i < state.deckCount[player]; i++) {
		if (oldDeckState[i] != state.deck[player][i]) {
			differentDeck = 1;
		}
	}
	
	failed = myassert(differentDeck, "Checking to see if the deck is not exactly the same.", failed);
	
	checkasserts(failed);
	
	return 0;
}
#include "dominion.h"
#include "myassert.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define PLAYERS 2

//Tests gainCard function, prototype was added to dominion.h to this end

int failed = 0;

int main() {
	int player;
	struct gameState state;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int i;
	
	initializeGame(PLAYERS, k , 5, &state);
	
	srand(time(NULL));
	player = rand() % PLAYERS;
	state.whoseTurn = player;	//Sets it to be this player's turn
	
	//Stores discard, hand, and deck counts before gainCard is called
	int oldDiscardCount = state.discardCount[player];
	int oldDeckCount = state.deckCount[player];
	int oldHandCount = state.handCount[player];
	
	//Flags used to check if the gained card is located in the deck, hand, or discard. 1 means it's there, 0 means it isn't.
	int inDiscard = 0;
	int inDeck = 0;
	int inHand = 0;
	
	//Tests card placed into discard
	failed = myassert(gainCard(duchy, &state, 0, player) == 0, "Checking if the function runs for discard", failed);
	failed = myassert(state.discardCount[player] == (oldDiscardCount + 1), "Checking if dicard pile has increased by 1", failed);
	
	for (i = 0; i < state.discardCount[player]; i++) {
		if (state.discard[player][i] == duchy) {
			inDiscard = 1;
		}
	}
	
	failed = myassert(inDiscard, "Checking to see if duchy was placed in discard", failed);
	
	//Tests card placed into deck
	failed = myassert(gainCard(duchy, &state, 1, player) == 0, "Checking if the function runs for deck", failed);
	failed = myassert(state.deckCount[player] == (oldDeckCount + 1), "Checking if deck size has increased by 1", failed);
	
	for (i = 0; i < state.deckCount[player]; i++) {
		if (state.deck[player][i] == duchy) {
			inDeck = 1;
		}
	}
	
	failed = myassert(inDeck, "Checking to see if duchy was placed in deck", failed);
	
	
	//Tests card placed into hand
	failed = myassert(gainCard(duchy, &state, 2, player) == 0, "Checking if the function runs for hand", failed);
	failed = myassert(state.handCount[player] == (oldHandCount + 1), "Checking if hand size has increased by 1", failed);
	
	for (i = 0; i < state.handCount[player]; i++) {
		if (state.hand[player][i] == duchy) {
			inHand = 1;
		}
	}
	
	failed = myassert(inHand, "Checking to see if duchy was placed in hand", failed);
	checkasserts(failed);
	
	return 0;
}
#include "dominion.h"
#include "myassert.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define PLAYERS 2

//Tests Village card functionality

int failed = 0;

int main() {
	int player;
	struct gameState state;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int i;
	
	//1 means Smithy is no longer in hand, 0 means it is
	int inHand = 1;
	
	//1 means Smithy is not in deck, 0 means it is
	int inDeck = 1;
	
	//0 means smithy is not in discard, 1 means it is
	int inDiscard = 0;

	initializeGame(PLAYERS, k , 5, &state);
	
	srand(time(NULL));
	player = rand() % PLAYERS;
	state.hand[player][0] = village;	//Adds Village to current player's hand
	
	//Stores numActions and handCount before Village is played
	int oldNumActions = state.numActions;
	int oldHandCount = state.handCount[player];
	
	//Makes sure Village can be played successfuly
	failed = myassert(playCard(0, 0, 0, 0, &state) == 0, "Checking if Village is played successfuly", failed);
	
	//Makes sure that Village is no longer in hand after being played
	for (i = 0; i < state.handCount[player]; i++) {
		if (state.hand[player][i] == village) {
			inHand = 0;
		}
	}
	
	failed = myassert(inHand, "Checking if Village isn't in hand", failed);
	
	//Makes sure Village doesn't somehow end up in the deck after being played
	for (i = 0; i < state.deckCount[player]; i++) {
		if (state.deck[player][i] == village) {
			inDeck = 0;
		}
	}
	
	failed = myassert(inDeck, "Checking if Village isn't in deck", failed);
	
	//Makes sure Village is put into the discard pile after being played
	for (i = 0; i < state.discardCount[player]; i++) {
		if (state.discard[player][i] == village) {
			inDiscard = 1;
		}
	}
	
	failed = myassert(inDiscard, "Checking if Village is in discard", failed);
	
	//Village draws 1, so hand size should be the same as before it was played
	failed = myassert(state.handCount[player] == oldHandCount, "Checking if hand size is the same", failed);
	
	//Village grants +2 actions, so total numActions should be 1 more than before
	failed = myassert(state.numActions == (oldNumActions + 1), "Checking if actions have increased by 1", failed);
	
	checkasserts(failed);
	
	return 0;
}
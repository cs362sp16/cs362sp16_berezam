#include "dominion.h"
#include "myassert.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define PLAYERS 2

//Tests Smithy card funcitonality

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
	
	//0 means Village is not in discard, 1 means it is
	int inDiscard = 0;

	initializeGame(PLAYERS, k , 5, &state);
	
	srand(time(NULL));
	//player = rand() % PLAYERS;
	player = 0;
	state.whoseTurn = player;	//Sets it to be this player's turn
	state.hand[player][0] = smithy;	//Adds Smithy to current player's hand
	
	int oldHandCount = state.handCount[player];	//Stores hand count before Smithy is played
	
	//Tests to see if Smithy can be played successfuly
	failed = myassert(playCard(0, 0, 0, 0, &state) == 0, "Checking if Smithy is played successfuly", failed);
	
	//Makes sure that Smithy is no longer in hand after being played
	for (i = 0; i < state.handCount[player]; i++) {
		if (state.hand[player][i] == smithy) {
			inHand = 0;
		}
	}
	
	failed = myassert(inHand, "Checking if Smithy isn't in hand", failed);
	
	//Makes sure Smithy doesn't somehow end up in the deck after being played
	for (i = 0; i < state.deckCount[player]; i++) {
		if (state.deck[player][i] == smithy) {
			inDeck = 0;
		}
	}
	
	failed = myassert(inDeck, "Checking if Smithy isn't in deck", failed);
	
	//Makes sure Smithy is put into the discard pile after being played
	for (i = 0; i < state.discardCount[player]; i++) {
		if (state.discard[player][i] == smithy) {
			inDiscard = 1;
		}
	}
	
	failed = myassert(inDiscard, "Checking if Smithy is in discard", failed);
	
	//Smithy draws 3, so hand size should be 2 bigger after Smithy is played
	failed = myassert(state.handCount[player] == (oldHandCount + 2), "Checking if hand size increased by 2", failed);
	
	checkasserts(failed);
	
	return 0;
}
#include "dominion.h"
#include "myassert.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define PLAYERS 2

//Tests Feast card functionality

int failed = 0;

int main() {
	int player;
	struct gameState state;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int i;
	
	//Flags used to check if Feast is in hand, deck, or discard. 1 means it's not, 0 means it's there.
	int inHand = 1;
	int inDeck = 1;
	int inDiscard = 1;
	
	initializeGame(PLAYERS, k , 5, &state);
	
	srand(time(NULL));
	player = rand() % PLAYERS;
	state.whoseTurn = player;	//Sets it to be this player's turn
	state.hand[player][0] = feast;	//Adds Feast to the player's hand
	
	//Tries to buy Duchy using Feast, should work since Duchy costs 5
	failed = myassert(playCard(0, duchy, 0, 0, &state) == 0, "Checking if Duchy can be bought", failed);
	
	//Feast is trashed after use, so it shouldn't be in hand
	for (i = 0; i < state.handCount[player]; i++) {
		if (state.hand[player][i] == feast) {
			inHand = 0;
		}
	}
	
	failed = myassert(inHand, "Checking if Feast isn't in hand", failed);
	
	//Feast is trashed after use, so it shouldn't be in deck
	for (i = 0; i < state.deckCount[player]; i++) {
		if (state.deck[player][i] == feast) {
			inDeck = 0;
		}
	}
	
	failed = myassert(inDeck, "Checking if Feast isn't in deck", failed);
	
	//Feast is trashed after use, so it shouldn't be in discard
	for (i = 0; i < state.discardCount[player]; i++) {
		if (state.discard[player][i] == feast) {
			inDiscard = 0;
		}
	}
	
	failed = myassert(inDiscard, "Checking if Feast isn't in discard", failed);
	
	//Tries to buy a Province with Feast, shouldn't work since Province costs 8
	failed = myassert(playCard(0, province, 0, 0, &state) != 0, "Checking if Province can't be bought", failed);
	
	checkasserts(failed);
	
	return 0;
}
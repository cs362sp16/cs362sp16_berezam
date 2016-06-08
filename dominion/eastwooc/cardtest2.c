#include "dominion.h"
#include "myassert.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define PLAYERS 2

//Tests Gardens card functionality

int failed = 0;

int main() {
	int player;
	struct gameState state;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	initializeGame(PLAYERS, k , 5, &state);
	
	srand(time(NULL));
	player = rand() % PLAYERS;
	state.whoseTurn = player;	//Sets it to be this player's turn
	state.hand[player][0] = gardens;
	
	//Gardens functions as a victory card, so trying to play it should return an error
	failed = myassert(playCard(0, 0, 0, 0, &state) != 0, "Checking if Gardens can't be played", failed);
	
	checkasserts(failed);
	
	return 0;
}
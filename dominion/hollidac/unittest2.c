#include "dominion.h"
#include "myassert.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define PLAYERS 2

//Tests the playCard function

int failed = 0;

int main() {
	int player;
	struct gameState state;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int i;
	int oldHandCount;	
	int oldActionCount;
	int cardPos;
	int cardStillInHand = 1;	//1 means that village is no longer in the player's hand, 0 means it still is
	
	initializeGame(PLAYERS, k , 5, &state);
	
	srand(time(NULL));
	player = rand() % PLAYERS;
	cardPos = 1;
	
	//Manually set state variables to simulate playing a card
	state.phase = 0;
	state.numActions = 1;
	state.whoseTurn = player;
	
	//Puts village in the current player's hand
	state.hand[player][cardPos] = village;
	
	oldHandCount = state.handCount[player];
	oldActionCount = state.numActions; 
	
	//Runs function for return code
	failed = myassert(playCard(cardPos, 0, 0, 0, &state) == 0, "Checking if the function runs", failed);

	//Compares new hand size to old hand size to make sure village's effect took place
	failed = myassert(state.handCount[player] == oldHandCount, "Checking if the hand size is the same", failed);

	//Compares new action count to old action count to make sure village's effect took place
	failed = myassert(state.numActions == (oldActionCount + 1), "Checking to see if numActions has increased by 1", failed);
	
	//Loops through to see if village is no longer in the player's hand
	for (i = 0; i < state.handCount[player]; i++) {
		if (state.hand[player][i] == village) {
			cardStillInHand = 0;
		}
	}
	
	failed = myassert(cardStillInHand, "Checking to see if village is still in hand.", failed);
	
	checkasserts(failed);
	
	return 0;
}
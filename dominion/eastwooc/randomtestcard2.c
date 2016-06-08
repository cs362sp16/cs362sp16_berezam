#include "dominion.h"
#include "myassert.h"
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define NUM_TESTS 100000

//Tests Gardens card functionality

int failed = 0;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Invalid number of arguments.\n");
		return -1;
	}
	
	else if (atoi(argv[1]) <= 0) {
		printf("Invalid seed. Seed value must a positive number.\n");
		return -1;
	} 
	
	int seedVal = atoi(argv[1]); 
	int i;
	int cur_test;
	int players;
	int p;
	int deckCount;
	int discardCount;
	int handCount;
	int numActions;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	
	SelectStream(2);
	PutSeed(seedVal);
	
	for(cur_test = 1; cur_test <= NUM_TESTS; cur_test++) {
		players = ceil(Random() * 3) + 1;
		p = ceil(Random() * players);
		deckCount = floor(Random() * MAX_DECK);
		discardCount = floor(Random() * MAX_DECK);
		handCount = floor(Random() * MAX_HAND);
		numActions = floor(Random() * 15) + 1; 
		
		initializeGame(players, k , 5, &G);
		G.numPlayers = players;
		G.whoseTurn = p;
		G.phase = 0;
		G.deckCount[p] = deckCount;
		G.handCount[p] = handCount;
		G.numActions = numActions;
		G.numBuys = floor(Random() * 15) + 1;
		G.playedCardCount = 0;
		
		for(i = 0; i < deckCount; i++)
			G.deck[p][i] = floor(Random() * (treasure_map + 1));
			
		for(i = 0; i < discardCount; i++) 
			G.discard[p][i] = floor(Random() * (treasure_map + 1));
					
		for(i = 1; i < handCount; i++) 
			G.hand[p][i] = floor(Random() * (treasure_map + 1));
		
		G.hand[p][0] = gardens;
		
		failed = myassert(playCard(0, 0, 0, 0, &G) != 0, "Checking if Gardens can't be played", failed);
	} 
	
	checkasserts(failed);
	
	return 0;
}
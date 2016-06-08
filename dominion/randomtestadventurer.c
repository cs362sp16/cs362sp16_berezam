#include "dominion.h"
#include "myassert.h"
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define NUM_TESTS 100	//Determines the number of tests ran

#define PRINT 1

//Tests Adventurer card functionality

int failed = 0;

int main(int argc, char* argv[]) {
	//Makes sure only 1 argument is given - the seed. Returns -1 otherwise.
	if (argc != 2) {
		printf("Invalid number of arguments.\n"); 
		return -1;
	}
	
	else if (atoi(argv[1]) <= 0) {
		printf("Invalid seed. Seed value must a positive number.\n");
		return -1;
	}
	
	int numFailed = 0;
	int seedVal = atoi(argv[1]);	//seed value
	int i;							//for loop counter
	int cur_test;					//stores the current test 
	int players;					//number of players
	int p;							//player whose turn it is
	int deckCount;					
	int discardCount;				
	int handCount;					
	int numActions;		
	int preAdventurerHandCount;
	int postAdventurerHandCount;
	int adventurerHandCheck;
	int preDeckDiscardTreasure;		//Number of treasures amongst the deck, discard, and played piles before Adventurer is played
	int preHandTreasure;			//Number of treasures in hand before Adventurer is played
	int postDeckDiscardTreasure;	
	int postHandTreasure;
	int numDrawn;					//The number of treasures that can be drawn by Adventurer. Is 2 unless the deck + discard contains less than two treasures. 
	int deckDiscardCountCheck;		//1 if deck + discard + played decrease by numDrawn - 1, 0 otherwise
	int handCountCheck;				//1 if hand size increases by numDrawn - 1, 0 otherwise
	int deckDiscardTreasureCheck;	//1 if the number of treasures in deck + discard + played decrreases by numDrawn, 0 otherwise
	int handTreasureCheck;			//1 if the number of treasures in hand increases by numDrawn, 0 otherwise
	int postPlayedCardCount;		//Size of played card pile after Adventurer is played
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	
	//Initializes random number generator
	SelectStream(2);
	PutSeed(seedVal);
	
	//Runs NUM_TESTS tests
	for(cur_test = 1; cur_test <= NUM_TESTS; cur_test++) {	
		players = ceil(Random() * 3) + 1;			//2 to 4
		p = ceil(Random() * players);				//1 to players
		deckCount = floor(Random() * MAX_DECK);		//0 to MAX_DECK - 1
		discardCount = floor(Random() * MAX_DECK);	//0 to MAX_DECK - 1
		handCount = floor(Random() * MAX_HAND);		//0 to MAX_HAND - 1
		numActions = floor(Random() * 15) + 1; 		//0 to 15. Arbitrary, but hard to imagine a turn with more than 15 actions.
		
		//Initialize flags to 0
		preDeckDiscardTreasure = 0;
		preHandTreasure = 0;
		preAdventurerHandCount = 1;	//Starts with 1
		postAdventurerHandCount = 0;
		adventurerHandCheck = 0;
		postDeckDiscardTreasure = 0;
		postHandTreasure = 0;
		numDrawn = 0;
		deckDiscardCountCheck = 0;
		handCountCheck = 0;
		deckDiscardTreasureCheck = 0;
		handTreasureCheck = 0;
		
		//Initializes state values
		initializeGame(players, k , 5, &G);
		G.numPlayers = players;
		G.whoseTurn = p;
		G.phase = 0;
		G.deckCount[p] = deckCount;
		G.handCount[p] = handCount;
		G.numActions = numActions;
		G.numBuys = floor(Random() * 15) + 1;		//0 to 15. Arbitrary, but hard to imagine a turn with more than 15 buys.
		G.playedCardCount = 0;
		
		//Randomly generates deck contents
		for(i = 0; i < deckCount; i++) {
			G.deck[p][i] = floor(Random() * (treasure_map + 1));
			
			//Counts Treasure cards as they're added to deck
			if((G.deck[p][i] == copper) | (G.deck[p][i] == silver) | (G.deck[p][i] == gold))
				preDeckDiscardTreasure++;
		}
		
		for(i = 0; i < discardCount; i++) {
			G.discard[p][i] = floor(Random() * (treasure_map + 1));
			
			if((G.discard[p][i] == copper) | (G.discard[p][i] == silver) | (G.discard[p][i] == gold))
				preDeckDiscardTreasure++;
		}
		
		for(i = 1; i < handCount; i++) {
			G.hand[p][i] = floor(Random() * (treasure_map + 1));
			
			if((G.hand[p][i] == copper) | (G.hand[p][i] == silver) | (G.hand[p][i] == gold))
				preHandTreasure++;
			
			else if (G.hand[p][i] == adventurer)
				preAdventurerHandCount++;
		}
		
		//Make the first card in the player's hand Adventurer
		G.hand[p][0] = adventurer;
		
		failed = myassert(playCard(0, 0, 0, 0, &G) == 0, "Checking if Adventurer can be played", failed);
		
		postPlayedCardCount = G.playedCardCount;
		
		//The number of Treasure cards that should be drawn is 2 unless there's less than 2 Treasure in the combination of the deck and the discard
		if(preDeckDiscardTreasure >= 2)
			numDrawn = 2;
		
		else
			numDrawn = preDeckDiscardTreasure;
		
		//Counts the number of Treasure card in deck, discard, and hand after Adventurer is played
		for(i = 0; i < G.deckCount[p]; i++) {
			if((G.deck[p][i] == copper) | (G.deck[p][i] == silver) | (G.deck[p][i] == gold))
				postDeckDiscardTreasure++;
		}
		
		for(i = 0; i < G.discardCount[p]; i++) {
			if((G.discard[p][i] == copper) | (G.discard[p][i] == silver) | (G.discard[p][i] == gold))
				postDeckDiscardTreasure++;
		}
		
		for(i = 0; i < G.handCount[p]; i++) {
			if((G.hand[p][i] == copper) | (G.hand[p][i] == silver) | (G.hand[p][i] == gold))
				postHandTreasure++;
			
			else if (G.hand[p][i] == adventurer)
				postAdventurerHandCount++;
		}
		
		for(i = 0; i < G.playedCardCount; i++) {
			if((G.playedCards[i] == copper) | (G.playedCards[i] == silver) | (G.playedCards[i] == gold))
				postDeckDiscardTreasure++;
		}
		
		//Uses logic to assign flags
		if(G.handCount[p] == handCount + numDrawn - 1)
			handCountCheck = 1;
		
		if((G.deckCount[p] + G.discardCount[p] + G.playedCardCount) == deckCount + discardCount - numDrawn + 1)
			deckDiscardCountCheck = 1;
		
		if(postDeckDiscardTreasure == (preDeckDiscardTreasure - numDrawn))
			deckDiscardTreasureCheck = 1;
		
		if(postHandTreasure == (preHandTreasure + numDrawn))
			handTreasureCheck = 1;
		
		if(postAdventurerHandCount == (preAdventurerHandCount - 1))
			adventurerHandCheck = 1;
		
		else 
			numFailed++;
		
		//Calls assertions based on flags and prints descriptive messages
		//failed = myassert(handCountCheck, "Checking if hand size increased by correct amount", failed);
		
		//failed = myassert(deckDiscardCountCheck, "Checking if deck/discard/played size decreased by correct amount", failed);
		
		//failed = myassert(deckDiscardTreasureCheck, "Checking if number of treasure cards in deck/discard/played decreased by correct amount", failed);
		
		//failed = myassert(handTreasureCheck, "Checking if number of treasures in hand increased by correct amount", failed);
		
		failed = myassert(adventurerHandCheck, "Checking if an Adventurer was removed from the hand", failed);
		
		//Prints data for each test if the static PRINT value is set to 1
		if(PRINT && (adventurerHandCheck == 0)) {
			printf("Num treasure cards drawn: %d\n", numDrawn);
			printf("Hand Size Before: %d\n", handCount);
			printf("Hand Size After: %d\n", G.handCount[p]);
			//printf("Deck Size Before: %d\n", deckCount);
			//printf("Deck Size After: %d\n", G.deckCount[p]);
			//printf("Discard Size Before: %d\n", discardCount);
			//printf("Discard Size After: %d\n", G.discardCount[p]);
			//printf("Played Size Before: 0\n");
			//printf("Played Size After: %d\n", postPlayedCardCount);
			//printf("Deck + Discard + Played Before: %d\n", deckCount + discardCount);
			//printf("Deck + Discard + Played After: %d\n", G.deckCount[p] + G.discardCount[p] + G.playedCardCount);
			//printf("Number of Treasure Cards in Deck + Discard + Played before: %d\n", preDeckDiscardTreasure);
			//printf("Number of Treasure Cards in Deck + Discard + Played after: %d\n", postDeckDiscardTreasure);
			//printf("Number of Treasure Cards in Hand before: %d\n", preHandTreasure);
			//printf("Number of Treasure Cards in Hand after: %d\n", postHandTreasure);
			printf("Number of Adventurer Cards in Hand before: %d\n", preAdventurerHandCount);
			printf("Number of Adventurer Cards in Hand after: %d\n", postAdventurerHandCount);
		} 
	} 
	
	checkasserts(failed);
	printf("Number of Adventurer remaining in hand fails: %d/%d.\n", numFailed, NUM_TESTS);
	
	return 0;
}
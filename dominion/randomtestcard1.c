#include "dominion.h"
#include "myassert.h"
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define NUM_TESTS 1000000

//Tests Feast card functionality

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
	int choice;						//Which card is gained by Feast
	int cost;						//Cost of the selected card
	int cur_test;
	int players;
	int p;
	int deckCount;
	int discardCount;
	int handCount;
	int numActions;
	int feastCountDeckBefore;		//Number of Feast cards in deck before Feast is played
	int feastCountHandBefore;		//Number of Feast cards in hand before Feast is played (excluding the one played)
	int feastCountDiscardBefore;	//Number of Feast cards in discard before Feast is played
	int feastCountDeckAfter;		//Number of Feast cards in deck after Feast is played
	int feastCountHandAfter;		//Number of Feast cards in hand after Feast is played
	int feastCountDiscardAfter;		//Number of Feast cards in discard after Feast is played
	int choiceCountBefore;			//Number of cards that are of the type 'choice' in discard before Feast is played
	int choiceCountAfter;			//Number of cards that are of the type 'choice' in discard after Feast is played
	int flag;						//Between 0 and 1, randomly. If below 0.1, the aupply of the chosen card is set to 0.
	int notInDeck;					//1 if there is no change in the number of Feasts in deck before and after Feast is played, 0 otherwise.
	int notInHand;					//1 if there is no change in the number of Feasts in hand before and after Feast is played (besides the one played), 0 otherwise.
	int notInDiscard;				//1 if there is no change in the number of Feasts in discard before and after Feast is played, 0 otherwise.
	int cardGained;					//1 if the card was gained to the discard, 0 otherwise.
	int handSizeCheck;				//1 if the handSize has decreased by 1 after playing Feast, 0 otherwise.
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	
	SelectStream(2);
	PutSeed(seedVal);
	
	for(cur_test = 1; cur_test <= NUM_TESTS; cur_test++) {
		flag = Random();
		choice = floor(Random() * (treasure_map + 1));	//randomly picks any card as the one being gained by Feast
		cost = getCost(choice);							//gets the cost of the chosen card
		players = ceil(Random() * 3) + 1;
		p = ceil(Random() * players);
		deckCount = floor(Random() * MAX_DECK);
		discardCount = floor(Random() * MAX_DECK);
		handCount = floor(Random() * MAX_HAND);
		numActions = floor(Random() * 15) + 1; 
		
		feastCountDeckBefore = 0;
		feastCountHandBefore = 0;
		feastCountDiscardBefore = 0;
		feastCountDeckAfter = 0;
		feastCountHandAfter = 0;
		feastCountDiscardAfter = 0;
		choiceCountBefore = 0;
		choiceCountAfter = 0;
		notInDeck = 0;
		notInDiscard = 0;
		notInHand = 0;
		cardGained = 0;
		handSizeCheck = 0;
		
		initializeGame(players, k , 5, &G);
		G.numPlayers = players;
		G.whoseTurn = p;
		G.phase = 0;
		G.deckCount[p] = deckCount;
		G.handCount[p] = handCount;
		G.numActions = numActions;
		G.numBuys = floor(Random() * 15) + 1;
		G.playedCardCount = 0;
		
		if(flag < 0.1)
			G.supplyCount[choice] = 0;
		
		else
			G.supplyCount[choice] = ceil(Random() * 10);
		
		//G.supplyCount[choice] = 10;
		
		G.hand[p][0] = feast;
		
		//If the chosen card costs too much or there's no copies of it left, should return -1
		if((cost > 5) || (G.supplyCount[choice] <= 0))
			failed = myassert(playCard(0, choice, 0, 0, &G) != 0, "Checking if Feast can't be played", failed);
		
		//Otherwise, run other checks
		else {
			for(i = 0; i < deckCount; i++) {
				G.deck[p][i] = floor(Random() * (treasure_map + 1));
				
				if(G.deck[p][i] == feast)
					feastCountDeckBefore++;
			}
			
			for(i = 0; i < discardCount; i++) {
				G.discard[p][i] = floor(Random() * (treasure_map + 1));
				
				if(G.discard[p][i] == feast)
					feastCountDiscardBefore++;
				
				if(G.discard[p][i] == choice)
					choiceCountBefore++;
			}
			
			for(i = 1; i < handCount; i++) {
				G.hand[p][i] = floor(Random() * (treasure_map + 1));
				
				if(G.hand[p][i] == feast)
					feastCountHandBefore++;
			}
					
			failed = myassert(playCard(0, choice, 0, 0, &G) == 0, "Checking if Feast can be played", failed);
			
			for(i = 0; i < G.deckCount[p]; i++) {
				if(G.deck[p][i] == feast)
					feastCountDeckAfter++;
			}
			
			for(i = 0; i < G.discardCount[p]; i++) {
				if(G.discard[p][i] == feast)
					feastCountDiscardAfter++;
				
				if(G.discard[p][i] == choice)
					choiceCountAfter++;
			}
			
			for(i = 0; i < G.handCount[p]; i++) {
				if(G.hand[p][i] == feast)
					feastCountHandAfter++;
			}
			
			if(feastCountDeckAfter == feastCountDeckBefore)
				notInDeck = 1;
			
			if(feastCountDiscardAfter == feastCountDiscardBefore)
				notInDiscard = 1;
			
			if(feastCountHandAfter == feastCountHandBefore)
				notInHand = 1;
			
			if((choiceCountAfter - choiceCountBefore) == 1)
				cardGained = 1;
			
			if(G.handCount[p] == (handCount - 1))
				handSizeCheck = 1;
			
			failed = myassert(notInDeck, "Checking if Feast is no longer in deck", failed);
			
			failed = myassert(notInHand, "Checking if Feast is no longer in hand", failed);
			
			failed = myassert(notInDiscard, "Checking if Feast is no longer in discard", failed);
			
			failed = myassert(cardGained, "Checking if card added to discard", failed);
			
			failed = myassert(handSizeCheck, "Checking if hand size decreased by 1", failed);
		}
	} 
	
	checkasserts(failed);
	
	return 0;
}
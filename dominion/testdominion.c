#include "dominion.h"
#include "myassert.h"
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define CHOICETRIES 5
#define MAXCARDSPLAYEDPERTURN 10
#define BUYTRIES 10
#define KINGDOMCARDBUYTRIES 10

//Tries to play a game of Dominion
int failed = 0;

void actionPhase(struct gameState* g) {
	int i, j, cardToPlay, choice1, choice2, choice3;
	int cardPlayed = 0;
	int numPlayed = 0;
	char cardName[256];
	for(i = 0; i < numHandCards(g); i++) {
		for(j = 0; j < CHOICETRIES; j++) {
			cardToPlay = handCard(i, g);
			choice1 = floor(Random() * 27); 
			choice2 = floor(Random() * 27); 
			choice3 = floor(Random() * 27); 
			
			if ((cardToPlay == remodel) || (cardToPlay == salvager))
				choice1 = floor(Random() * numHandCards(g));
			
			else if (cardToPlay == mine) {
				choice1 = floor(Random() * numHandCards(g));
				choice2 = floor(Random() * 3 + 4);	//Copper to Gold
			}
			
			else if (cardToPlay == ambassador) {
				choice1 = floor(Random() * numHandCards(g));
				choice2 = floor(Random() * 3);	//0 to 2	
			}
			
			else if (cardToPlay == baron)
				choice1 = floor(Random() * 2 + 1);	//1 or 2
			
			else if (cardToPlay == minion) 
				choice1 = floor(Random() * 2 + 1);	//1 or 2
			
			else if (cardToPlay == steward) {
				choice1 = floor(Random() * 3 + 1);	//1 to 3
				choice2 = floor(Random() * numHandCards(g));
				choice3 = floor(Random() * numHandCards(g));
			}
			
			if (playCard(i, choice1, choice2, choice3, g) == 0) {
				cardNumToName(cardToPlay, cardName);
				printf("Player %d played %s.\n", whoseTurn(g), cardName);
				i = 0;
				cardPlayed = 1;
				numPlayed++;
				break;
			}
		}
		
		if (numPlayed > MAXCARDSPLAYEDPERTURN)
			break;
	}
	
	if (cardPlayed == 0)
		printf("Player %d didn't play any cards this turn.\n", whoseTurn(g));
}

void buyPhase(struct gameState* g, int k[10]) {
	int cardBought = 0;
	int i, j, kCard, tCard, vCard;
	int choice;
	char cardName[256];
	for(i = 0; i < BUYTRIES; i++) {
		choice = Random();
		
		if (choice < 0.33) {	//tries to buy Kingdom Card
			for (j = 0; j < KINGDOMCARDBUYTRIES; j++) {
				kCard = floor(Random() * 10);
				
				if (buyCard(k[kCard], g) == 0) {
					cardNumToName(k[kCard], cardName);
					printf("Player %d bought %s.\n", whoseTurn(g), cardName);
					cardBought = 1;
					break;
				}
			}
		}
		
		else if (choice < 0.67) {	//tries to buy Treasure Card
			tCard = gold;
			
			if (buyCard(tCard, g) == 0) {
				cardNumToName(tCard, cardName);
				printf("Player %d bought %s.\n", whoseTurn(g), cardName);
				cardBought = 1;
			}
			
			else {
				tCard = silver;
			
				if (buyCard(tCard, g) == 0) {
					cardNumToName(tCard, cardName);
					printf("Player %d bought %s.\n", whoseTurn(g), cardName);
					cardBought = 1;
				}
			
				else {
					tCard = copper;
					
					if (buyCard(tCard, g) == 0) {
						cardNumToName(tCard, cardName);
						printf("Player %d bought %s.\n", whoseTurn(g), cardName);
						cardBought = 1;
					}
				}
			}
		}
		
		else {	//tries to buy Victory Card
			vCard = province;
			
			if (buyCard(vCard, g) == 0) {
				cardNumToName(vCard, cardName);
				printf("Player %d bought %s.\n", whoseTurn(g), cardName);
				cardBought = 1;
			}
			
			else {
				vCard = duchy;
			
				if (buyCard(vCard, g) == 0) {
					cardNumToName(vCard, cardName);
					printf("Player %d bought %s.\n", whoseTurn(g), cardName);
					cardBought = 1;
				}
			
				else {
					vCard = estate;
					
					if (buyCard(vCard, g) == 0) {
						cardNumToName(vCard, cardName);
						printf("Player %d bought %s.\n", whoseTurn(g), cardName);
						cardBought = 1;
					}
				}
			}
		}
	}
	
	if(cardBought == 0)
		printf("Player %d didn't buy any cards this turn.\n", whoseTurn(g));
}

int main(int argc, char* argv[]) {
	//Makes sure only 1 argument is given: the seed. Returns -1 otherwise.
	if (argc != 2) {
		printf("Invalid number of arguments.\n"); 
		return -1;
	}
	
	else if (atoi(argv[1]) <= 0) {
		printf("Invalid seed. Seed value must a positive number.\n");
		return -1;
	}
	
	int i, players, size, kcard, seedVal, numVictory, numCurse, curGame;
	int k[10];
	int winner[MAX_PLAYERS];
	char name[256];
	struct gameState state;
	
	seedVal = atoi(argv[1]);	//seed value
	
	//Checks card costs
	failed = myassert(getCost(curse) == 0, "Curse should cost 0", failed);
	failed = myassert(getCost(estate) == 2, "Estate should cost 2", failed);
	failed = myassert(getCost(duchy) == 5, "Duchy should cost 5", failed);
	failed = myassert(getCost(province) == 8, "Province should cost 8", failed);
	failed = myassert(getCost(copper) == 0, "Copper should cost 0", failed);
	failed = myassert(getCost(silver) == 3, "Silver should cost 3", failed);
	failed = myassert(getCost(gold) == 6, "Gold should cost 6", failed);
	failed = myassert(getCost(adventurer) == 6, "Adventurer should cost 6", failed);
	failed = myassert(getCost(council_room) == 5, "Council Room should cost 5", failed);
	failed = myassert(getCost(feast) == 4, "Feast should cost 4", failed);
	failed = myassert(getCost(gardens) == 4, "Gardens should cost 4", failed);
	failed = myassert(getCost(mine) == 5, "Mine should cost 5", failed);
	failed = myassert(getCost(remodel) == 4, "Remodel should cost 4", failed);
	failed = myassert(getCost(smithy) == 4, "Smithy should cost 4", failed);
	failed = myassert(getCost(village) == 3, "Village should cost 3", failed);
	failed = myassert(getCost(baron) == 4, "Baron should cost 4", failed);
	failed = myassert(getCost(great_hall) == 3, "Great Hall should cost 3", failed);
	failed = myassert(getCost(minion) == 5, "Minion should cost 5", failed);
	failed = myassert(getCost(steward) == 3, "Steward should cost 3", failed);
	failed = myassert(getCost(tribute) == 5, "Tribute should cost 5", failed);
	failed = myassert(getCost(ambassador) == 3, "Ambassador should cost 3", failed);
	failed = myassert(getCost(cutpurse) == 4, "Cutpurse should cost 4", failed);
	failed = myassert(getCost(embargo) == 2, "Embargo should cost 2", failed);
	failed = myassert(getCost(outpost) == 5, "Outpost should cost 5", failed);
	failed = myassert(getCost(salvager) == 4, "Salvager should cost 4", failed);
	failed = myassert(getCost(sea_hag) == 4, "Sea Hag should cost 4", failed);
	failed = myassert(getCost(treasure_map) == 4, "Treaasure Map should cost 4", failed);
	
	for(curGame = 0; curGame < 100; curGame++) {
		//Initializes random number generator
		seedVal++;
		SelectStream(2);
		PutSeed(seedVal);
		
		//Set number of players
		players = ceil(Random() * 3) + 1;	//2 to 4
		
		//Select 10 Kingdom Cards
		int possibleCards[20] = {adventurer, 
								 council_room,
								 feast,
								 gardens,
								 mine,
								 remodel,
								 smithy,
								 village,
								 baron,
								 great_hall,
								 minion,
								 steward, 
								 tribute,
								 ambassador,
								 cutpurse,
								 embargo,
								 outpost,
								 salvager,
								 sea_hag,
								 treasure_map};
								 
		size = 20;
		
		for(i = 0; i < 10; i++) {
			kcard = floor(Random() * size);
			k[i] = possibleCards[kcard];
			size--;
			
			if(kcard != size)
				possibleCards[kcard] = possibleCards[size];
		}
		
		//Initialize game
		initializeGame(players, k, seedVal, &state);
		
		//Checks supply
		if (players == 2) {
			numVictory = 8;
			numCurse = 10;
		}
		
		else if (players == 3) {
			numVictory = 8;
			numCurse = 10;
		}
		
		else if (players == 4) {
			numVictory = 8;
			numCurse = 10;
		}
		
		else {
			printf("Invalid number of players: %d.\n", players);
			return 0;
		}
			
		failed = myassert(state.supplyCount[curse] == numCurse, "Curse supply", failed);
		failed = myassert(state.supplyCount[estate] == numVictory, "Estate supply", failed);
		failed = myassert(state.supplyCount[duchy] == numVictory, "Duchy supply", failed);
		failed = myassert(state.supplyCount[province] == numVictory, "Province supply", failed);
		failed = myassert(state.supplyCount[copper] == (60 - (7 * players)), "Copper supply", failed);
		failed = myassert(state.supplyCount[silver] == 40, "Silver supply", failed);
		failed = myassert(state.supplyCount[gold] == 30, "Gold supply", failed);
		
		for(i = 0; i < 10; i++) {
			cardNumToName(k[i], name);
			strcat(name, " supply");
			
			if ((k[i] == gardens) || (k[i] == great_hall))
				failed = myassert(state.supplyCount[k[i]] == numVictory, name, failed);
			
			else
				failed = myassert(state.supplyCount[k[i]] == 10, name, failed);
		}
		
		while (isGameOver(&state) == 0) {
			actionPhase(&state);
			buyPhase(&state, k);
			endTurn(&state);
		}
		
		getWinners(winner, &state);
		
		for(i = 0; i < players; i++) {
			if (winner[i] == 1)
				printf("Player %d won.\n", i);
		}
	}
	
	checkasserts(failed);
	
	return 1;
}
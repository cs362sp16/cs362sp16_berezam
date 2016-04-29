#include "dominion.h"
#include "myassert.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define PLAYERS 2

//Tests getCost function, prototype was added to dominion.h to this end

int failed = 0;

int main() {
	struct gameState state;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	initializeGame(PLAYERS, k , 5, &state);
	
	//Checks to see if the cost value used for 5 arbitrarily chosen cards matches those found on the Dominion Wiki
	failed = myassert(getCost(council_room) == 5, "Checking Council Room costs 5", failed);
	failed = myassert(getCost(smithy) == 4, "Checking Smithy costs 4", failed);
	failed = myassert(getCost(remodel) == 4, "Checking Remodel costs 4", failed);
	failed = myassert(getCost(outpost) == 5, "Checking Outpost costs 5", failed);
	failed = myassert(getCost(duchy) == 5, "Checking Duchy costs 5", failed);
	
	checkasserts(failed);
	
	return 0;
}
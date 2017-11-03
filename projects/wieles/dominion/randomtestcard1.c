/*
* randomtestcard1.c
* Random tests for the Smithy card in Dominion
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

int checkSmithyCard(struct gameState *post, int handPos) {
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));

	int i, r, p, preCards, postCards, preSmithy, postSmithy;

	p = pre.whoseTurn;

	r = cardEffect(smithy, 0, 0, 0, post, handPos, 0);

	if (r != 0)
		printf("FAIL. cardEffect did not return 0.\n");
	else
		printf("PASS. cardEffect returned 0.\n");

	//check hand count increased by 2 (draw 3 cards, discard Smithy)
	if (post->handCount[p] != pre.handCount[p] + 2)
		printf("FAIL. Total hand count incorrect.\n");
	else
		printf("PASS. Total hand count correct.\n");

	//check smithy card was discarded
	preSmithy = 0;
	postSmithy = 0;
	for (i = 0; i < pre.handCount[p]; i++) {
		if (pre.hand[p][i] == smithy) {
			preSmithy++;
		}
	}

	for (i = 0; i < post->handCount[p]; i++) {
		if (post->hand[p][i] == smithy) {
			postSmithy++;
		}
	}

	if (postSmithy != preSmithy - 1) 
		printf("FAIL. Smithy card not discarded.\n");
	else
		printf("PASS. Smithy card discarded.\n");

	//check deck + discard count decreased by 3
	preCards = pre.deckCount[p] + pre.discardCount[p];
	postCards = post->deckCount[p] + post->discardCount[p];
	if (postCards != preCards - 3)
		printf("FAIL. Total deck + discard count incorrect.\n");
	else
		printf("PASS. Total deck + discard count correct.\n");

	return 0;
}

int main() {
	int n, p, h;

	int seed = 1000;
	int numPlayers = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, 
		remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf("Testing Smithy Card.\n");

	SelectStream(2);
	PutSeed(3);

	initializeGame(numPlayers, k, seed, &G);

	for (n = 0; n < 2000; n++) {
		printf("\nTest %d:\n", n+1);

		//randomize player
		p = floor(Random() * 2);
		G.whoseTurn = p;

		//randomize hand count
		G.handCount[p] = floor(Random() * MAX_HAND);

		//randomize Smithy hand position
		h = floor(Random() * (G.handCount[p]));
		G.hand[p][h] = smithy;
		
		//randomize deck count
		G.deckCount[p] = floor(Random() * MAX_DECK);
		
		//randomize discard count
		G.discardCount[p] = floor(Random() * MAX_DECK);
		
		checkSmithyCard(&G, h);
	}

	return 0;
}
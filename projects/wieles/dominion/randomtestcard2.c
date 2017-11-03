/*
* randomtestcard2.c
* Random tests for the Salvager card in Dominion
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

int checkSalvagerCard(int c1, struct gameState *post, int handPos) {
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));

	int i, r, p, cost;
	int preSalvager, postSalvager, preSelect, postSelect;

	p = pre.whoseTurn;

	r = cardEffect(salvager, c1, 0, 0, post, handPos, 0);

	if (r != 0)
		printf("FAIL. cardEffect did not return 0.\n");
	else
		printf("PASS. cardEffect returned 0.\n");

	//check buys increased by 1
	if (post->numBuys != pre.numBuys + 1)
		printf("FAIL. Buys did not increase by 1.\n");
	else
		printf("PASS. Buys increased by 1.\n");

	//check hand count decreased by 2 (trashed card, discard Salvager)
	if (post->handCount[p] != pre.handCount[p] - 2){
		printf("FAIL. Hand count did not decrease by 2.\n");
		printf("Hand count before: %d, Hand count after: %d\n", pre.handCount[p], post->handCount[p]);
	}
	else
		printf("PASS. Hand count decreased by 2.\n");

	//check selected card was trashed
	preSelect = 0;
	postSelect = 0;
	for (i = 0; i < pre.handCount[p]; i++) {
		if (pre.hand[p][i] == pre.hand[p][c1])
			preSelect++;
	}
	for (i = 0; i < post->handCount[p]; i++) {
		if (post->hand[p][i] == pre.hand[p][c1])
			postSelect++;
	}
	if (pre.hand[p][c1] == salvager) {
		if (postSelect != preSelect - 2) {
			printf("FAIL. Selected card not trashed correctly.\n");
			printf("Selected card count before: %d, Selected card count after: %d\n", preSelect, postSelect);
		}
		else
			printf("PASS. Selected card trashed.\n");
	}
	else {
		if (postSelect != preSelect - 1) {
			printf("FAIL. Selected card not trashed correctly.\n");
			printf("Selected card count before: %d, Selected card count after: %d\n", preSelect, postSelect);
		}
		else
			printf("PASS. Selected card trashed.\n");
	}

	//check coins increased by selected card cost
	cost = getCost(pre.hand[p][c1]);
	if (post->coins != pre.coins + cost) {
		printf("FAIL. Trashed card cost incorrectly added to coins.\n");
		printf("Card: %d, Card cost: %d, Coin count before: %d, Coin count after: %d\n", pre.hand[p][c1], cost, pre.coins, post->coins);
	}
	else {
		printf("PASS. Trashed card cost added to coins.\n");
		printf("Card: %d, Card cost: %d, Coin count before: %d, Coin count after: %d\n", pre.hand[p][c1], cost, pre.coins, post->coins);
	}

	//check Salvager was discarded
	preSalvager = 0;
	postSalvager = 0;
	for (i = 0; i < pre.handCount[p]; i++) {
		if (pre.hand[p][i] == salvager)
			preSalvager++;
	}
	for (i = 0; i < post->handCount[p]; i++) {
		if (post->hand[p][i] == salvager)
			postSalvager++;
	}
	if (pre.hand[p][c1] == salvager) {
		if (postSalvager != preSalvager - 2) {
			printf("FAIL. Salvager card not discarded correctly.\n");
			printf("Salvager count before: %d, Salvager count after: %d\n", preSalvager, postSalvager);
		}
		else
			printf("PASS. Salvager card discarded.\n");
	}
	else {
		if (postSalvager != preSalvager - 1) {
			printf("FAIL. Salvager card not discarded correctly.\n");
			printf("Salvager count before: %d, Salvager count after: %d\n", preSalvager, postSalvager);
		}
		else
			printf("PASS. Salvager card discarded.\n");
	}
	
	

	//check deck and discard piles remained the same
	if (post->deckCount[p] != pre.deckCount[p])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (post->discardCount[p] != pre.discardCount[p])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	return 0;
}

int main() {
	int i, n, p, h, c, t;

	int k1[17] = {curse, estate, duchy, province, copper, silver, gold, 
		adventurer, council_room, feast, gardens, mine, 
		remodel, smithy, village, baron, great_hall};

	int seed = 1000;
	int numPlayers = 2;
	int k2[10] = {adventurer, council_room, feast, gardens, mine, 
		remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf("Testing Salvager Card.\n");

	SelectStream(2);
	PutSeed(3);

	initializeGame(numPlayers, k2, seed, &G);

	for (n = 0; n < 2000; n++) {
		printf("\nTest %d:\n", n+1);

		//randomize player
		p = floor(Random() * 2);
		G.whoseTurn = p;

		//randomize hand count
		G.handCount[p] = floor(Random() * MAX_HAND);

		//randomize cards in hand
		for (i = 0; i < G.handCount[p]; i++) {
			c = floor(Random() * 17);
			G.hand[p][i] = k1[c];
		}

		//randomize Salvager hand position
		h = floor(Random() * (G.handCount[p]));
		G.hand[p][h] = salvager;

		//randomize trashed card
		t = floor(Random() * (G.handCount[p]));
		if (t == h) {
			t++;
			if (t >= G.handCount[p]){
				t = 0;
			}
		}

		printf("Trashed card position: %d, Salvager card position: %d, Hand count: %d\n", t, h, G.handCount[p]);
		
		//randomize deck count
		G.deckCount[p] = floor(Random() * MAX_DECK);
		
		//randomize discard count
		G.discardCount[p] = floor(Random() * MAX_DECK);

		//get coin count
		updateCoins(p, &G, 0);
		
		checkSalvagerCard(t, &G, h);
	}

	return 0;
}
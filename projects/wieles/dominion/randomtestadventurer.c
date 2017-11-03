/*
* randomtestadventurer.c
* Random tests for the Adventurer card in Dominion
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

int checkAdventurerCard(struct gameState *post, int handPos) {
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	
	int i, r, p, preCards, postCards, preTreasure, postTreasure, numTreasure, preAdventurer, postAdventurer;

	p = pre.whoseTurn;

	r = cardEffect(adventurer, 0, 0, 0, post, handPos, 0);

	if (r != 0)
		printf("FAIL. cardEffect did not return 0.\n");
	else
		printf("PASS. cardEffect returned 0.\n");

	//get number of treasure cards in deck + discard
	numTreasure = 0;
	for (i = 0; i < pre.deckCount[p]; i++) {
		if (pre.deck[p][i] == copper || pre.deck[p][i] == silver || pre.deck[p][i] == gold) {
			numTreasure++;
		}
	}
	for (i = 0; i < pre.discardCount[p]; i++) {
		if (pre.discard[p][i] == copper || pre.discard[p][i] == silver || pre.discard[p][i] == gold) {
			numTreasure++;
		}
	}

	preCards = pre.deckCount[p] + pre.discardCount[p];
	postCards = post->deckCount[p] + post->discardCount[p];
	//if at least two treasure cards in deck + discard, 
	//check post deck + discard = pre deck + discard - 2
	if (numTreasure >= 2) {
		if (postCards != preCards - 2) {
			printf("FAIL. Total deck + discard count out of expected range.\n");
		}
		else {
			printf("PASS. Total deck + discard count is correct.\n");
		}
	}
	//if one treasure card in deck + discard, 
	//check post deck + discard = pre deck + discard - 1
	else if (numTreasure == 1) {
		if (postCards != preCards - 1) {
			printf("FAIL. Total deck + discard count out of expected range.\n");
		}
		else {
			printf("PASS. Total deck + discard count is correct.\n");
		}
	}
	//if no treasure cards in deck + discard, 
	//check post deck + discard = pre deck + discard
	else {
		if (postCards != preCards) {
			printf("FAIL. Total deck + discard count out of expected range.\n");
		}
		else {
			printf("PASS. Total deck + discard count is correct.\n");
		}
	}	

	//if at least two treasure cards in deck + discard, 
	//check hand increases by no more than 1 (draw two treasure cards, discard adventurer)
	if (numTreasure >= 2) {
		if (post->handCount[p] != pre.handCount[p] + 1) {
			printf("FAIL. Total hand count out of expected range.\n");
		}
		else {
			printf("PASS. Total hand count is correct.\n");
		}
	}

	//if one treasure card in deck + discard,
	//check hand count stays the same (draw one treasure card, discard adventurer)
	else if (numTreasure == 1) {
		if (post->handCount[p] != pre.handCount[p]) {
			printf("FAIL. Total hand count out of expected range.\n");
		}
		else {
			printf("PASS. Total hand count is correct.\n");
		}
	}
		
	//if no treasure cards in deck + discard,
	//check hand decreases by one (discard adventurer)
	else {
		if (post->handCount[p] != pre.handCount[p] - 1) {
			printf("FAIL. Total hand count out of expected range.\n");
		}
		else {
			printf("PASS. Total hand count is correct.\n");
		}
	}

	//check adventurer card was discarded
	preAdventurer = 0;
	postAdventurer = 0;
	for (i = 0; i < pre.handCount[p]; i++) {
		if (pre.hand[p][i] == adventurer) {
			preAdventurer++;
		}
	}

	for (i = 0; i < post->handCount[p]; i++) {
		if (post->hand[p][i] == adventurer) {
			postAdventurer++;
		}
	}

	if (postAdventurer != preAdventurer - 1) 
		printf("FAIL. Adventurer card count out of expected range.\n");
	
	else
		printf("PASS. Adventurer card count is correct.\n");

	//check treasure count increased correctly
	preTreasure = 0;
	postTreasure = 0;
	for (i = 0; i < pre.handCount[p]; i++) {
		if (pre.hand[p][i] == copper || pre.hand[p][i] == silver || pre.hand[p][i] == gold) {
			preTreasure++;
		}
	}
	for (i = 0; i < post->handCount[p]; i++) {
		if (post->hand[p][i] == copper || post->hand[p][i] == silver || post->hand[p][i] == gold) {
			postTreasure++;
		}
	}
	if (numTreasure >= 2) {
		if (postTreasure != preTreasure + 2) {
			printf("FAIL. Hand treasure count out of expected range.\n");
		}
		else {
			printf("PASS. Hand treasure count is correct.\n");
		}
	}
	else if (numTreasure == 1) {
		if (postTreasure != preTreasure + 1) {
			printf("FAIL. Hand treasure count out of expected range.\n");
		}
		else {
			printf("PASS. Hand treasure count is correct.\n");
		}
	}
	else {
		if (postTreasure != preTreasure) {
			printf("FAIL. Hand treasure count out of expected range.\n");
		}
		else {
			printf("PASS. Hand treasure count is correct.\n");
		}
	}

	return 0;
}

int main() {
	int i, n, p, h, c;

	int k[17] = {curse, estate, duchy, province, copper, silver, gold, 
		adventurer, council_room, feast, gardens, mine, 
		remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf("Testing Adventurer Card.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 2000; n++) {
		printf("\nTest %d:\n", n+1);

		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256); // fill game state with random bytes
		}
		//randomize player
		p = floor(Random() * 2);
		G.whoseTurn = p;

		//randomize hand count
		G.handCount[p] = floor(Random() * MAX_HAND);

		//randomize Adventurer hand position
		h = floor(Random() * (G.handCount[p]));
		G.hand[p][h] = adventurer;
		
		//randomize deck count
		G.deckCount[p] = floor(Random() * MAX_DECK);
		
		//randomize cards in deck
		for (i = 0; i < G.deckCount[p]; i++) {
			c = floor(Random() * 17);
			G.deck[p][i] = k[c];
		}
		
		//randomize discard count
		G.discardCount[p] = floor(Random() * MAX_DECK);
		
		//randomize card in discard
		for (i = 0; i < G.discardCount[p]; i++) {
			c = floor(Random() * 17);
			G.discard[p][i] = k[c];
		}
		checkAdventurerCard(&G, h);
	}

	return 0;
}
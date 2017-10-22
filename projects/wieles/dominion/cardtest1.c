/*
* Unit tests for Adventurer
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int seed = 1000;
	int numPlayers = 2;
	int player = 0;
	struct gameState G, initG, startG;
	int k[10] = {adventurer, embargo, village, minion, mine, 
				 cutpurse, sea_hag, tribute, smithy, council_room};

	int i, j;
	int startTreasureCount, endTreasureCount;
	int startAdventurerCount, endAdventurerCount;

	printf("Testing Adventurer Card\n");

	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = player;
	G.hand[player][0] = adventurer;

	memcpy(&initG, &G, sizeof(struct gameState));

	//test drawing different types of treasure cards
	printf("\nTest 1: Drawing each type of treasure card\n");
	for (i = copper; i <= gold; i++)
	{
		if (i == copper)
			printf("\nTesting copper cards\n");
		else if (i == silver)
			printf("\nTesting silver cards\n");
		else
			printf("\nTesting gold cards\n");

		G.handCount[player] = initG.handCount[player];
		for (j = 0; j < initG.handCount[player]; j++)
		{
			G.hand[player][j] = initG.hand[player][j];
		}

		startTreasureCount = 0;
		startAdventurerCount = 0;
		endTreasureCount = 0;
		endAdventurerCount = 0;

		for (j = 0; j < G.handCount[player]; j++)
		{
			if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold)
				startTreasureCount++;
			if (G.hand[player][j] == adventurer)
				startAdventurerCount++;
		}

		G.discardCount[player] = 0;
		G.playedCardCount = 0;

		G.deckCount[player] = 6;
		G.deck[player][0] = estate;
		G.deck[player][1] = i;
		G.deck[player][2] = village;
		G.deck[player][3] = i;
		G.deck[player][4] = i;
		G.deck[player][5] = duchy;

		memcpy(&startG, &G, sizeof(struct gameState));

		cardEffect(adventurer, 0, 0, 0, &G, 0, 0);

		for (j = 0; j < G.handCount[player]; j++)
		{
			if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold)
				endTreasureCount++;
			if (G.hand[player][j] == adventurer)
				endAdventurerCount++;
		}

		printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
		printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
		printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
		printf("Played card count before: %d, Played card count after: %d\n", startG.playedCardCount, G.playedCardCount);
		printf("Treasure hand count before: %d, Treasure hand count after: %d\n", startTreasureCount, endTreasureCount);
		printf("Adventurer hand count before: %d, Adventurer hand count after: %d\n", startAdventurerCount, endAdventurerCount);

		//check hand increased by 1 (2 added treasure, and discard Adventurer)
		if (G.handCount[player] != startG.handCount[player] + 1)
			printf("FAIL. Hand count did not increase by 1.\n");
		else
			printf("PASS. Hand count increased by 1.\n");

		if (G.discardCount[player] != startG.discardCount[player] + 1)
			printf("FAIL. Discard count did not increase by 1.\n");
		else
			printf("PASS. Discard count increased by 1.\n");

		if (G.deckCount[player] != startG.deckCount[player] - 3)
			printf("FAIL. Deck count did not decrease by 3.\n");
		else
			printf("PASS. Deck count decreased by 3.\n");

		if (G.playedCardCount != startG.playedCardCount + 1)
			printf("FAIL. Played card count did not increase by 1.\n");
		else
			printf("PASS. Played card count increased by 1.\n");

		if (endTreasureCount != startTreasureCount + 2)
			printf("FAIL. Did not add two treasure cards to hand.\n");
		else
			printf("PASS. Added two treasure cards to hand.\n");

		if (endAdventurerCount != startAdventurerCount - 1)
			printf("FAIL. Adventurer count did not decrease by 1.\n");
		else
			printf("PASS. Adventurer count decreased by 1.\n");
	}

	//-------------------------------------------------------------------------------
	printf("\nTest 2: No treasure cards in deck, and only one treasure card in discard\n");
	
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (j = 0; j < initG.handCount[player]; j++)
	{
		G.hand[player][j] = initG.hand[player][j];
	}

	startTreasureCount = 0;
	startAdventurerCount = 0;
	endTreasureCount = 0;
	endAdventurerCount = 0;

	for (j = 0; j < G.handCount[player]; j++)
	{
		if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold)
			startTreasureCount++;
		if (G.hand[player][j] == adventurer)
			startAdventurerCount++;
	}

	G.discardCount[player] = 4;
	G.discard[player][0] = estate;
	G.discard[player][1] = copper;
	G.discard[player][2] = village;
	G.discard[player][3] = mine;

	G.playedCardCount = 0;

	G.deckCount[player] = 6;
	G.deck[player][0] = estate;
	G.deck[player][1] = mine;
	G.deck[player][2] = village;
	G.deck[player][3] = duchy;
	G.deck[player][4] = smithy;
	G.deck[player][5] = duchy;

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(adventurer, 0, 0, 0, &G, 0, 0);

	for (j = 0; j < G.handCount[player]; j++)
	{
		if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold)
			endTreasureCount++;
		if (G.hand[player][j] == adventurer)
			endAdventurerCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Played card count before: %d, Played card count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Treasure hand count before: %d, Treasure hand count after: %d\n", startTreasureCount, endTreasureCount);
	printf("Adventurer hand count before: %d, Adventurer hand count after: %d\n", startAdventurerCount, endAdventurerCount);

	if (G.handCount[player] != startG.handCount[player])
		printf("FAIL. Hand count changed.\n");
	else
		printf("PASS. Hand count did not change.\n");

	if (G.discardCount[player] != 9 || G.deckCount[player] != 0)
		printf("FAIL. Did not go through both deck and discard.\n");
	else
		printf("PASS. Went through entire deck and discard, and non-treasure drawn cards added to discard.\n");

	if (G.playedCardCount != startG.playedCardCount + 1)
		printf("FAIL. Played card count did not increase by 1.\n");
	else
		printf("PASS. Played card count increased by 1.\n");

	if (endTreasureCount != startTreasureCount + 1)
		printf("FAIL. Treasure hand count did not increase by 1.\n");
	else
		printf("PASS. Added treasure card to hand.\n");

	if (endAdventurerCount != startAdventurerCount - 1)
		printf("FAIL. Adventurer count did not decrease by 1.\n");
	else
		printf("PASS. Adventurer count decreased by 1.\n");

	//-------------------------------------------------------------
	printf("\nTest 3: No treasure cards in deck or discard\n");
	
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (j = 0; j < initG.handCount[player]; j++)
	{
		G.hand[player][j] = initG.hand[player][j];
	}

	startTreasureCount = 0;
	startAdventurerCount = 0;
	endTreasureCount = 0;
	endAdventurerCount = 0;

	for (j = 0; j < G.handCount[player]; j++)
	{
		if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold)
			startTreasureCount++;
		if (G.hand[player][j] == adventurer)
			startAdventurerCount++;
	}

	G.discardCount[player] = 4;
	G.discard[player][0] = estate;
	G.discard[player][1] = smithy;
	G.discard[player][2] = village;
	G.discard[player][3] = mine;

	G.playedCardCount = 0;

	G.deckCount[player] = 6;
	G.deck[player][0] = estate;
	G.deck[player][1] = mine;
	G.deck[player][2] = village;
	G.deck[player][3] = duchy;
	G.deck[player][4] = smithy;
	G.deck[player][5] = duchy;

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(adventurer, 0, 0, 0, &G, 0, 0);

	for (j = 0; j < G.handCount[player]; j++)
	{
		if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold)
			endTreasureCount++;
		if (G.hand[player][j] == adventurer)
			endAdventurerCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Played card count before: %d, Played card count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Treasure hand count before: %d, Treasure hand count after: %d\n", startTreasureCount, endTreasureCount);
	printf("Adventurer hand count before: %d, Adventurer hand count after: %d\n", startAdventurerCount, endAdventurerCount);

	if (G.handCount[player] != startG.handCount[player] - 1)
		printf("FAIL. Hand count did not decrease by 1.\n");
	else
		printf("PASS. Hand count decreased by 1.\n");

	if (G.discardCount[player] != 10 || G.deckCount[player] != 0)
		printf("FAIL. Did not go through both deck and discard.\n");
	else
		printf("PASS. Went through entire deck and discard, and non-treasure drawn cards added to discard.\n");

	if (G.playedCardCount != startG.playedCardCount + 1)
		printf("FAIL. Played card count did not increase by 1.\n");
	else
		printf("PASS. Played card count increased by 1.\n");

	if (endTreasureCount != startTreasureCount)
		printf("FAIL. Treasure hand count changed.\n");
	else
		printf("PASS. Treasure hand count did not change.\n");

	if (endAdventurerCount != startAdventurerCount - 1)
		printf("FAIL. Adventurer count did not decrease by 1.\n");
	else
		printf("PASS. Adventurer count decreased by 1.\n");

	printf("\nAventurer Testing Complete\n\n");

	return 0;
}
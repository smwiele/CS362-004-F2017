/*
* Unit tests for salvagerCardEffect()
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
	int choice1;
	int i;
	int startChoice1Count, endChoice1Count;
	int startSalvagerCount, endSalvagerCount;
	int cardCost;

	printf("Testing Salvager Card\n");

	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = player;

	memcpy(&initG, &G, sizeof(struct gameState));

	printf("\nTest 1: Trash adventurer card.\n");

	choice1 = adventurer;
	cardCost = getCost(choice1);
	G.hand[player][2] = choice1;
	G.hand[player][1] = salvager;

	startChoice1Count = 0;
	startSalvagerCount = 0;
	endChoice1Count = 0;
	endSalvagerCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == salvager)
			startSalvagerCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(salvager, 2, 0, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == salvager)
			endSalvagerCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Adventurer hand count before: %d, Adventurer hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Salvager hand count before: %d, Salvager hand count after: %d\n", startSalvagerCount, endSalvagerCount);
	printf("Buy count before: %d, Buy count after: %d\n", startG.numBuys, G.numBuys);
	printf("Coin count before: %d, Coin count after: %d\n", startG.coins, G.coins);

	if (G.handCount[player] != startG.handCount[player] - 2)
		printf("FAIL. Hand count did not decrease by 2.\n");
	else
		printf("PASS. Hand count decreased by 2.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount + 1)
		printf("FAIL. Played card count did not increase.\n");
	else
		printf("PASS. Played card count increased by 1.\n");

	if (endChoice1Count != startChoice1Count - 1)
		printf("FAIL. Adventurer card count did not change.\n");
	else
		printf("PASS. Adventurer card count decreased by 1\n");

	if (endSalvagerCount != startSalvagerCount - 1)
		printf("FAIL. Salvager card count did not change.\n");
	else
		printf("PASS. Salvager card count decreased by 1\n");

	if (G.numBuys != startG.numBuys + 1)
		printf("FAIL. Buys count incorrect.\n");
	else
		printf("PASS. Buys increased by 1.\n");

	if (G.coins != startG.coins + cardCost)
		printf("FAIL. Coin count incorrect.\n");
	else
		printf("PASS. Coin count correct.\n");

	//------------------------------------------------------
	printf("\nTest 2: Trash copper card.\n");
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (i = 0; i < initG.handCount[player]; i++)
	{
		G.hand[player][i] = initG.hand[player][i];
	}

	choice1 = copper;
	cardCost = getCost(choice1);
	G.hand[player][0] = choice1;
	G.hand[player][1] = salvager;

	startChoice1Count = 0;
	startSalvagerCount = 0;
	endChoice1Count = 0;
	endSalvagerCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == salvager)
			startSalvagerCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(salvager, 0, 0, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == salvager)
			endSalvagerCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Copper hand count before: %d, Copper hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Salvager hand count before: %d, Salvager hand count after: %d\n", startSalvagerCount, endSalvagerCount);
	printf("Buy count before: %d, Buy count after: %d\n", startG.numBuys, G.numBuys);
	printf("Coin count before: %d, Coin count after: %d\n", startG.coins, G.coins);

	if (G.handCount[player] != startG.handCount[player] - 2)
		printf("FAIL. Hand count did not decrease by 2.\n");
	else
		printf("PASS. Hand count decreased by 2.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount + 1)
		printf("FAIL. Played card count did not increase.\n");
	else
		printf("PASS. Played card count increased by 1.\n");

	if (endChoice1Count != startChoice1Count - 1)
		printf("FAIL. Copper card count did not change.\n");
	else
		printf("PASS. Copper card count decreased by 1\n");

	if (endSalvagerCount != startSalvagerCount - 1)
		printf("FAIL. Salvager card count did not change.\n");
	else
		printf("PASS. Salvager card count decreased by 1\n");

	if (G.numBuys != startG.numBuys + 1)
		printf("FAIL. Buys count incorrect.\n");
	else
		printf("PASS. Buys increased by 1.\n");

	if (G.coins != startG.coins + cardCost)
		printf("FAIL. Coin count incorrect.\n");
	else
		printf("PASS. Coin count correct.\n");

	//------------------------------------------------------
	printf("\nTest 3: Trash curse card.\n");
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (i = 0; i < initG.handCount[player]; i++)
	{
		G.hand[player][i] = initG.hand[player][i];
	}

	choice1 = curse;
	cardCost = getCost(choice1);
	G.hand[player][0] = choice1;
	G.hand[player][1] = salvager;

	startChoice1Count = 0;
	startSalvagerCount = 0;
	endChoice1Count = 0;
	endSalvagerCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == salvager)
			startSalvagerCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(salvager, 0, 0, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == salvager)
			endSalvagerCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Curse hand count before: %d, Curse hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Salvager hand count before: %d, Salvager hand count after: %d\n", startSalvagerCount, endSalvagerCount);
	printf("Buy count before: %d, Buy count after: %d\n", startG.numBuys, G.numBuys);
	printf("Coin count before: %d, Coin count after: %d\n", startG.coins, G.coins);

	if (G.handCount[player] != startG.handCount[player] - 2)
		printf("FAIL. Hand count did not decrease by 2.\n");
	else
		printf("PASS. Hand count decreased by 2.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount + 1)
		printf("FAIL. Played card count did not increase.\n");
	else
		printf("PASS. Played card count increased by 1.\n");

	if (endChoice1Count != startChoice1Count - 1)
		printf("FAIL. Curse card count did not change.\n");
	else
		printf("PASS. Curse card count decreased by 1\n");

	if (endSalvagerCount != startSalvagerCount - 1)
		printf("FAIL. Salvager card count did not change.\n");
	else
		printf("PASS. Salvager card count decreased by 1\n");

	if (G.numBuys != startG.numBuys + 1)
		printf("FAIL. Buys count incorrect.\n");
	else
		printf("PASS. Buys increased by 1.\n");

	if (G.coins != startG.coins + cardCost)
		printf("FAIL. Coin count incorrect.\n");
	else
		printf("PASS. Coin count correct.\n");

	//------------------------------------------------------
	printf("\nTest 4: Trash treasure map card.\n");
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (i = 0; i < initG.handCount[player]; i++)
	{
		G.hand[player][i] = initG.hand[player][i];
	}

	choice1 = treasure_map;
	cardCost = getCost(choice1);
	G.hand[player][0] = choice1;
	G.hand[player][1] = salvager;

	startChoice1Count = 0;
	startSalvagerCount = 0;
	endChoice1Count = 0;
	endSalvagerCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == salvager)
			startSalvagerCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(salvager, 0, 0, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == salvager)
			endSalvagerCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Treasure Map hand count before: %d, Treasure Map hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Salvager hand count before: %d, Salvager hand count after: %d\n", startSalvagerCount, endSalvagerCount);
	printf("Buy count before: %d, Buy count after: %d\n", startG.numBuys, G.numBuys);
	printf("Coin count before: %d, Coin count after: %d\n", startG.coins, G.coins);

	if (G.handCount[player] != startG.handCount[player] - 2)
		printf("FAIL. Hand count did not decrease by 2.\n");
	else
		printf("PASS. Hand count decreased by 2.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount + 1)
		printf("FAIL. Played card count did not increase.\n");
	else
		printf("PASS. Played card count increased by 1.\n");

	if (endChoice1Count != startChoice1Count - 1)
		printf("FAIL. Treasure Map card count did not change.\n");
	else
		printf("PASS. Treasure Map card count decreased by 1\n");

	if (endSalvagerCount != startSalvagerCount - 1)
		printf("FAIL. Salvager card count did not change.\n");
	else
		printf("PASS. Salvager card count decreased by 1\n");

	if (G.numBuys != startG.numBuys + 1)
		printf("FAIL. Buys count incorrect.\n");
	else
		printf("PASS. Buys increased by 1.\n");

	if (G.coins != startG.coins + cardCost)
		printf("FAIL. Coin count incorrect.\n");
	else
		printf("PASS. Coin count correct.\n");

	printf("\nSalvager Testing Complete\n\n");

	return 0;
}
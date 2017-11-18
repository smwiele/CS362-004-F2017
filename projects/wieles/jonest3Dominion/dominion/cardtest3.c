/*
* Unit tests for mineCardEffect()
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
	int choice1, choice2;
	struct gameState G, initG, startG;
	int k[10] = {adventurer, embargo, village, minion, mine, 
				 cutpurse, sea_hag, tribute, smithy, council_room};

	int startChoice1Count, endChoice1Count;
	int startChoice2Count, endChoice2Count;
	int startMineCount, endMineCount;
	int i;

	printf("Testing Mine Card\n");

	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = player;

	memcpy(&initG, &G, sizeof(struct gameState));

	//----------------------------------------------------------
	printf("\nTest 1: Trash copper to gain silver\n");
	choice1 = copper;
	choice2 = silver;
	G.hand[player][0] = choice1;
	G.hand[player][1] = mine;

	startChoice1Count = 0;
	startChoice2Count = 0;
	startMineCount = 0;
	endChoice1Count = 0;
	endChoice2Count = 0;
	endMineCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == choice2)
			startChoice2Count++;
		if (G.hand[player][i] == mine)
			startMineCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(mine, 0, choice2, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == choice2)
			endChoice2Count++;
		if (G.hand[player][i] == mine)
			endMineCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Copper hand count before: %d, Copper hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Silver hand count before: %d, Silver hand count after: %d\n", startChoice2Count, endChoice2Count);
	printf("Mine hand count before: %d, Mine hand count after: %d\n", startMineCount, endMineCount);

	if (G.handCount[player] != startG.handCount[player] - 1)
		printf("FAIL. Hand count incorrect.\n");
	else
		printf("PASS. Hand count correct.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount + 1)
		printf("FAIL. Played card count did not increase by 1.\n");
	else
		printf("PASS. Played card count increased by 1.\n");

	if (endChoice1Count != startChoice1Count - 1)
		printf("FAIL. Did not trash copper.\n");
	else
		printf("PASS. Trashed copper.\n");

	if (endChoice2Count != startChoice2Count + 1)
		printf("FAIL. Did not gain silver.\n");
	else
		printf("PASS. Gained silver to hand.\n");

	if (endMineCount != startMineCount - 1)
		printf("FAIL. Did not discard mine.\n");
	else
		printf("PASS. Discarded mine card.\n");

	//----------------------------------------------------------
	printf("\nTest 2: Trash silver to gain gold\n");
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (i = 0; i < initG.handCount[player]; i++)
	{
		G.hand[player][i] = initG.hand[player][i];
	}

	choice1 = silver;
	choice2 = gold;
	G.hand[player][0] = choice1;
	G.hand[player][1] = mine;

	startChoice1Count = 0;
	startChoice2Count = 0;
	startMineCount = 0;
	endChoice1Count = 0;
	endChoice2Count = 0;
	endMineCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == choice2)
			startChoice2Count++;
		if (G.hand[player][i] == mine)
			startMineCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(mine, 0, choice2, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == choice2)
			endChoice2Count++;
		if (G.hand[player][i] == mine)
			endMineCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Silver hand count before: %d, Silver hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Gold hand count before: %d, Gold hand count after: %d\n", startChoice2Count, endChoice2Count);
	printf("Mine hand count before: %d, Mine hand count after: %d\n", startMineCount, endMineCount);

	if (G.handCount[player] != startG.handCount[player] - 1)
		printf("FAIL. Hand count incorrect.\n");
	else
		printf("PASS. Hand count correct.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount + 1)
		printf("FAIL. Played card count did not change.\n");
	else
		printf("PASS. Played card count increased by 1.\n");

	if (endChoice1Count != startChoice1Count - 1)
		printf("FAIL. Did not trash silver.\n");
	else
		printf("PASS. Trashed silver.\n");

	if (endChoice2Count != startChoice2Count + 1)
		printf("FAIL. Did not gain gold.\n");
	else
		printf("PASS. Gained gold to hand.\n");

	if (endMineCount != startMineCount - 1)
		printf("FAIL. Did not discard mine.\n");
	else
		printf("PASS. Discarded mine card.\n");

	//----------------------------------------------------------
	printf("\nTest 3: Trash copper and try to gain gold\n");
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (i = 0; i < initG.handCount[player]; i++)
	{
		G.hand[player][i] = initG.hand[player][i];
	}

	choice1 = copper;
	choice2 = gold;
	G.hand[player][0] = choice1;
	G.hand[player][1] = mine;

	startChoice1Count = 0;
	startChoice2Count = 0;
	startMineCount = 0;
	endChoice1Count = 0;
	endChoice2Count = 0;
	endMineCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == choice2)
			startChoice2Count++;
		if (G.hand[player][i] == mine)
			startMineCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(mine, 0, choice2, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == choice2)
			endChoice2Count++;
		if (G.hand[player][i] == mine)
			endMineCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Copper hand count before: %d, Copper hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Gold hand count before: %d, Gold hand count after: %d\n", startChoice2Count, endChoice2Count);
	printf("Mine hand count before: %d, Mine hand count after: %d\n", startMineCount, endMineCount);

	if (G.handCount[player] != startG.handCount[player])
		printf("FAIL. Hand count changed.\n");
	else
		printf("PASS. Hand count did not change.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount)
		printf("FAIL. Played card count changed.\n");
	else
		printf("PASS. Played card count did not change.\n");

	if (endChoice1Count != startChoice1Count)
		printf("FAIL. Copper count changed.\n");
	else
		printf("PASS. Copper count did not change.\n");

	if (endChoice2Count != startChoice2Count)
		printf("FAIL. Gold count changed.\n");
	else
		printf("PASS. Gold count did not change.\n");

	if (endMineCount != startMineCount)
		printf("FAIL. Mine count changed.\n");
	else
		printf("PASS. Mine count did not change.\n");


	//----------------------------------------------------------
	printf("\nTest 4: Trash copper and try to gain village\n");
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (i = 0; i < initG.handCount[player]; i++)
	{
		G.hand[player][i] = initG.hand[player][i];
	}

	choice1 = copper;
	choice2 = village;
	G.hand[player][0] = choice1;
	G.hand[player][1] = mine;

	startChoice1Count = 0;
	startChoice2Count = 0;
	startMineCount = 0;
	endChoice1Count = 0;
	endChoice2Count = 0;
	endMineCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == choice2)
			startChoice2Count++;
		if (G.hand[player][i] == mine)
			startMineCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(mine, 0, choice2, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == choice2)
			endChoice2Count++;
		if (G.hand[player][i] == mine)
			endMineCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Copper hand count before: %d, Copper hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Village hand count before: %d, Village hand count after: %d\n", startChoice2Count, endChoice2Count);
	printf("Mine hand count before: %d, Mine hand count after: %d\n", startMineCount, endMineCount);

	if (G.handCount[player] != startG.handCount[player])
		printf("FAIL. Hand count changed.\n");
	else
		printf("PASS. Hand count did not change.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount)
		printf("FAIL. Played card count changed.\n");
	else
		printf("PASS. Played card count did not change.\n");

	if (endChoice1Count != startChoice1Count)
		printf("FAIL. Copper count changed.\n");
	else
		printf("PASS. Copper count did not change.\n");

	if (endChoice2Count != startChoice2Count)
		printf("FAIL. Village count changed.\n");
	else
		printf("PASS. Village count did not change.\n");

	if (endMineCount != startMineCount)
		printf("FAIL. Mine count changed.\n");
	else
		printf("PASS. Mine count did not change.\n");

	//----------------------------------------------------------
	printf("\nTest 5: Trash copper and try to gain estate\n");
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (i = 0; i < initG.handCount[player]; i++)
	{
		G.hand[player][i] = initG.hand[player][i];
	}

	choice1 = copper;
	choice2 = estate;
	G.hand[player][0] = choice1;
	G.hand[player][1] = mine;

	startChoice1Count = 0;
	startChoice2Count = 0;
	startMineCount = 0;
	endChoice1Count = 0;
	endChoice2Count = 0;
	endMineCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == choice2)
			startChoice2Count++;
		if (G.hand[player][i] == mine)
			startMineCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(mine, 0, choice2, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == choice2)
			endChoice2Count++;
		if (G.hand[player][i] == mine)
			endMineCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Copper hand count before: %d, Copper hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Estate hand count before: %d, Estate hand count after: %d\n", startChoice2Count, endChoice2Count);
	printf("Mine hand count before: %d, Mine hand count after: %d\n", startMineCount, endMineCount);

	if (G.handCount[player] != startG.handCount[player])
		printf("FAIL. Hand count changed.\n");
	else
		printf("PASS. Hand count did not change.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount)
		printf("FAIL. Played card count changed.\n");
	else
		printf("PASS. Played card count did not change.\n");

	if (endChoice1Count != startChoice1Count)
		printf("FAIL. Copper count changed.\n");
	else
		printf("PASS. Copper count did not change.\n");

	if (endChoice2Count != startChoice2Count)
		printf("FAIL. Estate count changed.\n");
	else
		printf("PASS. Estate count did not change.\n");

	if (endMineCount != startMineCount)
		printf("FAIL. Mine count changed.\n");
	else
		printf("PASS. Mine count did not change.\n");

	//----------------------------------------------------------
	printf("\nTest 6: Try to trash curse and try to gain silver.\n");
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (i = 0; i < initG.handCount[player]; i++)
	{
		G.hand[player][i] = initG.hand[player][i];
	}

	choice1 = curse;
	choice2 = silver;
	G.hand[player][0] = choice1;
	G.hand[player][1] = mine;

	startChoice1Count = 0;
	startChoice2Count = 0;
	startMineCount = 0;
	endChoice1Count = 0;
	endChoice2Count = 0;
	endMineCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == choice2)
			startChoice2Count++;
		if (G.hand[player][i] == mine)
			startMineCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(mine, 0, choice2, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == choice2)
			endChoice2Count++;
		if (G.hand[player][i] == mine)
			endMineCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Curse hand count before: %d, Curse hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Silver hand count before: %d, Silver hand count after: %d\n", startChoice2Count, endChoice2Count);
	printf("Mine hand count before: %d, Mine hand count after: %d\n", startMineCount, endMineCount);

	if (G.handCount[player] != startG.handCount[player])
		printf("FAIL. Hand count changed.\n");
	else
		printf("PASS. Hand count did not change.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount)
		printf("FAIL. Played card count changed.\n");
	else
		printf("PASS. Played card count did not change.\n");

	if (endChoice1Count != startChoice1Count)
		printf("FAIL. Curse count changed.\n");
	else
		printf("PASS. Curse count did not change.\n");

	if (endChoice2Count != startChoice2Count)
		printf("FAIL. Silver count changed.\n");
	else
		printf("PASS. Silver count did not change.\n");

	if (endMineCount != startMineCount)
		printf("FAIL. Mine count changed.\n");
	else
		printf("PASS. Mine count did not change.\n");

	//----------------------------------------------------------
	printf("\nTest 7: Try to trash village and try to gain gold.\n");
	//reset starting hand
	G.handCount[player] = initG.handCount[player];
	for (i = 0; i < initG.handCount[player]; i++)
	{
		G.hand[player][i] = initG.hand[player][i];
	}

	choice1 = village;
	choice2 = gold;
	G.hand[player][0] = choice1;
	G.hand[player][1] = mine;

	startChoice1Count = 0;
	startChoice2Count = 0;
	startMineCount = 0;
	endChoice1Count = 0;
	endChoice2Count = 0;
	endMineCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			startChoice1Count++;
		if (G.hand[player][i] == choice2)
			startChoice2Count++;
		if (G.hand[player][i] == mine)
			startMineCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(mine, 0, choice2, 0, &G, 1, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == choice1)
			endChoice1Count++;
		if (G.hand[player][i] == choice2)
			endChoice2Count++;
		if (G.hand[player][i] == mine)
			endMineCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[player], G.discardCount[player]);
	printf("Played count before: %d, Played count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Village hand count before: %d, Village hand count after: %d\n", startChoice1Count, endChoice1Count);
	printf("Gold hand count before: %d, Gold hand count after: %d\n", startChoice2Count, endChoice2Count);
	printf("Mine hand count before: %d, Mine hand count after: %d\n", startMineCount, endMineCount);

	if (G.handCount[player] != startG.handCount[player])
		printf("FAIL. Hand count changed.\n");
	else
		printf("PASS. Hand count did not change.\n");

	if (G.deckCount[player] != startG.deckCount[player])
		printf("FAIL. Deck count changed.\n");
	else
		printf("PASS. Deck count did not change.\n");

	if (G.discardCount[player] != startG.discardCount[player])
		printf("FAIL. Discard count changed.\n");
	else
		printf("PASS. Discard count did not change.\n");

	if (G.playedCardCount != startG.playedCardCount)
		printf("FAIL. Played card count changed.\n");
	else
		printf("PASS. Played card count did not change.\n");

	if (endChoice1Count != startChoice1Count)
		printf("FAIL. Village count changed.\n");
	else
		printf("PASS. Village count did not change.\n");

	if (endChoice2Count != startChoice2Count)
		printf("FAIL. Gold count changed.\n");
	else
		printf("PASS. Gold count did not change.\n");

	if (endMineCount != startMineCount)
		printf("FAIL. Mine count changed.\n");
	else
		printf("PASS. Mine count did not change.\n");

	printf("\nMine Testing Complete.\n\n");

	return 0;
}
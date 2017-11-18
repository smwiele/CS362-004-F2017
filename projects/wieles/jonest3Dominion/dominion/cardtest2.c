/*
* Unit tests for smithyCardEffect()
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
	struct gameState G, startG;
	int k[10] = {adventurer, embargo, village, minion, mine, 
				 cutpurse, sea_hag, tribute, smithy, council_room};
	int i;
	int startSmithyCount, endSmithyCount;

	printf("Testing Smithy Card\n");

	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = player;
	G.hand[player][0] = smithy;

	startSmithyCount = 0;
	endSmithyCount = 0;

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == smithy)
			startSmithyCount++;
	}

	memcpy(&startG, &G, sizeof(struct gameState));

	cardEffect(smithy, 0, 0, 0, &G, 0, 0);

	for (i = 0; i < G.handCount[player]; i++)
	{
		if (G.hand[player][i] == smithy)
			endSmithyCount++;
	}

	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[player], G.handCount[player]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[player], G.deckCount[player]);
	printf("Played card count before: %d, Played card count after: %d\n", startG.playedCardCount, G.playedCardCount);
	printf("Smithy hand count before: %d, Smithy hand count after: %d\n", startSmithyCount, endSmithyCount);

	//check hand increased by 2 cards (3 cards added and Smithy card discarded)
	if (G.handCount != startG.handCount + 2)
		printf("FAIL. Hand count did not increase by 2.\n");
	else
		printf("PASS. Hand count increased by 2.\n");

	//check deck decreased by 3 cards
	if (G.deckCount[player] != startG.deckCount[player] - 3)
		printf("FAIL. Cards not correctly removed from players deck.\n");
	else
		printf("PASS. Cards removed from players deck.\n");

	if (G.playedCardCount != startG.playedCardCount + 1)
		printf("FAIL. Played card count did not increase by 1.\n");
	else
		printf("PASS. Played card count increased by 1.\n");

	if (endSmithyCount != startSmithyCount - 1)
		printf("FAIL. Smithy card count did not decrease by 1.\n");
	else
		printf("PASS. Smithy card count decreased by 1.\n");

	//check other player's card counts did not change
	printf("\nCheck Player 2's card counts\n");
	printf("Hand count before: %d, Hand count after: %d\n", startG.handCount[1], G.handCount[1]);
	printf("Deck count before: %d, Deck count after: %d\n", startG.deckCount[1], G.deckCount[1]);
	printf("Discard count before: %d, Discard count after: %d\n", startG.discardCount[1], G.discardCount[1]);
	if (G.handCount[1] != startG.handCount[1])
		printf("FAIL. Player 2's hand count changed.\n");
	else if (G.deckCount[1] != startG.deckCount[1])
		printf("FAIL. Player 2's deck count changed.\n");
	else if (G.discardCount[1] != startG.discardCount[1])
		printf("FAIL. Player 2's discard count changed.\n");
	else
		printf("PASS. Player 2's card counts did not change.\n");

	//check supply card piles did not change
	printf("\nCheck supply card piles did not change\n");
	for (i = curse; i <= treasure_map; i++)
	{
		printf("Card %d - supply count before: %d, supply count after: %d\n", i, startG.supplyCount[i], G.supplyCount[i]);
		if (G.supplyCount[i] != startG.supplyCount[i])
			printf("FAIL. Card %d supply count changed.\n", i);
		else
			printf("PASS. Card %d supply count did not change.\n", i);
	}

	printf("\nSmithy Testing complete\n\n");

	return 0;
}
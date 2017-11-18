/*
* Unit tests for fullDeckCount()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int main()
{
	int seed = 1000;
	int numPlayers = 2;
	int player = 0;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, 
				 cutpurse, sea_hag, tribute, smithy, council_room};

	int i;
	int card;
	int cardCount;

	printf("Testing fullDeckCount() function\n");

	//initialize game
	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = player;

	//--------------------------------------------------------------------
	printf("\nTest 1: Card in game set that is in deck, hand, and discard\n");

	//use coppers and estates
	//initialize player deck
	G.handCount[player] = 5;
	for (i = 0; i < 4; i++) 
	{
		G.hand[player][i] = copper;
	}
	G.hand[player][4] = estate;

	G.deckCount[player] = 5;
	for (i = 0; i < 2; i++)
	{
		G.deck[player][i] = copper;
	}
	for (i = 2; i < 5; i++)
	{
		G.deck[player][i] = estate;
	}

	G.discardCount[player] = 5;
	for (i = 0; i < 3; i++) 
	{
		G.discard[player][i] = copper;
	}
	for (i = 3; i < 5; i++)
	{
		G.discard[player][i] = estate;
	}

	card = copper;
	cardCount = fullDeckCount(player, card, &G);
	printf("Copper - Expected card count: 9, Actual card count: %d\n", cardCount);
	if (cardCount != 9)
		printf("FAIL. Card count not correct.\n");
	else
		printf("PASS. Card count correct.\n");

	card = estate;
	cardCount = fullDeckCount(player, card, &G);
	printf("Estate - Expected card count: 6, Actual card count: %d\n", cardCount);
	if (cardCount != 6)
		printf("FAIL. Card count not correct.\n");
	else
		printf("PASS. Card count correct.\n");

	//--------------------------------------------------------------------------------
	printf("\nTest 2: Card in game set that is not in deck, hand, or discard\n");

	card = mine;
	cardCount = fullDeckCount(player, card, &G);
	printf("Expected card count: 0, Actual card count: %d\n", cardCount);

	if (cardCount != 0)
		printf("FAIL. Card count not correct.\n");
	else
		printf("PASS. Card count correct.\n");

	//---------------------------------------------
	printf("\nTest 3: Card not in game set\n");

	card = salvager;
	cardCount = fullDeckCount(player, card, &G);
	printf("Expected card count: 0, Actual card count: %d\n", cardCount);

	if (cardCount != 0)
		printf("FAIL. Card count not correct.\n");
	else
		printf("PASS. Card count correct.\n");

	printf("\nfullDeckCount() Testing Complete.\n\n");

	return 0;
}
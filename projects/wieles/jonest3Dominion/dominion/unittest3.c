/*
* Unit tests for buyCard()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int main() {
	int seed = 1000;
	int numPlayers = 2;
	int player = 0;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, 
				 cutpurse, sea_hag, tribute, smithy, council_room};

	int card;
	int cardBefore, cardAfter;
	int discardBefore, discardAfter;
	int supplyBefore, supplyAfter;
	int coinsBefore, coinsAfter;
	int buysBefore, buysAfter;

	//initialize game
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing buyCard() function\n");

	printf("\nTest case 1: Buys = 1, Supply = 1, Coins = Cost\n");
	printf("Card = Village, Cost = 3\n");

	card = village;
	G.whoseTurn = player;
	G.numBuys = 1;
	G.supplyCount[card] = 1;
	G.coins = 3;

	cardBefore = fullDeckCount(player, card, &G);
	discardBefore = G.discardCount[player];
	supplyBefore = G.supplyCount[card];
	coinsBefore = G.coins;
	buysBefore = G.numBuys;

	if (buyCard(card, &G) == 0)
	{
		cardAfter = fullDeckCount(player, card, &G);
		discardAfter = G.discardCount[player];
		supplyAfter = G.supplyCount[card];
		coinsAfter = G.coins;
		buysAfter = G.numBuys;

		printf("Card type count before: %d,  Card type count after: %d\n", cardBefore, cardAfter);
		printf("Discard count before: %d,  	 Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,   	 Supply count after: %d\n", supplyBefore, supplyAfter);
		printf("Coin count before: %d,     	 Coin count after: %d\n", coinsBefore, coinsAfter);
		printf("Buy count before: %d,      	 Buy count after: %d\n", buysBefore, buysAfter);

		if (cardAfter != cardBefore + 1)
			printf("FAIL. Did not increase card type by 1.\n");
		else
			printf("PASS. Card type increased by 1.\n");

		if (discardAfter != discardBefore + 1)
			printf("FAIL. Did not add card to discard.\n");
		else
			printf("PASS. Added card to discard.\n");

		if (supplyAfter != supplyBefore - 1)
			printf("FAIL. Did not decrease supply.\n");
		else
			printf("PASS. Supply decreased by 1.\n");

		if (coinsAfter != coinsBefore - getCost(card))
			printf("FAIL. Did not subtract correct cost from coins.\n");
		else
			printf("PASS. Cost correctly subtracted from coins.\n");

		if (buysAfter != buysBefore - 1)
			printf("FAIL. Buys did not decrease by 1.\n");
		else
			printf("PASS. Buys decreased by 1.\n");
	}
	else
		printf("FAIL. Did not buy card.\n");

	//-----------------------------------------------------------------
	printf("\nTest case 2: Buys > 1, Supply > 1, Coins > Cost\n");
	printf("Card = Village, Cost = 3\n");

	card = village;
	G.whoseTurn = player;
	G.numBuys = 3;
	G.supplyCount[card] = 10;
	G.coins = 5;

	cardBefore = fullDeckCount(player, card, &G);
	discardBefore = G.discardCount[player];
	supplyBefore = G.supplyCount[card];
	coinsBefore = G.coins;
	buysBefore = G.numBuys;

	if (buyCard(card, &G) == 0)
	{
		cardAfter = fullDeckCount(player, card, &G);
		discardAfter = G.discardCount[player];
		supplyAfter = G.supplyCount[card];
		coinsAfter = G.coins;
		buysAfter = G.numBuys;

		printf("Card type count before: %d,  Card type count after: %d\n", cardBefore, cardAfter);
		printf("Discard count before: %d,  	 Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,   	 Supply count after: %d\n", supplyBefore, supplyAfter);
		printf("Coin count before: %d,     	 Coin count after: %d\n", coinsBefore, coinsAfter);
		printf("Buy count before: %d,      	 Buy count after: %d\n", buysBefore, buysAfter);

		if (cardAfter != cardBefore + 1)
			printf("FAIL. Did not increase card type by 1.\n");
		else
			printf("PASS. Card type increased by 1.\n");

		if (discardAfter != discardBefore + 1)
			printf("FAIL. Did not add card to discard.\n");
		else
			printf("PASS. Added card to discard.\n");

		if (supplyAfter != supplyBefore - 1)
			printf("FAIL. Did not decrease supply.\n");
		else
			printf("PASS. Supply decreased by 1.\n");

		if (coinsAfter != coinsBefore - getCost(card))
			printf("FAIL. Did not subtract correct cost from coins.\n");
		else
			printf("PASS. Cost correctly subtracted from coins.\n");

		if (buysAfter != buysBefore - 1)
			printf("FAIL. Buys did not decrease by 1.\n");
		else
			printf("PASS. Buys decreased by 1.\n");
	}
	else
		printf("FAIL. Did not buy card.\n");

	//-----------------------------------------------------------------
	printf("\nTest Case 3: Buys < 1\n");
	printf("Card = Village, Cost = 3\n");

	card = village;
	G.whoseTurn = player;
	G.numBuys = 0;
	G.supplyCount[card] = 10;
	G.coins = 5;

	cardBefore = fullDeckCount(player, card, &G);
	discardBefore = G.discardCount[player];
	supplyBefore = G.supplyCount[card];
	coinsBefore = G.coins;
	buysBefore = G.numBuys;

	if (buyCard(card, &G) == -1)
	{
		cardAfter = fullDeckCount(player, card, &G);
		discardAfter = G.discardCount[player];
		supplyAfter = G.supplyCount[card];
		coinsAfter = G.coins;
		buysAfter = G.numBuys;

		printf("Card type count before: %d,  Card type count after: %d\n", cardBefore, cardAfter);
		printf("Discard count before: %d,  	 Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,   	 Supply count after: %d\n", supplyBefore, supplyAfter);
		printf("Coin count before: %d,     	 Coin count after: %d\n", coinsBefore, coinsAfter);
		printf("Buy count before: %d,      	 Buy count after: %d\n", buysBefore, buysAfter);

		if (cardAfter != cardBefore)
			printf("FAIL. Card type count changed.\n");
		else
			printf("PASS. Card type cound did not change.\n");

		if (discardAfter != discardBefore)
			printf("FAIL. Discard count changed.\n");
		else
			printf("PASS. Discard count did not change.\n");

		if (supplyAfter != supplyBefore)
			printf("FAIL. Supply count changed.\n");
		else
			printf("PASS. Supply count did not change.\n");

		if (coinsAfter != coinsBefore)
			printf("FAIL. Coin count changed.\n");
		else
			printf("PASS. Coin count did not change.\n");

		if (buysAfter != buysBefore)
			printf("FAIL. Buy count changed.\n");
		else
			printf("PASS. Buy count did not change.\n");
	}
	else
		printf("FAIL. Did not return -1.\n");

	//-----------------------------------------------------------------
	printf("\nTest Case 4: Supply < 1\n");
	printf("Card = Village, Cost = 3\n");

	card = village;
	G.whoseTurn = player;
	G.numBuys = 1;
	G.supplyCount[card] = 0;
	G.coins = 5;

	cardBefore = fullDeckCount(player, card, &G);
	discardBefore = G.discardCount[player];
	supplyBefore = G.supplyCount[card];
	coinsBefore = G.coins;
	buysBefore = G.numBuys;

	if (buyCard(card, &G) == -1)
	{
		cardAfter = fullDeckCount(player, card, &G);
		discardAfter = G.discardCount[player];
		supplyAfter = G.supplyCount[card];
		coinsAfter = G.coins;
		buysAfter = G.numBuys;

		printf("Card type count before: %d,  Card type count after: %d\n", cardBefore, cardAfter);
		printf("Discard count before: %d,  	 Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,   	 Supply count after: %d\n", supplyBefore, supplyAfter);
		printf("Coin count before: %d,     	 Coin count after: %d\n", coinsBefore, coinsAfter);
		printf("Buy count before: %d,      	 Buy count after: %d\n", buysBefore, buysAfter);

		if (cardAfter != cardBefore)
			printf("FAIL. Card type count changed.\n");
		else
			printf("PASS. Card type cound did not change.\n");

		if (discardAfter != discardBefore)
			printf("FAIL. Discard count changed.\n");
		else
			printf("PASS. Discard count did not change.\n");

		if (supplyAfter != supplyBefore)
			printf("FAIL. Supply count changed.\n");
		else
			printf("PASS. Supply count did not change.\n");

		if (coinsAfter != coinsBefore)
			printf("FAIL. Coin count changed.\n");
		else
			printf("PASS. Coin count did not change.\n");

		if (buysAfter != buysBefore)
			printf("FAIL. Buy count changed.\n");
		else
			printf("PASS. Buy count did not change.\n");
	}
	else
		printf("FAIL. Did not return -1.\n");

	//-----------------------------------------------------------------
	printf("\nTest Case 5: Coins < Cost\n");
	printf("Card = Village, Cost = 3\n");

	card = village;
	G.whoseTurn = player;
	G.numBuys = 1;
	G.supplyCount[card] = 10;
	G.coins = 2;

	cardBefore = fullDeckCount(player, card, &G);
	discardBefore = G.discardCount[player];
	supplyBefore = G.supplyCount[card];
	coinsBefore = G.coins;
	buysBefore = G.numBuys;

	if (buyCard(card, &G) == -1)
	{
		cardAfter = fullDeckCount(player, card, &G);
		discardAfter = G.discardCount[player];
		supplyAfter = G.supplyCount[card];
		coinsAfter = G.coins;
		buysAfter = G.numBuys;

		printf("Card type count before: %d,  Card type count after: %d\n", cardBefore, cardAfter);
		printf("Discard count before: %d,  	 Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,   	 Supply count after: %d\n", supplyBefore, supplyAfter);
		printf("Coin count before: %d,     	 Coin count after: %d\n", coinsBefore, coinsAfter);
		printf("Buy count before: %d,      	 Buy count after: %d\n", buysBefore, buysAfter);

		if (cardAfter != cardBefore)
			printf("FAIL. Card type count changed.\n");
		else
			printf("PASS. Card type cound did not change.\n");

		if (discardAfter != discardBefore)
			printf("FAIL. Discard count changed.\n");
		else
			printf("PASS. Discard count did not change.\n");

		if (supplyAfter != supplyBefore)
			printf("FAIL. Supply count changed.\n");
		else
			printf("PASS. Supply count did not change.\n");

		if (coinsAfter != coinsBefore)
			printf("FAIL. Coin count changed.\n");
		else
			printf("PASS. Coin count did not change.\n");

		if (buysAfter != buysBefore)
			printf("FAIL. Buy count changed.\n");
		else
			printf("PASS. Buy count did not change.\n");
	}
	else
		printf("FAIL. Did not return -1.\n");

	printf("\nbuyCard() Testing Complete.\n\n");

	return 0;
}
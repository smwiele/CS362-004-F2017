/*
* Unit tests for gainCard()
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
	int supplyBefore, supplyAfter;
	int cardBefore, cardAfter;
	int deckBefore, deckAfter;
	int handBefore, handAfter;
	int discardBefore, discardAfter;
	
	//initialize game
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing gainCard() function\n");

	// ------------------------------------------------------------------------------
	printf("\nTest 1: Gain Adventurer card and check it is added to deck.\n");
	
	card = adventurer;
	cardBefore = fullDeckCount(player, card, &G);
	deckBefore = G.deckCount[player];
	handBefore = G.handCount[player];
	discardBefore = G.discardCount[player];
	supplyBefore = supplyCount(card, &G);

	if (gainCard(card, &G, 1, player) == 0)
	{
		cardAfter = fullDeckCount(player, card, &G);
		deckAfter = G.deckCount[player];
		handAfter = G.handCount[player];
		discardAfter = G.discardCount[player];
		supplyAfter = supplyCount(card, &G);
		
		printf("Adventurer count before: %d,  Adventurer count after: %d\n", cardBefore, cardAfter);
		printf("Deck count before: %d,        Deck count after: %d\n", deckBefore, deckAfter);
		printf("Hand count before: %d,        Hand count after: %d\n", handBefore, handAfter);
		printf("Discard count before: %d,     Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,      Supply count after: %d\n", supplyBefore, supplyAfter);
		
		if (cardAfter != cardBefore + 1)
			printf("FAIL. Did not add adventurer card.\n");
		else
			printf("PASS. Added adventurer card to hand.\n");
		
		if (deckAfter != deckBefore + 1)
			printf("FAIL. Card not added to deck.\n");
		else
			printf("PASS. Card added to deck.\n");
		
		if (handAfter != handBefore)
			printf("FAIL. Hand count changed.\n");
		else
			printf("PASS. Hand count did not change.\n");

		if (discardAfter != discardBefore)
			printf("FAIL. Discard count changed.\n");
		else
			printf("PASS. Discard count did not change.\n");

		if (supplyAfter != supplyBefore - 1)
			printf("FAIL. Supply pile did not decrease by 1.\n");
		else
			printf("PASS. Supply pile decreased by 1.\n");
	}
	else
		printf("FAIL. Did not gain card.\n");

	//-----------------------------------------------------------------------
	printf("\nTest 2: Gain Adventurer card and check it is added to hand.\n");
	
	cardBefore = fullDeckCount(player, card, &G);
	deckBefore = G.deckCount[player];
	handBefore = G.handCount[player];
	discardBefore = G.discardCount[player];
	supplyBefore = supplyCount(card, &G);

	if (gainCard(card, &G, 2, player) == 0)
	{
		cardAfter = fullDeckCount(player, card, &G);
		deckAfter = G.deckCount[player];
		handAfter = G.handCount[player];
		discardAfter = G.discardCount[player];
		supplyAfter = supplyCount(card, &G);
		
		printf("Adventurer count before: %d,  Adventurer count after: %d\n", cardBefore, cardAfter);
		printf("Deck count before: %d,        Deck count after: %d\n", deckBefore, deckAfter);
		printf("Hand count before: %d,        Hand count after: %d\n", handBefore, handAfter);
		printf("Discard count before: %d,     Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,      Supply count after: %d\n", supplyBefore, supplyAfter);
		
		if (cardAfter != cardBefore + 1)
			printf("FAIL. Did not add adventurer card.\n");
		else
			printf("PASS. Added adventurer card to hand.\n");
		
		if (deckAfter != deckBefore)
			printf("FAIL. Deck count changed.\n");
		else
			printf("PASS. Deck count did not change.\n");
		
		if (handAfter != handBefore + 1)
			printf("FAIL. Hand count did not increase by 1.\n");
		else
			printf("PASS. Hand count increased by 1.\n");

		if (discardAfter != discardBefore)
			printf("FAIL. Discard count changed.\n");
		else
			printf("PASS. Discard count did not change.\n");

		if (supplyAfter != supplyBefore - 1)
			printf("FAIL. Supply pile did not decrease by 1.\n");
		else
			printf("PASS. Supply pile decreased by 1.\n");
	}
	else
		printf("FAIL. Did not gain card.\n");

	//----------------------------------------------------------------------
	printf("\nTest 3: Gain Adventurer card and check it is added to discard.\n");
	
	cardBefore = fullDeckCount(player, card, &G);
	deckBefore = G.deckCount[player];
	handBefore = G.handCount[player];
	discardBefore = G.discardCount[player];
	supplyBefore = supplyCount(card, &G);

	if (gainCard(card, &G, 0, player) == 0)
	{
		cardAfter = fullDeckCount(player, card, &G);
		deckAfter = G.deckCount[player];
		handAfter = G.handCount[player];
		discardAfter = G.discardCount[player];
		supplyAfter = supplyCount(card, &G);
		
		printf("Adventurer count before: %d,  Adventurer count after: %d\n", cardBefore, cardAfter);
		printf("Deck count before: %d,        Deck count after: %d\n", deckBefore, deckAfter);
		printf("Hand count before: %d,        Hand count after: %d\n", handBefore, handAfter);
		printf("Discard count before: %d,     Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,      Supply count after: %d\n", supplyBefore, supplyAfter);

		if (cardAfter != cardBefore + 1)
			printf("FAIL. Did not add adventurer card.\n");
		else
			printf("PASS. Added adventurer card to hand.\n");
		
		if (deckAfter != deckBefore)
			printf("FAIL. Deck count changed.\n");
		else
			printf("PASS. Deck count did not change.\n");
		
		if (handAfter != handBefore)
			printf("FAIL. Hand count changed.\n");
		else
			printf("PASS. Hand count did not change.\n");

		if (discardAfter != discardBefore + 1)
			printf("FAIL. Discard count did not increase by 1.\n");
		else
			printf("PASS. Discard count increased by 1.\n");

		if (supplyAfter != supplyBefore - 1)
			printf("FAIL. Supply pile did not decrease by 1.\n");
		else
			printf("PASS. Supply pile decreased by 1.\n");
	}
	else
		printf("FAIL. Did not gain card.\n");

	//--------------------------------------------------------------------
	printf("\nTest 4: Try to gain Tribute card when supply pile is empty.\n");
	card = tribute;
	G.supplyCount[card] = 0;

	cardBefore = fullDeckCount(player, card, &G);
	deckBefore = G.deckCount[player];
	handBefore = G.handCount[player];
	discardBefore = G.discardCount[player];
	supplyBefore = supplyCount(card, &G);

	if (gainCard(card, &G, 1, player) == -1) {
		cardAfter = fullDeckCount(player, card, &G);
		deckAfter = G.deckCount[player];
		handAfter = G.handCount[player];
		discardAfter = G.discardCount[player];
		supplyAfter = supplyCount(card, &G);

		printf("Tribute count before: %d,  Tribute count after: %d\n", cardBefore, cardAfter);
		printf("Deck count before: %d,     Deck count after: %d\n", deckBefore, deckAfter);
		printf("Hand count before: %d,     Hand count after: %d\n", handBefore, handAfter);
		printf("Discard count before: %d,  Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,   Supply count after: %d\n", supplyBefore, supplyAfter);
		
		if (cardAfter != cardBefore)
			printf("FAIL. Added Tribute card.\n");
		else
			printf("PASS. Did not add Tribute card.\n");

		if (deckAfter != deckBefore)
			printf("FAIL. Deck count changed.\n");
		else
			printf("PASS. Deck count did not change.\n");

		if (handAfter != handBefore)
			printf("FAIL. Hand count changed.\n");
		else
			printf("PASS. Hand count did not change.\n");

		if (discardAfter != discardBefore)
			printf("FAIL. Discard count changed.\n");
		else
			printf("PASS. Discard count did not change.\n");

		if (supplyAfter != supplyBefore)
			printf("FAIL. Supply pile changed.\n");
		else
			printf("PASS. Supply pile did not change.\n");
	}
	else
		printf("FAIL. Did not return -1.\n");

	//-------------------------------------------------------------------
	printf("\nTest 5: Try to gain Feast card that is not in game.\n");
	
	card = feast;
	cardBefore = fullDeckCount(player, card, &G);
	deckBefore = G.deckCount[player];
	handBefore = G.handCount[player];
	discardBefore = G.discardCount[player];
	supplyBefore = supplyCount(card, &G);

	if (gainCard(card, &G, 1, player) == -1) {
		cardAfter = fullDeckCount(player, card, &G);
		deckAfter = G.deckCount[player];
		handAfter = G.handCount[player];
		discardAfter = G.discardCount[player];
		supplyAfter = supplyCount(card, &G);

		printf("Feast count before: %d,    Feast count after: %d\n", cardBefore, cardAfter);
		printf("Deck count before: %d,     Deck count after: %d\n", deckBefore, deckAfter);
		printf("Hand count before: %d,     Hand count after: %d\n", handBefore, handAfter);
		printf("Discard count before: %d,  Discard count after: %d\n", discardBefore, discardAfter);
		printf("Supply count before: %d,   Supply count after: %d\n", supplyBefore, supplyAfter);
		
		if (cardAfter != cardBefore)
			printf("FAIL. Added Tribute card.\n");
		else
			printf("PASS. Did not add Tribute card.\n");

		if (deckAfter != deckBefore)
			printf("FAIL. Deck count changed.\n");
		else
			printf("PASS. Deck count did not change.\n");

		if (handAfter != handBefore)
			printf("FAIL. Hand count changed.\n");
		else
			printf("PASS. Hand count did not change.\n");

		if (discardAfter != discardBefore)
			printf("FAIL. Discard count changed.\n");
		else
			printf("PASS. Discard count did not change.\n");

		if (supplyAfter != supplyBefore)
			printf("FAIL. Supply pile changed.\n");
		else
			printf("PASS. Supply pile did not change.\n");
	}
	else
		printf("FAIL. Did not return -1.\n");

	printf("\ngainCard() Testing Complete\n\n");

	return 0;
}



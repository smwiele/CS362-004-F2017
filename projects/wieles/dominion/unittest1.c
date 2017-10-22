/******************************************************************************
* Unit test for getCost()
* *****************************************************************************
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

#define NUMCARDS 27

int main() {
	char *cardName;
	int cost;
	int i;
	int cardCosts[NUMCARDS] = { 0, 2, 5, 8, 0, 3, 6, 6, 5,
						    	4, 4, 5, 4, 4, 3, 4, 3, 5,
						    	3, 5, 3, 4, 2, 5, 4, 4, 4 };
	

	printf("Testing getCost() function\n");

	for (i = curse; i <= treasure_map; i++) {
		cardNumToName(i, cardName); //get card name

		cost = getCost(i); //get card cost

		printf("Card: %s,  Cost: %d,  Expected Cost: %d\n", cardName, cost, cardCosts[i]);
		//check that cost returned equals expected cost
		if (cost == cardCosts[i])
			printf("PASS. Returned correct cost.\n");
		else
			printf("FAIL. Returned incorrect cost.\n");
	}

	//check card not in game
	printf("\nTesting card value not in game\n");
	cost = getCost(30);
	if (cost == -1)
		printf("PASS. Returned -1.\n");
	else
		printf("FAIL. Did not return -1.\n");

	printf("\ngetCost() Testing complete\n\n");

	return 0;
}
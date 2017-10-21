/* jonest3
 * Unit Test 4*/

// getCost()
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "getCard.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){

   int cardArray[27] = {curse, estate, duchy, province, copper, silver, gold, 
			adventurer, council_room, feast, gardens, mine, remodel, 
			smithy, village, baron, great_hall, minion, steward, tribute, 
			ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
   int i;
   int cost;

   for(i = 0; i < 27; i++){
	cost = getCost(cardArray[i]);
	if(cardArray[i] == curse  ||  cardArray[i] == copper){
		if(cost != 0)
			printf("--TEST FAILED @ %s--\n", getCardName(cardArray[i]));
		else
			printf("--TEST PASSED @ %s--\n", getCardName(cardArray[i]));
	}
	else if(cardArray[i] == estate  ||  cardArray[i] == embargo){
		if(cost != 2)
			printf("--TEST FAILED @ %s--\n", getCardName(cardArray[i]));
                else
                        printf("--TEST PASSED @ %s--\n", getCardName(cardArray[i]));
	}
	else if(cardArray[i] == silver  ||  cardArray[i] == village  ||  cardArray[i] == great_hall  ||  cardArray[i] == steward  ||  cardArray[i] == ambassador){
		if(cost != 3)
			printf("--TEST FAILED @ %s--\n", getCardName(cardArray[i]));
                else
                        printf("--TEST PASSED @ %s--\n", getCardName(cardArray[i]));
	}
	else if(cardArray[i] == feast  ||  cardArray[i] == gardens  ||  cardArray[i] == remodel  || cardArray[i] == smithy  ||  cardArray[i] == baron  || cardArray[i] == cutpurse  || cardArray[i] == salvager  || cardArray[i] == sea_hag  ||  cardArray[i] == treasure_map){
		if(cost != 4)
			printf("--TEST FAILED @ %s--\n", getCardName(cardArray[i]));
                else
                        printf("--TEST PASSED @ %s--\n", getCardName(cardArray[i]));
	}
	else if(cardArray[i] == duchy  ||  cardArray[i] == council_room  ||  cardArray[i] == mine || cardArray[i] == minion  || cardArray[i] == tribute  ||  cardArray[i] == outpost){
		if(cost != 5)
			printf("--TEST FAILED @ %s--\n", getCardName(cardArray[i]));
                else
                        printf("--TEST PASSED @ %s--\n", getCardName(cardArray[i]));
	}
	else if(cardArray[i] == gold  || cardArray[i] == adventurer){
		if(cost != 6)
			printf("--TEST FAILED @ %s--\n", getCardName(cardArray[i]));
                else
                        printf("--TEST PASSED @ %s--\n", getCardName(cardArray[i]));
	}	
	else if(cardArray[i] == province){
		if(cost != 8)
			printf("--TEST FAILED @ %s--\n", getCardName(cardArray[i]));
                else
                        printf("--TEST PASSED @ %s--\n", getCardName(cardArray[i]));
	}
	else
		printf("CARD NOT IN DECK");
   }

   return 0;
}

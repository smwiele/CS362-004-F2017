/* jonest3
 * Unit Test 2*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "getCard.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(){
   printf("----------TESTING ISGAMEOVER----------\n\n");

   // Set up game
   int seed = 1000;
   int numPlayers = MAX_PLAYERS;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;

//   assert(initializeGame(numPlayers, k, seed, &G));
   initializeGame(numPlayers, k, seed, &G);


   int testNum = 3;
   int i;

   for(i = 0; i < testNum; i++){

   	int isOver = 0;

   	// check to see if game is over after setup
   	if(i == 0){
		printf("--TESTING GAME OVER AFTER START--\n");
		isOver = isGameOver(&G);

		if(!isOver) printf("TEST PASSED @ After Game Initialized\n");
		else printf("TEST FAILED @ After Game Initialized\n");
   	}
   	// check to see that game ends when province stack is empty
   	else if(i == 1){
		printf("--TESTING PROVINCE EMPTY--\n");
		G.supplyCount[province] = 0;
		isOver = isGameOver(&G);
	
		if(isOver) printf("TEST PASSED @ Province Stack == 0\n");
		else printf("TEST FAILED @ Province Stack == 0\n");

		G.supplyCount[province] = 8;
   	}
	// check to see if game is over when 3 supply piles are 0
   	else if(i == 2){
		// For all cards
		int cards[25] = {curse, estate, duchy, copper, 
				silver, gold, adventurer, council_room, feast, 
				gardens, mine, remodel, smithy, village, 
				baron, great_hall, minion, steward, tribute, 
				ambassador, cutpurse, embargo, outpost, salvager, 
				sea_hag};
		int card1, card2, card3, m;
		
		for(m = 0; m < 23; m++){

			int j;
			for(j = 0; j < 25; j++)
				G.supplyCount[cards[j]] = 8;

			assert(!isGameOver(&G));

			card1 = cards[m];
			card2 = cards[m+1];
			card3 = cards[m+2];

			printf("\n**Testing Cards: %s, %s, & %s**\n", getCardName(card1), getCardName(card2), getCardName(card3));

			// check to see if game is over when 3 supply piles are 1
			printf("\n--Testing Supplies == 1--\n");
			for(j = 0; j < 3; j++){
				if(j == 0)
					G.supplyCount[card1] = 1;
				else if(j == 1)
					G.supplyCount[card2] = 1;
				else
					G.supplyCount[card3] = 1;
	
				if(isGameOver(&G)){ printf("TEST FAILED @ Game over when %d supply == 1\n", j+1); break;}
				else printf("TEST PASSED @ Cards with supply == 1: %d\n", j+1);

			}
			// check to see if game is over when 3 supply piles are 0
			printf("\n--Testing Supplies == 0--\n");
			for(j = 0; j < 3; j++){
				if(j == 0)
				{
					G.supplyCount[card1] = 0; printf("%s's supply count: %d\n", getCardName(card1), G.supplyCount[card1]);
				}
				else if(j == 1)
				{
					G.supplyCount[card2] = 0; printf("%s's supply count: %d\n", getCardName(card2), G.supplyCount[card2]);
				}
				else
				{
					G.supplyCount[card3] = 0; printf("%s's supply count: %d\n", getCardName(card3), G.supplyCount[card3]);
				}

				if(isGameOver(&G)  &&  j == 2) printf("TEST PASSED @ Game over when 3 supply == 0\n");
				else if(isGameOver(&G)  && j != 2){ printf("TEST FAILED @ Game over when %d supply == 0\n", j+1); break;}
				else if(!isGameOver(&G)  &&  j == 2){ printf("TEST FAILED @ Game not over when 3 supply == 0\n"); break;}
			}
		}
		for(i = 0; i < 24; i++){
			G.supplyCount[cards[i]] = 10;
		}
		G.supplyCount[cards[24]] = 0;
		G.supplyCount[cards[19]] = 0;
		G.supplyCount[cards[4]] = 0;
		if(isGameOver(&G)) printf("TEST PASSED SEA_HAG\n");
		else printf("TEST FAILED SEA_HAG\n");
	}
   }
   return 0;
}

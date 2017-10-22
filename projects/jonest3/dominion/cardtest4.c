/*jonest3
 * Card Test 4*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "getCard.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// mine card

int main(){
   struct gameState G, testG;
   int seed = 10000;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   int numPlayers = 2;
   int i;
   int pass = 1;

   initializeGame(numPlayers, k, seed, &G);

   int counter = 0;
//   while(counter < 500){
{
   counter++;
   printf("---------- TESTING CARD: minee ----------\n");

   printf("Before: \n");

   int handCount = G.handCount[0];

   printf("-Hand: ");
   for(i = 0; i < G.handCount[0]; i++){
	printf("%s ", getCardName(G.hand[0][i]));
   }
   printf("\n-Size: %d\n", G.handCount[0]);

   printf("-Deck: ");
   for(i = 0; i < G.deckCount[0]; i++){
	printf("%s ", getCardName(G.deck[0][i]));
   }
   printf("\n-Size: %d\n", G.deckCount[0]);

   printf("-Discard: ");
   for(i = 0; i < G.discardCount[0]; i++){
	printf("%s ", getCardName(G.discard[0][i]));
   }
   printf("\n-Size: %d\n", G.discardCount[0]);

   printf("-Played: ");
   for(i = 0; i < G.playedCardCount; i++){
	printf("%s ", getCardName(G.playedCards[i]));
   }
   printf("\n-Size: %d\n", G.playedCardCount);

   // copy the game state to a testcase
   memcpy(&testG, &G, sizeof(struct gameState));

   int j;
   int choice1, choice2, choice3;
   for(j = 0; j < 3; j++){
	if(j == 0)
	{
		choice1 = 1;
		choice2 = 0;
		choice3 = 0;
	}
	else if(j == 1)
	{
		choice1 = 0;
		choice2 = 1;
		choice3 = 0;
	}
	else if(j == 2)
	{
		choice1 = 0;
		choice2 = 0;
		choice3 = 1;
	}


   	printf("--TESTING: cardEffect & mine\n");
   	if(cardEffect(mine, choice1, choice2, choice3, &testG, 1, NULL) < 0){
		printf("TEST = FAILED >> cardEffect returned < 0\n");
		pass = 0;
   	}
   	else printf("TEST = PASSED\n");

   	printf("\nAfter: \n");

   	printf("-Hand: ");
   	for(i = 0; i < testG.handCount[0]; i++){
        	printf("%s ", getCardName(testG.hand[0][i]));
   	}
   	printf("\n-Size: %d\n", testG.handCount[0]);

   	printf("-Deck: ");
   	for(i = 0; i < testG.deckCount[0]; i++){
        	printf("%s ", getCardName(testG.deck[0][i]));
   	}
   	printf("\n-Size: %d\n", testG.deckCount[0]);

   	printf("-Discard: ");
   	for(i = 0; i < testG.discardCount[0]; i++){
        	printf("%s ", getCardName(testG.discard[0][i]));
   	}
   	printf("\n-Size: %d\n", testG.discardCount[0]);

   	printf("-Played: ");
   	for(i = 0; i < testG.playedCardCount; i++){
		printf("%s ", getCardName(testG.playedCards[i]));
   	}
   	printf("\n-Size: %d\n", testG.playedCardCount);

   	// mine
      int m;
      int result = 1;
      m = G.hand[0][choice1];  //store card we will trash

      if (G.hand[0][choice1] < copper || G.hand[0][choice1] > gold)
	{
	  result = -1;
//	  break;
	}
		
      if (choice2 > treasure_map || choice2 < curse)
	{
	  result = -1;
//	  break;
	}

      if ( (getCost(G.hand[0][choice1]) + 3) > getCost(choice2) )
	{
	  result = -1;
//	  break;
	}
	
      if (result){
      		gainCard(choice2, &G, 2, 0);

      		//discard card from hand
      		discardCard(0, 0, &G, 0);
      
      		//discard trashed card
	      for (i = 0; i < G.handCount[0]; i++)
	      {
      			if (G.hand[0][i] == m)
       	    		{
       				discardCard(i, 0, &G, 0);			
       	      	      		break;
            		}
      	      }
	}
         
   	printf("---Print Results\n");

   	printf("\nExpected: \n");

   	printf("-Hand: ");
   	for(i = 0; i < G.handCount[0]; i++){
        	printf("%s ", getCardName(G.hand[0][i]));
   	}
   	printf("\n-Size: %d\n", G.handCount[0]);

   	printf("-Deck: ");
   	for(i = 0; i < G.deckCount[0]; i++){
        	printf("%s ", getCardName(G.deck[0][i]));
   	}
   	printf("\n-Size: %d\n", G.deckCount[0]);

   	printf("-Discard: ");
   	for(i = 0; i < G.discardCount[0]; i++){
        	printf("%s ", getCardName(G.discard[0][i]));
   	}
   	printf("\n-Size: %d\n", G.discardCount[0]);

  	printf("-Played: ");
   	for(i = 0; i < G.playedCardCount; i++){
		printf("%s ", getCardName(G.playedCards[i]));
   	}
   	printf("\n-Size: %d\n", G.playedCardCount);

   	printf("\n\n--Results:\n");

   	printf("-Hand Count:\n");
   	printf("Expected: %d\nResults : %d\n", G.handCount[0], testG.handCount[0]);

   	printf("--TESTING HAND COUNT--\n");
   	if(G.handCount[0] != testG.handCount[0]){ printf("CARD FAILED AT >> Hand Count\n"); pass = 0;}
   	else{
		for(i = 0; i < G.handCount[0]; i++){
			if(G.hand[0][i] != testG.hand[0][i]){ printf("CARD FAILED AT >> Hands do not match\n"); pass = 0;}
		}
   	}
   	if(pass)
		printf("TESTING = PASSED\n");

   	printf("--TESTING HAND COUNT GAIN--\n");
   	if(testG.handCount[0] == (handCount)){
		printf("TESTING = PASSED\n");
   	}
   	else{
		printf("CARD FAILED AT >> Hand Count did not gain 1 cards & discard 1.\n");
		pass = 0;
   	}
   	printf("\n-Deck Count:\n");
  	printf("Expected: %d\nResults : %d\n", G.deckCount[0], testG.deckCount[0]);

   	printf("--TESTING DECK COUNT\n");
   	if(G.deckCount[0] != testG.deckCount[0]){ printf("CARD FAILED AT >> Deck Count\n"); pass = 0;}
   	else{
		for(i = 0; i < G.deckCount[0]; i++){
			if(G.deck[0][i] != testG.deck[0][i]){ printf("CARD FAILED AT >> Decks do not match\n"); pass = 0;}
		}
   	}
   	if(pass)
		printf("TESTING = PASSED\n");

   	printf("\n-Discard Count:\n");
   	printf("Expected: %d\nResults : %d\n", G.discardCount[0], testG.discardCount[0]);

   	printf("--TESTING DISCARD\n");
   	if(G.discardCount[0] != testG.discardCount[0]){ printf("CARD FAILED AT >> Discard Count\n"); pass = 0;}
   	else{
		for(i = 0; i < G.discardCount[0]; i++){
			if(G.discard[0][i] != testG.discard[0][i]){ printf("CARD FAILED AT >> Discards do not match\n"); pass = 0;}
		}	
   	}
   	if(pass)
		printf("TESTING = PASSED\n");

   	printf("--TESTING PLAYED CARDS\n");
   	if(testG.playedCardCount == G.playedCardCount){ 
   		printf("TEST = PASSED\n");
		for(i = 0; i < G.playedCardCount; i++){
			if(G.playedCards[i] != testG.playedCards[i]){
				printf("CARD FAILED AT >> Played cards do not match\n");
				pass = 0;
			}
		}
   	}
   	else{
		printf("CARD FAILED AT >> Played Card Count\n");
		pass = 0;
   	}

   	if(pass)
		printf(">>> TEST SUCCESSFUL <<<\n");
   	else
		printf(">>> TEST FAILED <<<\n");
   	}
   }
   return 0;
}

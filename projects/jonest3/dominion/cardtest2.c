/*jonest3
 * Card Test 2*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "getCard.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// smithy card

int main(){
   struct gameState G, testG;
   int seed = 10000;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   int numPlayers = 2;
   int i;
   int pass = 1;

   initializeGame(numPlayers, k, seed, &G);

   int counter = 0;
   while(counter < 500){
   counter++;
   printf("---------- TESTING CARD: smithy ----------\n");

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

   // copy the game state to a testcase
   memcpy(&testG, &G, sizeof(struct gameState));

   printf("--TESTING: cardEffect & smithy\n");
   if(cardEffect(smithy, 0, 0, 0, &testG, 0, NULL) < 0){
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

   // Smithy
   // +3 Cards
   for (i = 0; i < 3; i++)
   {
	drawCard(0, &G);
   }
   // discard card from hand
   discardCard(0, 0, &G, 0);

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
   if(testG.handCount[0] == (2+handCount)){
	printf("TESTING = PASSED\n");
   }
   else{
	printf("CARD FAILED AT >> Hand Count did not gain 3 cards & discard smithy.\n");
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

   if(pass)
	printf(">>> TEST SUCCESSFUL <<<\n");
   else
	printf(">>> TEST FAILED <<<\n");
   }
   return 0;
}

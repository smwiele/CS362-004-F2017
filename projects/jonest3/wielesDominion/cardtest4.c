/*jonest3
 * Card Test 4*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "getCard.h"
#include "interface.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// great_hall card

int main(){
   struct gameState G, testG;
   int seed = 10000;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   int numPlayers = MAX_PLAYERS;
   int i;
   int pass = 1;

   initializeGame(numPlayers, k, seed, &G);

   int counter = 0;
//   while(counter < 500){
//{
   counter++;
   printf("---------- TESTING CARD: great_hall ----------\n");

   printf("Before: \n");

   printf("-Hand: ");
   printHand(0, &G);
   printf("-Size: %d\n\n", G.handCount[0]);
   int handNum = G.handCount[0];

   printf("-Deck: ");
   printDeck(0, &G);
   printf("-Size: %d\n\n", G.deckCount[0]);
 
   printf("-Discard: ");
   printDiscard(0, &G);
   printf("-Size: %d\n\n", G.discardCount[0]);
 
   printf("-Played: ");
   printPlayed(0, &G);
   printf("-Size: %d\n\n", G.playedCardCount);
 
   printf("Game Action Count: %d\n\n", G.numActions);
   int numActions = G.numActions;

   // copy the game state to a testcase
   memcpy(&testG, &G, sizeof(struct gameState));

   printf("--TESTING: cardEffect & mine\n");
   if(cardEffect(great_hall, 0, 0, 0, &testG, 0, NULL) < 0){
	printf("TEST = FAILED >> cardEffect returned < 0\n");
	pass = 0;
   }
   else printf("TEST = PASSED\n");

   printf("\nAfter: \n");

   printf("-Hand: ");
   printHand(0, &testG);
   printf("-Size: %d\n\n", testG.handCount[0]);

   printf("-Deck: ");
   printDeck(0, &testG);
   printf("-Size: %d\n\n", testG.deckCount[0]);

   printf("-Discard: ");
   printDiscard(0, &testG);
   printf("-Size: %d\n\n", testG.discardCount[0]);

   printf("-Played: ");
   printPlayed(0, &testG);
   printf("-Size: %d\n\n", testG.playedCardCount);

   printf("Game Action Count: %d\n\n", testG.numActions);
   
   // great_hall
   drawCard(0, &G);
   G.numActions++;
   discardCard(0,0,&G,0);

   printf("------RESULTS-----\n");

   printf("\nExpected: \n");

   printf("-Hand: ");
   printHand(0, &G);
   printf("-Size: %d\n\n", G.handCount[0]);

   printf("-Deck: ");
   printDeck(0, &G);
   printf("-Size: %d\n\n", G.deckCount[0]);

   printf("-Discard: ");
   printDiscard(0, &G);
   printf("-Size: %d\n\n", G.discardCount[0]);

   printf("-Played: ");
   printPlayed(0, &G);
   printf("-Size: %d\n\n", G.playedCardCount);

   printf("Game Action Count: %d\n\n",G.numActions);

   printf("\n\n--Results:\n");

   printf("--Testing Hands--\n\n");
   printf("-Hand Count:\n");
   printf("Expected: %d\nResults: %d\n", G.handCount[0], testG.handCount[0]);
   pass = 1;
   if(G.handCount[0] != testG.handCount[0]) {printf("TEST FAILED @ Expected Hand Count != Results\n"); pass = 0;}
   else{
  	pass = 1;
	for(i = 0; i < G.handCount[0]; i++){
		if(G.hand[0][i] != testG.hand[0][i]) {printf("TEST FAILED @ Hands do not match.\n"); break; pass = 0;}
	}
   }
   if(pass)
	printf("TEST SUCCESSFUL\n");

   printf("--Testing Hand Increase by Exact Amount--\n");
   pass = 1;
   if(testG.handCount[0] != handNum) {printf("TEST FAILED @ Hand Count did not increase by 1\n"); pass = 0;}
   if(pass)
	printf("TEST SUCCESSFUL\n");

   printf("--Testing Decks--\n");
   printf("-Deck Count:\n");
   printf("Expected: %d\nResults: %d\n", G.deckCount[0], testG.deckCount[0]);
   pass = 1;
   if(G.deckCount[0] != testG.deckCount[0]) {printf("TEST FAILED @ Expected Deck Count != Results\n"); pass = 0;}
   else{
	pass = 1;
        for(i = 0; i < G.deckCount[0]; i++){
                if(G.deck[0][i] != testG.deck[0][i]) {printf("TEST FAILED @ Decks do not match.\n"); break; pass = 0;}
        }
   }
   if(pass)
	printf("TEST SUCCESSFUL\n");

   printf("--Testing Discard--\n");
   printf("-Discard Count:\n");
   printf("Expected: %d\nResults: %d\n", G.discardCount[0], testG.discardCount[0]);
   pass = 1;
   if(G.discardCount[0] != testG.discardCount[0]) {printf("TEST FAILED @ Expected Discard Count != Results\n"); pass = 0;}
   else{
        for(i = 0; i < G.discardCount[0]; i++){
                if(G.discard[0][i] != testG.discard[0][i]) {printf("TEST FAILED @ Discards do not match.\n"); break; pass = 0;}
        }
   }
   if(pass)
	printf("TEST SUCCESSFUL\n");

   printf("--Testing Played--\n");
   printf("-Played Count:\n");
   printf("Expected: %d\nResults: %d\n", G.playedCardCount, testG.playedCardCount);
   pass = 1;
   if(G.playedCardCount != testG.playedCardCount) {printf("TEST FAILED @ Expected Played Count != Results\n"); pass = 0;}
   else{
        for(i = 0; i < G.playedCardCount; i++){
                if(G.playedCards[i] != testG.playedCards[i]) {printf("TEST FAILED @ Played cards do not match.\n"); break; pass = 0;}
        }
   }
   if(pass)
	printf("TEST SUCCESSFUL\n");

   printf("--Testing Action Count--\n");
   printf("-# of Actions:\n");
   printf("Expected: %d\nResults: %d\n", G.numActions, testG.numActions);
   pass = 1;
   if(G.numActions != testG.numActions){ printf("TEST FAILED @ Expected Number of Actions != Results\n"); pass = 0;}

   if(testG.numActions != numActions+1){ printf("TEST FAILED @ Number of Actions != +1 Action\n"); pass = 0;}

   if(pass)
	printf("TEST SUCCESSFUL\n");
   return 0;
}

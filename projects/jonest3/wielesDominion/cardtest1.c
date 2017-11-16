/*jonest3
 * Card Test 1*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "getCard.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// adventurer card

int main(){
   struct gameState G, testG;
   int seed = 10000;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   int numPlayers = 2;
   int i;
   int pass = 0;
   int total_pass = 1;

   initializeGame(numPlayers, k, seed, &G);

   int counter = 0;
//   while(counter < 500){
{   
   counter++;
   printf("---------- TESTING CARD: adventurer ----------\n");

   printf("Before: \n");

   int replacementDeck[5] = { copper, silver, estate, estate, curse};
   
   G.hand[0][0] = adventurer;
   for(i = 0; i < 5; i++){
	G.deck[0][i] = replacementDeck[i];
   }

   G.deckCount[0] = 5;
 
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

   int prevTreasure = 0;
   for(i = 0; i < G.handCount[0]; i++){
	if(G.hand[0][i] == copper  ||  G.hand[0][i] == silver  ||  G.hand[0][i] == gold)
		prevTreasure += 1;
   }

   // copy the game state to a testcase
   memcpy(&testG, &G, sizeof(struct gameState));

   printf("--TESTING: cardEffect & adventurer\n");
   if(cardEffect(adventurer, 0, 0, 0, &testG, 0, NULL) < 0){
	printf("TEST = FAILED >> cardEffect returned < 0\n");
	total_pass = 0;
	pass = 0;
   }
   else{ printf("TEST = PASSED\n"); pass = 1;}

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

// adventurer
   int temphand[MAX_HAND];
   int drawntreasure = 0;
   int z = 0;

   while(drawntreasure<2){
	if (G.deckCount[0] <1){//if the deck is empty we need to shuffle discard and add to deck
		shuffle(0, &G);
	}
        drawCard(0, &G);
        int cardDrawn = G.hand[0][G.handCount[0]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		drawntreasure++;
        else{
            	temphand[z]=cardDrawn;
            	G.handCount[0]--; //this should just remove the top card (the most recently drawn one).
		z++;
       	}
   }
   while(z-1>=0){
       	G.discard[0][G.discardCount[0]++]=temphand[z-1]; // discard all cards in play that have been drawn
       	z=z-1;
   }

   discardCard(0,0,&G,0);

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
   pass = 1;
   if(G.handCount[0] != testG.handCount[0]) printf("CARD FAILED AT >> Hand Count\n");
   else{
	for(i = 0; i < G.handCount[0]; i++){
		if(G.hand[0][i] != testG.hand[0][i]){ printf("CARD FAILED AT >> Hands do not match\n"); pass = 0; total_pass = 0;}
	}
   }
   if(pass)
	printf("TESTING = PASSED\n");

   printf("--TESTING HAND COUNT GAINED 2\n");
   pass = 1;
   if(testG.handCount[0] != 7){ printf("CARD FAILED AT >> Hand did not equal 7 (+2)\n"); pass = 0;}
   else{
	int exTreasure = 0, resTreasure = 0;
	for(i = 0; i < testG.handCount[0]; i++){
		if(G.hand[0][i] == copper  ||  G.hand[0][i] == silver  ||  G.hand[0][i] == gold)
			exTreasure += 1;
		if(testG.hand[0][i] == copper  ||  testG.hand[0][i] == silver  ||  testG.hand[0][i]  == gold)
			resTreasure += 1;
	}
  	if(exTreasure != resTreasure){ printf("CARD FAILED AT >> Expected & Result treasure counts do not match\n"); pass = 0; total_pass = 0;}
	else if(resTreasure != prevTreasure + 2){ printf("CARD FAILED AT >> +2 Treasures not added to hand\n"); pass = 0; total_pass = 0;}
   }
   if(pass)
	printf("TESTING = PASSED\n");

   printf("\n-Deck Count:\n");
   printf("Expected: %d\nResults: %d\n", G.deckCount[0], testG.deckCount[0]);

   printf("--TESTING DECK COUNT\n");
   pass = 1;
   if(G.deckCount[0] != testG.deckCount[0]){ printf("CARD FAILED AT >> Deck Count\n"); pass = 0;}
   else{
	for(i = 0; i < G.deckCount[0]; i++){
		if(G.deck[0][i] != testG.deck[0][i]){ printf("CARD FAILED AT >> Decks do not match\n"); pass = 0; total_pass = 0;}
	}
   }
   if(pass)
	printf("TESTING = PASSED\n");

   printf("\n-Discard Count:\n");
   printf("Expected: %d\nResults: %d\n", G.discardCount[0], testG.discardCount[0]);

   printf("--TESTING DISCARD\n");
   pass = 1;
   if(G.discardCount[0] != testG.discardCount[0]){ printf("CARD FAILED AT >> Discard Count\n"); pass = 0; total_pass = 0;}
   else{
	for(i = 0; i < G.discardCount[0]; i++){
		if(G.discard[0][i] != testG.discard[0][i]){ printf("CARD FAILED AT >> Discards do not match\n"); pass = 0; total_pass = 0;}
	}
	
   }
   if(pass)
	printf("TESTING = PASSED\n");


   printf("-Played Count:\n");
   printf("Expected: %d\nResults: %d\n", G.playedCardCount, testG.playedCardCount);

   printf("--TESTING PLAYED\n");
   pass = 1;
   if(G.playedCardCount != testG.playedCardCount){ printf("CARD FAILED AT >> Played Card Count\n"); pass = 0; total_pass = 0;}
   else{
	for(i = 0; i < G.playedCardCount; i++){
		if(G.playedCards[i] != testG.playedCards[i]){ printf("CARD FAILED AT >> Played do not match\n"); pass = 0; total_pass = 0;}
	}
   }
   if(pass)
	printf("TESTING = PASSED\n");


   if(total_pass)
	printf(">>> TEST SUCCESSFUL <<<\n");
   else
	printf(">>> TEST FAILED <<<\n");
   }
   return 0;
}

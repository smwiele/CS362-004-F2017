/*
 * Taylor Jones jonest3
 * Card: smithy 
 *
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define TEST_RUNS 500
#define CARD_TESTS


int main(){
   printf("* RANDOM TESTING SMITHY CARD *\n\n");

   int cards[] = {     curse, estate, duchy, province, copper, silver,
                       gold, adventurer, council_room, feast, gardens,
                       mine, remodel, smithy, village, baron, great_hall,
                       minion, steward, tribute, ambassador, cutpurse,
                       embargo, outpost, salvager, sea_hag, treasure_map       };
 
   struct gameState G, testG;
   int seed = 1000;
   int k[10];
   int numPlayers;;
   int rand_int;
   int rand_hand;
   int rand_deck;
   int rand_discard;
   int total_passes; // counts the total number of tests that were passed

   int i;

   for(i = 1; i <= TEST_RUNS; i++){
        printf("-- Test #: %d\n", i);
        // randomize number of players between 2 and 4
        numPlayers = rand() % (4 + 1 - 2) + 2;
        printf("-- # Players: %d\n", numPlayers);

        k[0] = adventurer; // make sure adventurer is included

        int j;
        int numSelected = 1;
        int used;
        int passes = 0; // counts the number of tests passed

        // Get random kingdom cards
        while(numSelected < 10){
                used = 0;
                // rand_int used for random card selection
                rand_int = rand() % (26 + 1 - 8) + 8; // kingdom cards are elements 7-26
                for(j = 1; j < numSelected; j++){
                        if(k[j] == cards[rand_int]){
                                used = 1;
                                break;
                        }
                }
                if(used == 1) continue;
                k[j] = cards[rand_int];
                numSelected++;
        }

        initializeGame(numPlayers, k, seed, &G);

        // Set up decks with 0 to 10 cards
        rand_hand = rand() % (10 + 1);
        G.handCount[0] = rand_hand;
        G.hand[0][0] = smithy;

        rand_deck = rand() % (10 + 1);
        G.deckCount[0] = rand_deck;

        rand_discard = rand() % (10 + 1);
        G.discardCount[0] = rand_discard;

        printf("\n\n---- Card Counts ----\n");
        printf("-    Hand Count: %d\n", rand_hand);
        printf("-    Deck Count: %d\n", rand_deck);
        printf("- Discard Count: %d\n", rand_discard);

	memcpy(&testG, &G, sizeof(struct gameState));

        printf("\n--- INITIAL DECKS ---\n\n");
        char name[MAX_STRING_LENGTH];

        printf("   Hand:  ");
        for(j = 0; j < G.handCount[0]; j++){
                cardNumToName(G.hand[0][j], name);
                printf("%s ", name);
        }
        printf("\n");

        printf("   Deck:  ");
        for(j = 0; j < G.deckCount[0]; j++){
                cardNumToName(G.deck[0][j], name);
                printf("%s ", name);
        }
        printf("\n");

        printf("Discard:  ");
        for(j = 0; j < G.discardCount[0]; j++){
                cardNumToName(G.discard[0][j], name);
                printf("%s ", name);
        }
        printf("\n");

        printf(" Played:  ");
        printf("\n");

/****************************************************************/
	// What smithy should do
	for(j = 0; j < 3; j++){
		drawCard(0, &G);
	}

	discardCard(0, 0, &G, 0);
/****************************************************************/

        printf("\n--- EXPECTED DECKS ---\n\n");

        printf("   Hand:  ");
        for(j = 0; j < G.handCount[0]; j++){
                cardNumToName(G.hand[0][j], name);
                printf("%s ", name);
        }
        printf("\n");

        printf("   Deck:  ");
        for(j = 0; j < G.deckCount[0]; j++){
                cardNumToName(G.deck[0][j], name);
                printf("%s ", name);
        }
        printf("\n");

        printf("Discard:  ");
        for(j = 0; j < G.discardCount[0]; j++){
                cardNumToName(G.discard[0][j], name);
                printf("%s ", name);
        }
        printf("\n");

        printf(" Played:  ");
        for(j = 0; j < G.playedCardCount; j++){
                cardNumToName(G.playedCards[j], name);
                printf("%s ", name);
        }
        printf("\n");



        memcpy(&testG, &G, sizeof(struct gameState));

        cardEffect(adventurer, 0, 0, 0, &testG, 0, NULL);

        printf("\n--- RESULTING DECKS ---\n\n");

        printf("   Hand:  ");
        for(j = 0; j < testG.handCount[0]; j++){
                cardNumToName(testG.hand[0][j], name);
                printf("%s ", name);
        }
        printf("\n");

        printf("   Deck:  ");
        for(j = 0; j < testG.deckCount[0]; j++){
                cardNumToName(testG.deck[0][j], name);
                printf("%s ", name);
        }
        printf("\n");

        printf("Discard:  ");
        for(j = 0; j < testG.discardCount[0]; j++){
                cardNumToName(testG.discard[0][j], name);
                printf("%s ", name);
        }
        printf("\n");

        printf(" Played:  ");
        for(j = 0; j < testG.playedCardCount; j++){
                cardNumToName(testG.playedCards[j], name);
                printf("%s ", name);
        }
        printf("\n");

/*********************************************************************/
        // Check to see if card passed all tests
        if(passes == CARD_TESTS){
                printf("***** TRIAL PASSED ALL TESTS *****\n\n");
                total_passes++;
        }
        else{
                printf("***** TRIAL FAILED *****\n\n");
        }
   }

   printf("* TOTAL %d PASSED RUNS OUT OF %d TRIALS *\n\n", total_passes, TEST_RUNS);
   
   return 0;
}

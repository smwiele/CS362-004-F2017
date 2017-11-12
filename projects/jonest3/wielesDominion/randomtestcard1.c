/*
 * Taylor Jones jonest3
 * Card: village 
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

#define TEST_RUNS 50000
#define CARD_TESTS 4


int main(){
   printf("* RANDOM TESTING VILLAGE CARD *\n\n");

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
   int rand_actions;
   int total_passes; // counts the total number of tests that were passed

   int i;

   for(i = 1; i <= TEST_RUNS; i++){
        printf("-- Test #: %d\n", i);
        // randomize number of players between 2 and 4
        numPlayers = rand() % (4 + 1 - 2) + 2;
        printf("-- # Players: %d\n", numPlayers);

        k[0] = village; // make sure adventurer is included

        int j;
        int numSelected = 1;
        int used;
        int passes = 0; // counts the number of tests passed

        // Get random kingdom cards
        while(numSelected < 10){
                used = 0;
                // rand_int used for random card selection
                do{
	                rand_int = rand() % (26 + 1 - 8) + 8; // kingdom cards are elements 7-26
		}while(rand_int == village);

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
        rand_hand = rand() % (10 + 1 - 1) + 1;
        G.handCount[0] = rand_hand;
        G.hand[0][0] = village;

        rand_deck = rand() % (10 + 1);
        G.deckCount[0] = rand_deck;

        rand_discard = rand() % (10 + 1);
        G.discardCount[0] = rand_discard;

	rand_actions = rand() % (100 + 1);
	G.numActions = rand_actions;

        printf("\n\n---- Card Counts ----\n");
        printf("-    Hand Count: %d\n", rand_hand);
        printf("-    Deck Count: %d\n", rand_deck);
        printf("- Discard Count: %d\n", rand_discard);
	printf("- Actions Count: %d\n", rand_actions);

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


// 	What village should do
	drawCard(0, &G);
	G.numActions += 2;
	discardCard(0, 0, &G, 0);

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

//        memcpy(&testG, &G, sizeof(struct gameState));

        cardEffect(village, 0, 0, 0, &testG, 0, NULL);

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
	printf("*** Testing: Actions Increased by 2 ***\n");

	printf("Result: ");
	if(testG.numActions == rand_actions + 2){
		printf("PASSED\n\n");
		passes++;
	}
	else{
		printf("FAILED\n\n");
		if(testG.numActions > rand_actions + 2)
			printf("Test Actions had more actions added than 2.\n");
		else
			printf("Test Actions had less actions than expected.\n");
	}

	printf("*** Testing: Hand Size Stays the Same (- Village + New Card) ***\n");

	printf("Results: ");
	if(testG.handCount[0] == rand_hand){
		printf("PASSED\n\n");
		passes++;
	}
	else{
		printf("FAILED\n\n");
		if(testG.handCount[0] > rand_hand)
			printf("Test Hand has too many cards in hand.\n");
		else
			printf("Test Hand has too few cards in hand.\n");
	}
	
	printf("*** Testing: great_hall Added to Played Deck ***\n");
	if(testG.playedCards[0] == village  &&  testG.playedCardCount == 1){
		printf("PASSED\n\n");
		passes++;
	}
	else{
		printf("FAILED\n\n");
		if(testG.playedCards[0] != village)
			printf("Last card played was not Village\n");

		if(testG.playedCardCount > 1){
			printf("Too many cards added to play deck.\n");
		}
		else if(testG.playedCardCount < 1)
			printf("Too few cards added to play deck.\n");
	}

	printf("*** Testing: 1 card removed from deck ***\n");
	if(rand_deck != 0){
		if(testG.deckCount[0] == rand_deck - 1){
			printf("PASSED\n\n");
			passes++;
		}
		else{
			printf("FAILED\n\n");
			if(testG.deckCount[0] > rand_deck - 1)
				printf("Deck Count has too many cards.\n");
			else
				printf("Deck Count has too few cards.\n");
		}
	}
	else{
		if(testG.discardCount[0] == 0  &&  testG.deckCount[0] == rand_discard - 1){
			printf("PASSED\n\n");
			passes++;
		}
		else{
			printf("FAILED\n\n");
			if(testG.discardCount[0] > 0)
				printf("Discard Deck not reset or started with 0.\n");
			if(testG.deckCount[0] > rand_discard - 1)
				printf("New deck failed to discard card into player's hand.\n");
			else if(testG.deckCount[0] < rand_discard - 1)
				printf("New deck discarded too many cards.\n");
		}
	}
		

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

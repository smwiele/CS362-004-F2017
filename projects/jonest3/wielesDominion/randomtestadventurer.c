/*
 * Taylor Jones jonest3
 * Card: Adventurer
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h" // print all the decks
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TEST_RUNS 500
#define CARD_TESTS 6 // the number of specific checks for current player
#define CHECK_OTHERS_DECKS 4 // check other players' decks for changes

int main(){
   printf("* RANDOM TESTING ADVENTURER CARD *\n\n");

   int cards[] = {	curse, estate, duchy, province, copper, silver,
			gold, adventurer, council_room, feast, gardens,
			mine, remodel, smithy, village, baron, great_hall,
			minion, steward, tribute, ambassador, cutpurse,
			embargo, outpost, salvager, sea_hag, treasure_map	};

   

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
	G.hand[0][0] = adventurer;

	rand_deck = rand() % (10 + 1);
	G.deckCount[0] = rand_deck;

	rand_discard = rand() % (10 + 1);
	G.discardCount[0] = rand_discard;

	printf("\n\n---- Card Counts ----\n");
	printf("-    Hand Count: %d\n", rand_hand);
	printf("-    Deck Count: %d\n", rand_deck);
	printf("- Discard Count: %d\n", rand_discard);

	memcpy(&testG, &G, sizeof(struct gameState));

	int init_hand_advent_count, init_played_advent_count = 0;

	for(j = 0; j < G.handCount[0]; j++){
		if(G.hand[0][j] == adventurer)
			init_hand_advent_count++;
	}

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

	/***********************************************/
	int tempHand[MAX_HAND];
	int drawnTreasure = 0;
	int cardDrawn;
	j = 0;
	
      	while(drawnTreasure<2){
		if (G.deckCount[0] <1){//if the deck is empty we need to shuffle discard and add to deck
	  		shuffle(0, &G);
		}
		drawCard(0, &G);
		cardDrawn = G.hand[0][G.handCount[0]-1];//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  		drawnTreasure++;
		else{
	  		tempHand[j]=cardDrawn;
	  		G.handCount[0]--; //this should just remove the top card (the most recently drawn one).
	  		j++;
		}
      	}
      	while(j-1>=0){
		G.discard[0][G.discardCount[0]++]=tempHand[j-1]; // discard all cards in play that have been drawn
		j=j-1;
      	}

	discardCard(0, 0, &G, 0);
/***********************************************************************/

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

/***********************************************************************/
//	memcpy(&testG, &G, sizeof(struct gameState));

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

/***************************************************************************/	
	printf("\n** Testing: Current Player's Hand Count **\n");

	printf("*** Result: ");
	if(G.handCount[0] == testG.handCount[0]){
		printf("PASSED ***\n");
		passes++;
	}
	else{
		printf("FAILED ***\n");
		if(G.handCount[0] > testG.handCount[0])
			printf("Test Hand has less cards than expected.\n");
		
		else
			printf("Test Hand has more cards than expected.\n");
	}

	printf("** Testing: Current Player's Deck Count **\n");

	printf("*** Result: ");
	if(G.deckCount[0] == testG.deckCount[0]){
		printf("PASSED ***\n");
		passes++;
	}
	else{
		printf("FAILED ***\n");
		if(G.deckCount[0] > testG.deckCount[0])
			printf("Test Deck has less cards than expected.\n");

		else
			printf("Test Deck has more cards than expected.\n");
	}

	printf("** Testing: Current Player's Discard Count **\n");

	printf("*** Result: ");
	if(G.discardCount[0] == testG.discardCount[0]){
		printf("PASSED ***\n");
		passes++;
	}
	else{
		printf("FAILED ***\n");
		if(G.discardCount[0] > testG.discardCount[0])
			printf("Test Discard has less cards than expected.\n");

		else
			printf("Test discard has more cards than expected.\n");
	}

	printf("** Testing: Game's Played Card Count **\n");

	printf("*** Result: ");
	if(G.playedCardCount == testG.playedCardCount){
		printf("PASSED ***\n");
		passes++;
	}
	else{
		printf("FAILED ***\n");
		if(G.playedCardCount > testG.playedCardCount)
			printf("Test Played has less cards than expected.\n");

		else
			printf("Test Played has more cards than expected.\n");
	}

	printf("** Testing: 2 Treasures Added to Player's Hand **\n");

	printf("*** Result: ");
	int expect_treas_count, result_treas_count = 0;
	
	for(j = 0; j < G.handCount[0]; j++){
		if(G.hand[0][j] == copper  ||  G.hand[0][j] == silver  ||  G.hand[0][j] == gold){
			expect_treas_count++;
		}
	}

	for(j = 0; j < testG.handCount[0]; j++){	
		if(testG.hand[0][j] == copper  ||  testG.hand[0][j] == silver  ||  testG.hand[0][j] == gold){
			result_treas_count++;
		}
	}
	
	if(expect_treas_count == result_treas_count){
		printf("PASSED ***\n");
		passes++;
	}
	else{
		printf("FAILED ***\n");
		if(expect_treas_count > result_treas_count)
			printf("Player's hand has less treasure cards than expected.\n");
		
		else
			printf("Player's hand has more treasure cards than expected.\n");
	}

	printf("** Testing: Adventurer Card Played **\n");
	
	printf("*** Result: ");
	int result_hand_advent_count, result_played_advent_count = 0;
	int expect_hand_advent_count, expect_played_advent_count = 0;	

	for(j = 0; j < testG.handCount[0]; j++){
		if(testG.hand[0][j] == adventurer)
			result_hand_advent_count++;
	}

	for(j = 0; j < testG.playedCardCount; j++){
		if(testG.playedCards[j] == adventurer)
			result_played_advent_count++;
	}

	for(j = 0; j < G.handCount[0]; j++){
		if(G.hand[0][j] == adventurer)
			expect_hand_advent_count++;
	}

	for(j = 0; j < G.playedCardCount; j++){
		if(G.playedCards[j] == adventurer)
			expect_hand_advent_count++;
	}

	if(expect_hand_advent_count == result_hand_advent_count  &&  expect_played_advent_count ==  result_played_advent_count  &&  result_hand_advent_count == init_hand_advent_count - 1  &&  result_played_advent_count == init_played_advent_count + 1){
		printf("PASSED ***\n");
		passes++;
	}
	else{
		printf("FAILED ***\n");

		if(expect_hand_advent_count > result_hand_advent_count)
			printf("Test Hand has less adventurer card(s) than expected.\n");
		else
			printf("Test Hand has more adventurer card(s) than expected.\n");

		if(expect_played_advent_count > result_played_advent_count)
			printf("Test Played has less adventurer card(s) than expected.\n");
		else
			printf("Test Played has more adventurer card(s) than expected.\n");
		if(result_hand_advent_count > init_hand_advent_count - 1)
			printf("Test Hand failed to discard adventurer card from original hand.\n");
		else
			printf("Test Hand discarded too many adventurer cards from original hand.\n");

		if(result_played_advent_count > init_played_advent_count + 1)
			printf("Test Played has more than 1 new additional adventurer card.\n");
		else
			printf("Test Played has less adventurer cards than expected.\n");
	}
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

/* jonest3
 * Unit Test 3*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "getCard.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// gainCard(int supplyPos, struct gameState *state, int toFlag, int player);

// toFlag == 0: add to discard
// toFlag == 1: add to deck
// toFlag == 2: add to hand

void clear_Deck_Discard_Hand(struct gameState *state);
void printPlayersCards(int testCase, int player, struct gameState *state);
int check_if_gained(int card, int testCase, int player, struct gameState *state);

int main(){

   printf("TESTING gainCard()\n\n");

   // set up game
   printf("MAX_PLAYERS = %d\n", MAX_PLAYERS);

   int numPlayers = MAX_PLAYERS;
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, 
		tribute, smithy};
   int seed = 1000;
   
   initializeGame(numPlayers, k, seed, &G);

   int cardArray[] = {curse, estate, duchy, province,
		      copper, silver, gold,
		      adventurer, council_room, feast, gardens, mine,
		      remodel, smithy, village,
		      baron, great_hall, minion, steward, tribute, 
		      ambassador, cutpurse, embargo, outpost, salvager, 
		      sea_hag, treasure_map};

   // Clear discard, deck, and hands for all players
   clear_Deck_Discard_Hand(&G);

   int testCase;
   int i,j,m;
//   int gained; // 0 = true

   for(i = 0; i < 28; i++){
	printf("--Card: %s\n\n", getCardName(cardArray[i]));

	for(j = 0; j < MAX_PLAYERS; j++){
   		for(testCase = 0; testCase < 3; testCase++){
			if(testCase == 0){
				printf("Testing Gaining %s to Discard for Player %d:\n", getCardName(cardArray[i]),j);                                   
				gainCard(cardArray[i], &G, 0, j);
			}
			else if(testCase == 1){
				printf("Testing Gaining %s to Deck for Player %d:\n", getCardName(cardArray[i]),j);
				gainCard(cardArray[i], &G, 1, j);

			}
			else{
				printf("Testing Gaining %s to Hand for Player %d:\n", getCardName(cardArray[i]),j);
				gainCard(cardArray[i], &G, 2, j);
			}
		
			if(check_if_gained(cardArray[i],testCase, j, &G)){
				printf("--TEST PASSED--\n");
				for(m = 0; m < MAX_PLAYERS; m++){
					printPlayersCards(testCase, m, &G);
				}
			}
			else{
				printf("Supply of %s was empty; COULD NOT GAIN\n", getCardName(cardArray[i]));
				printf("--TEST PASSED--\n");				
			}
	   	}
	}
   }

   return 0;
}

void clear_Deck_Discard_Hand(struct gameState *state){

   int i;

   for(i = 0; i < MAX_PLAYERS; i++){
	state->deck[i][0] = 0;
	state->deckCount[i] = 0;
	state->discard[i][0] = 0;
	state->deckCount[i] = 0;
	state->hand[i][0] = 0;
	state->handCount[i] = 0;
   }
}

void printPlayersCards(int testCase, int player, struct gameState *state){
   int i;


   printf("Player %d: ", player);

   if(testCase == 0){
	for(i = 0; i < state->discardCount[player]; i++){
		printf("%s ", getCardName(state->discard[player][i]));
	}
   }
   else if(testCase == 1){
	for(i = 0; i < state->deckCount[player]; i++){
		printf("%s ", getCardName(state->deck[player][i]));
	}
   }
   else{
	for(i = 0; i < state->handCount[player]; i++){
		printf("%s ", getCardName(state->hand[player][i]));
	}
   }
   printf("\n");
}

int check_if_gained(int card, int testCase, int player, struct gameState *state){

   if(testCase == 0){
	return (card == state->discard[player][(state->discardCount[player])-1]);
   }
   else if(testCase == 1){
	return (card == state->deck[player][(state->deckCount[player])-1]);
   }
   return (card == state->hand[player][(state->handCount[player])-1]);
   
} 

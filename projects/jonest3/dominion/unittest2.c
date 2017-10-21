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

// #define UNITTEST "shuffle"

int checkDeckCount(int player, struct gameState *state);
int checkShuffleFeature(int newDeck[], int size_array, int player, struct gameState *state);
void delay(int number_of_seconds);

int main(){
   printf("----------TESTING SHUFFLE----------\n");

   // Set up game
   int seed = 1000;
   int player = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState state;

   int *arrayOfDecks[MAX_PLAYERS];

   int testDeck[] = {curse, estate, duchy, province, copper, silver, gold,
		     adventurer, council_room, feast, gardens, mine, remodel,
		     smithy, village, baron, great_hall, minion, steward, tribute,
		     ambassador, cutpurse, embargo, outpost, salvager, sea_hag, 
		     treasure_map};

   arrayOfDecks[0] = testDeck;

   initializeGame(player, k, seed, &state);

   printf("--Check deckCount--\n");
   if(checkDeckCount(player, &state))
   {
	printf("Test Successfully Completed\n\n");

	int length_array = 5;//10;//26;

	int i;
	for(i = 2; i <= length_array; i++){
		printf("Deck Size: %d\n", i);
		checkShuffleFeature(arrayOfDecks[0],i,player,&state); 
		printf("\n");
	}
   }
   return 0;
}

int checkDeckCount(int player, struct gameState *state){

   int deckCount = -50;
   int i;
   int results;

   for(i = 0; i < 101; i++){
   	state->deckCount[player] = deckCount;
	results = shuffle(player, state);

	if(deckCount < 1  &&  results != -1)
	{
		printf("checkDeckCount fails at: %d\n", i);
		return 0;
	}
	deckCount++;
   }
   return 1;  // means successful
}

int checkShuffleFeature(int newDeck[], int size_array, int player, struct gameState *state){

// int deck[MAX_PLAYERS][MAX_DECK]
   state->deckCount[player] = size_array;
   int i;
   for(i = 0; i < size_array; i++){
	printf("%s ", getCardName(newDeck[i]));
	state->deck[player][i] = newDeck[i];
   }
   printf("\n");
   printf("Shuffle Tests:\n");
   
   int j;
   for(j = 0; j < 5; j++){
	delay(2);
	shuffle(player, state);

//   printf("\nDeck count: %d\n", state->deckCount[player]);
   	for(i = 0; i < state->deckCount[player]; i++){
		printf("%s ", getCardName(state->deck[player][i]));
	}
	printf("\n");
   }  
   printf("\n");

   return 0;
}

//http://www.geeksforgeeks.org/time-delay-c/
void delay(int number_of_seconds)
{
   int milli_seconds = 1000 * number_of_seconds;
   clock_t start_time = clock();
   while(clock() < start_time + milli_seconds);
}

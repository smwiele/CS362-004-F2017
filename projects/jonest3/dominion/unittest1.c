/* jonest3
 * Unit Test 1*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "getCard.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define UNITTEST "updateCoins"

long random_at_most(long max); // https://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range

const char* getCardName(enum CARD card);

int main(){
   printf("TESTING %s\n", UNITTEST);
   printf("MAX_HAND = %d\n", MAX_HAND);
   printf("MAX_PLAYERS = %d\n", MAX_PLAYERS);

   // set up cards and hands
   int *arrayOfHands[8];

   int allCopper[MAX_HAND];
   int allSilver[MAX_HAND];
   int allGold[MAX_HAND];
   int copperSilver[MAX_HAND];
   int silverGold[MAX_HAND];
   int goldCopper[MAX_HAND];
   int allThree[MAX_HAND];
   int mixedHand[MAX_HAND];
   
   int i,j;
   long rand;


   for(i = 0; i < 8; i++){
   	for(j = 0; j < MAX_HAND; j++){
   		allCopper[j] = copper;
   		allSilver[j] = silver;
   		allGold[j] = gold;

		rand = random_at_most(1);

		if((int)rand == 1){
			copperSilver[j] = copper;
			silverGold[j] = silver;
			goldCopper[j] = gold;
		}
		else{
			copperSilver[j] = silver;
			silverGold[j] = gold;
			goldCopper[j] = copper;
		}	

		rand = random_at_most(2);

		if((int)rand == 1)
			allThree[j] = copper;
		else if((int)rand == 2)	
			allThree[j] = silver;
		else
			allThree[j] = gold;

		rand = random_at_most(6);

		if((int) rand == 1)
			mixedHand[j] = curse;
		else if((int) rand == 2)
			mixedHand[j] = estate;
       		 else if((int) rand == 3)
                	mixedHand[j] = duchy;
	        else if((int) rand == 4)
        	        mixedHand[j] = province;
	        else if((int) rand == 5)
       		        mixedHand[j] = copper;
        	else if((int) rand == 6)
                	mixedHand[j] = silver;
        	else
                	mixedHand[j] = gold;
   	}
   	arrayOfHands[0] = allCopper;
   	arrayOfHands[1] = allSilver;
   	arrayOfHands[2] = allGold;
   	arrayOfHands[3] = copperSilver;
   	arrayOfHands[4] = silverGold;
   	arrayOfHands[5] = goldCopper;
   	arrayOfHands[6] = allThree;
   	arrayOfHands[7] = mixedHand;

   	int factor;

 //  for(i = 0; i <= 7; i++){
   	if(i == 0){	
		factor = 1;
		printf("---Testing ALL COPPER\n");
	}
	else if(i == 1){
		factor = 2;
		printf("---Testing ALL SILVER\n");
	}
	else if(i == 2){
		factor = 3;
		printf("---Testing ALL GOLD\n");
	}
	else if(i == 3)
		printf("---Testing COPPER & SILVER\n");
	else if(i == 4)
		printf("---Testing SILVER & GOLD\n");
	else if(i == 5)
		printf("---Testing GOLD & COPPER\n");
	else if(i == 6)
		printf("---Testing ALL THREE\n");
	else
		printf("---Testing MIXED HAND\n");

   	int numPlayers;
   	struct gameState G;
   	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		     sea_hag, tribute, smithy};
   	int bonus = 0;
	int seed = 10000;
	int currentHand;
	int success = 1;
	int copperCount;
	int silverCount;
	int goldCount;

   	for(numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++){
		printf("----------TESTING FOR %d PLAYERS----------\n", numPlayers);
		memset(&G, 23, sizeof(struct gameState));
		initializeGame(numPlayers, k, seed, &G);

		int player;
		for(player = 1; player <= numPlayers; player++){
			printf("Player %d:\n", player);

			for(currentHand = 0; currentHand < 5; currentHand++){
				printf("--Current Hand Size: %d\n",currentHand);
				G.handCount[player] = currentHand;
				memcpy(G.hand[player], arrayOfHands[i], sizeof(int) * currentHand);

				int y;
				copperCount = 0;
				silverCount = 0;
				goldCount = 0;

				for(y = 0; y < currentHand; y++){
					printf("Card: %s\n", getCardName((G.hand[player][y])));						
					if(G.hand[player][y] == copper)
						copperCount++;
					else if(G.hand[player][y] == silver)
						silverCount++;
					else if(G.hand[player][y] == gold)
						goldCount++;
				}

  				updateCoins(player, &G, bonus);

				int coinSum;

				if(i < 3){
					if(G.coins != currentHand * factor)
					{
						success = 0;
						printf("Error for Player %d at hand %d.\n",player, currentHand); 	
						printf("G.coins  = %d\n", G.coins);
						printf("Expected = %d\n", currentHand * factor);
					} 
				}
				else{
					if(i == 3)
						coinSum = (copperCount * 1) + (silverCount * 2);
					else if(i == 4)
						coinSum = (silverCount * 2) + (goldCount * 3);
					else if(i == 5)
						coinSum = (goldCount * 3) + (copperCount * 1);
					else
						coinSum = (goldCount * 3) + (silverCount * 2) + (copperCount * 1);
					
					if(G.coins != coinSum){
						success = 0;
						printf("Error for Player %d at hand %d.\n", player, currentHand);
						printf("G.coins  = %d\n", G.coins);
						printf("Expected = %d\n", coinSum);
					}	
				}
			}
			if(success)
				printf("Test = PASSED\n");
			if(player != MAX_PLAYERS){
				printf("Press [ENTER] to see next player.\n");
				while(getchar() != '\n');
			}
		}
   	}
	printf("Press [ENTER] to test next hand combination.\n");
	while(getchar() != '\n');
   }
   return 0;
}

// Assumes 0 <= max <= RAND_MAX
// Returns in the closed interval [0, max]
long random_at_most(long max) {
  unsigned long
  // max <= RAND_MAX < ULONG_MAX, so this is okay.
  	num_bins = (unsigned long) max + 1,
        num_rand = (unsigned long) RAND_MAX + 1,
        bin_size = num_rand / num_bins,
        defect   = num_rand % num_bins;

   long x;
   do {
   	x = random();
   }
   // This is carefully written not to overflow
   while (num_rand - defect <= (unsigned long)x);

   // Truncated division is intentional
   return x/bin_size;
}

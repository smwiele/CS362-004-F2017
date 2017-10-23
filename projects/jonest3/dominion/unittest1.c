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

   for(j = 0; j < MAX_HAND; j++){
	// set up 3 pure decks
	allCopper[j] = copper;
	allSilver[j] = silver;
	allGold[j] = gold;
	mixedHand[j] = gold;
	allThree[j] = gold;
	copperSilver[j] = silver;
	silverGold[j] = gold;
	goldCopper[j] = copper;

	// set up mixed deck
	if(j % 2 == 0)
		mixedHand[j] = curse;
	else if(j % 6 == 0)
		mixedHand[j] = estate;
	else if(j % 5 == 0)
               	mixedHand[j] = duchy;
        else if(j % 4 == 0)
       	        mixedHand[j] = province;
        else if(j % 3 == 0){
	        mixedHand[j] = copper;
		allThree[j] = copper;
	}
       	else if(j % 2 != 0){
               	mixedHand[j] = silver;
		allThree[j] = silver;
                copperSilver[j] = copper;
                silverGold[j] = silver;
                goldCopper[j] = gold;
	}
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

    for(i = 0; i < 8; i++){
        if(i == 0){
                factor = 1;
                printf("----------Testing ALL COPPER\n");
        }
        else if(i == 1){
                factor = 2;
                printf("----------Testing ALL SILVER\n");
        }
        else if(i == 2){
                factor = 3;
                printf("----------Testing ALL GOLD\n");
        }
        else if(i == 3)
                printf("----------Testing COPPER & SILVER\n");
        else if(i == 4)
                printf("----------Testing SILVER & GOLD\n");
        else if(i == 5)
                printf("----------Testing GOLD & COPPER\n");
        else if(i == 6)
                printf("----------Testing ALL THREE\n");
        else
                printf("----------Testing MIXED HAND\n");

   	for(numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++){
		printf("\n----------TESTING FOR %d PLAYERS----------\n", numPlayers);
		memset(&G, 23, sizeof(struct gameState));
		initializeGame(MAX_PLAYERS, k, seed, &G);

		int player;
		for(player = 1; player <= MAX_PLAYERS; player++){
			printf("Player %d:\n", player);

			for(currentHand = 0; currentHand < 5; currentHand++){
				G.handCount[player] = currentHand;
				printf("--Current Hand Size: %d\n", G.handCount[player]);
//                                printf("--Current Hand Size: %d\n", currentHand);

				memcpy(G.hand[player], arrayOfHands[i], sizeof(int) * MAX_HAND);

                                printf("--Current Hand Size: %d\n", G.handCount[player]);
				G.handCount[player] = currentHand;
  				updateCoins(player, &G, bonus);

				int y;

//                              printf("--Current Hand Size: %d\n", G.handCount[player]);
//				G.hand[player][3] = copper;
//				G.hand[player][4] = copper;

//                                G.handCount[player] = currentHand;

//				G.hand[player][5] = copper;
//				G.hand[player][6] = copper;
				for(y = 0; y < G.handCount[player]; y++){
					printf("Card: %s\n", getCardName(G.hand[player][y]));
					printf("y = %d and handCount = %d\n", y, G.handCount[player]);
				}
				if(i < 3){
					if(G.coins !=  G.handCount[player] * factor)
					{
						success = 0;
						printf("Error for Player %d at hand %d.\n", player, G.handCount[player]); 	
						printf("G.coins  = %d\n", G.coins);
						printf("Expected = %d\n", G.handCount[player] * factor);
						return 0;
					} 
				}
				else{
	     	                        int y;
	                                copperCount = 0;
                	                silverCount = 0;
                        	        goldCount = 0;

                                	for(y = 0; y < G.handCount[player]; y++){
	       	                                if(G.hand[player][y] == copper)
                	                                copperCount += 1;
                        	                else if(G.hand[player][y] == silver)
                                	                silverCount += 1;
	                                        else if(G.hand[player][y] == gold)
        	                                        goldCount += 1;
	                                }

					int coinSum;

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
						printf("Error for Player %d at hand %d.\n", player, G.handCount[player]);
						printf("G.coins  = %d\n", G.coins);
						printf("Expected = %d\n", coinSum);
						return 0;
					}	
				}
			}
			if(success)
				printf("Test = PASSED\n");
//			if(player != MAX_PLAYERS){
//				printf("Press [ENTER] to see next player.\n");
//				while(getchar() != '\n');
//			}
		}
   	}
//	if( i != 8){
//		printf("Press [ENTER] to test next hand combination.\n");
//		while(getchar() != '\n');
//	}
   }
   return 0;
}

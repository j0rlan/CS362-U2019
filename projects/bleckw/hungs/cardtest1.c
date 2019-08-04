/********************************************************************************************
 * Unit test 6
 * testing the initializeGame function in dominion.c
 * ******************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion_card_effects.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion_assert.h"
#include "rngs.h"
int k[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
int VCSupply[4] = {0, 0, 8, 12};

struct gameState state;
void unitTest(int numPlayers, int kingdomCards[10], int randomSeed){
   memset(&state, 0, sizeof(struct gameState));
   initializeGame(numPlayers, kingdomCards, 1, &state);
}

void assertSuite(int players, int estateSup, int copperSup, int cards[10], int cardSup[10]){
   
   printf("%d players:\n", players);
   printf("estate (#%d) supply is %d: ", estate, estateSup);
   assertTrue(supplyCount(estate, &state), estateSup); 

   printf("copper (#%d) supply is %d: ", copper, copperSup);
   assertTrue(supplyCount(copper, &state), copperSup); 
   
   printf("kingdomCards[0] (#%d) supply is %d: ", cards[0], cardSup[0]);
   assertTrue(supplyCount(cards[0], &state), cardSup[0]); 
}

int main(int argc, char* argv[])
{
   int k1[10];
   int i;
   int j;
   int k1sup[10];
   srand(time(0));
   int testNumber = 0;
   printf("\n*************************\n");
   printf("cardtest1.c : initializeGame");
   printf("\n*************************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("initializing a random 2 player game\n");
   for (i = 0, j = rand() % 20; i < 10; i++, j++) {
      k1[i] = k[j % 20];
      if (k1[i] == gardens || k1[i] == great_hall) {
         k1sup[i] = 8;
      }
      else {
         k1sup[i] = 10;
      }
   }
   unitTest(2, k1, rand());
   assertSuite(2, VCSupply[2], 60 - 7 * 2, k1, k1sup);
   
   printf("\ntest number %d:\n", ++testNumber);
   printf("same deck with 3 players\n");
   unitTest(3, k1, rand());
   assertSuite(3, VCSupply[3], 60 - 7 * 3, k1, k1sup);

   printf("\ntest number %d:\n", ++testNumber);
   printf("supply deck tries to have a second stack of provinces\n");
   k1[0] = province;
   k1sup[0] = 0;
   unitTest(3, k1, rand());
   assertSuite(3, VCSupply[0], 0, k1, k1sup);

   printf("\ntest number %d:\n", ++testNumber);
   printf("supply deck tries to have a second stack of silvers\n");
   k1[0] = silver;
   k1sup[0] = 0;
   unitTest(2, k1, rand());
   assertSuite(2, VCSupply[0], 0, k1, k1sup);

   printf("\ntest number %d:\n", ++testNumber);
   printf("supply deck tries to have two stack of the same card\n");
   k1[0] = k1[1];
   k1sup[0] = 0;
   unitTest(2, k1, rand());
   assertSuite(2, VCSupply[0], 0, k1, k1sup);

   return 0;
}

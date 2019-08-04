/********************************************************************************************
 * Unit test 3
 * testing the ambassador function in dominion.c
 * ******************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion_card_effects.h"
#include <string.h>
#include <stdio.h>
#include "dominion_assert.h"
#include "rngs.h"

struct gameState state;
int k[10] = {baron, minion, ambassador, tribute, mine, village, smithy, remodel, steward, gardens};

void unitTest(int cursesInHand, int returnQty){
   memset(&state, 0, sizeof(struct gameState));
   initializeGame(3, k, 1, &state);

   for (int j = 0; j < 3; j++){
      for (int i = 0; i < 5; i++){
         state.hand[j][i] = ambassador;
      }
      for (int i = 0; i < 10; i++){
         state.deck[j][i] = gold;
      }
   }
   for (int i = 0; i > cursesInHand; i++){
      state.hand[0][4-i] = curse;
   }

   ambassadorEffect(4, returnQty, 0, 0, &state);

}

void assertSuite(int thisScore, int nextScore, int handCount, int curseSupply){
   printf("current player has score %d: ", thisScore);
   assertTrue(scoreFor(0, &state), thisScore); 
   printf("opponents have score %d, %d: ", nextScore, nextScore);
   assertTrue(scoreFor(1, &state), nextScore);
   assertTrue(scoreFor(2, &state), nextScore);
   printf("current player hand count %d: ", handCount);
   assertTrue(state.handCount[0], handCount); 
   printf("game supply curse count %d: ", curseSupply);
   assertTrue(supplyCount(curse, &state), curseSupply); 
}

int main(int argc, char* argv[])
{
   int testNumber = 0;
   printf("\n********************\n");
   printf("unittest3.c : ambassador");
   printf("\n********************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("player reveals a curse, has 0 others, chooses to discard 0\n");
   unitTest(1, 0);
   assertSuite(-1, 0, 5, 20);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player reveals a curse, has 0 others, tries to discard 1\n");
   unitTest(1, 1);
   assertSuite(-1, 0, 5, 20);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player reveals a curse, has 1 other, chooses to discard 1\n");
   unitTest(2, 1);
   assertSuite(-1, -1, 4, 19);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player reveals a curse, has 2 others, chooses to discard 1\n");
   unitTest(3, 1);
   assertSuite(-2, -1, 4, 19);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player reveals a curse, has 2 others, chooses to discard 2\n");
   unitTest(3, 2);
   assertSuite(-1, -1, 3, 20);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player reveals a curse, has 3 others, chooses to discard 2\n");
   unitTest(4, 2);
   assertSuite(-2, -1, 3, 20);

   return 0;
}

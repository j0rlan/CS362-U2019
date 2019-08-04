/********************************************************************************************
 * Unit test 1
 * testing the baron function in dominion.c
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

void unitTest(int choice, int estates){
   memset(&state, 0, sizeof(struct gameState));
   initializeGame(2, k, 1, &state);
   state.handCount[0] = 5;
   for (int i = 0; i < 5; i++){
      state.hand[0][i] = baron;
   }
   for (int i = 0; i < 5; i++){
      state.deck[0][i] = smithy;
   }
   for (int i = 0; i < estates; i++){
      state.hand[0][i+1] = estate;
   }
   baronEffect(choice, &state, 0);
}

void assertSuite(int coins, int score, int remaining){
   printf("coins should equal             %d: ", coins);
   assertTrue(state.coins, coins);
   printf("score should equal             %d: ", score);
   assertTrue(scoreFor(0, &state), score);
   printf("estates in supply should equal %d: ", remaining);
   assertTrue(supplyCount(estate, &state), remaining);
}

int main(int argc, char* argv[])
{
   int testNumber = 0;
   printf("\n*******************\n");
   printf("unittest1.c : baron");
   printf("\n*******************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("choose not to discard, no estates in hand\n");
   unitTest(0, 0);
   assertSuite(0, 1, 7);


   printf("\ntest number %d:\n", ++testNumber);
   printf("choose to discard, no estates in hand\n");
   unitTest(1, 0);
   assertSuite(0, 1, 7);
   
   printf("\ntest number %d:\n", ++testNumber);
   printf("choose not to discard, one estate in hand\n");
   unitTest(0, 1);
   assertSuite(0, 2, 7);


   printf("\ntest number %d:\n", ++testNumber);
   printf("choose to discard, one estate in hand\n");
   unitTest(1, 1);
   assertSuite(4, 1, 8);

   printf("\ntest number %d:\n", ++testNumber);
   printf("choose to discard, four estates in hand\n");
   unitTest(1, 4);
   assertSuite(4, 4, 8);

   return 0;
}

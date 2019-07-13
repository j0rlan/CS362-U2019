/********************************************************************************************
 * Unit test 5
 * testing the mine function in dominion.c
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
int defSupply[7] = {-1, -1, -1, -1, 46, 40, 30};
void unitTest(int card1, int card2){
   memset(&state, 0, sizeof(struct gameState));
   initializeGame(2, k, 1, &state);

   for (int i = 0; i < 5; i++){
      state.hand[0][i] = mine;
   }
   for (int i = 0; i < 10; i++){
      state.deck[0][i] = smithy;
   }

   state.coins = 0;
   state.numActions = 0;
   state.handCount[0] = 3;
   state.deckCount[0] = 5;
   state.discardCount[0] = 0;
   state.discard[0][0] = -1;
   state.hand[0][1] = card1;

   _mine(1, card2, 0, 0, &state);

}

void assertSuite(int card1, int card2, int newSupply){
   printf("card1 (%d) is now card2 (%d): ", card1, card2);
   assertTrue(state.hand[0][1], card2); 
   printf("card2 supply is now %d: ", newSupply);
   assertTrue(supplyCount(card2, &state), defSupply[card2] - 1);
}

int main(int argc, char* argv[])
{
   int testNumber = 0;
   printf("\n********************\n");
   printf("unittest5.c : mine");
   printf("\n********************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("player mines a copper for a silver\n");
   unitTest(copper, silver);
   assertSuite(copper, silver, 39);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player mines a copper for a copper\n");
   unitTest(copper, copper);
   assertSuite(copper, copper, 45);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player mines a gold for a silver\n");
   unitTest(gold, silver);
   assertSuite(gold, silver, 39);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player mines a gold for a copper\n");
   unitTest(gold, silver);
   assertSuite(gold, silver, 39);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player tries to mine a copper for a gold\n");
   unitTest(copper, gold);
   assertSuite(copper, copper, 45);


   return 0;
}

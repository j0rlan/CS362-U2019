/********************************************************************************************
 * Unit test 4
 * testing the tribute function in dominion.c
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

void unitTest(int card1, int card2){
   memset(&state, 0, sizeof(struct gameState));
   initializeGame(2, k, 1, &state);

   for (int i = 0; i < 5; i++){
      state.hand[0][i] = tribute;
   }
   for (int i = 0; i < 10; i++){
      state.deck[0][i] = copper;
   }

   state.deckCount[1] = 1;
   state.discardCount[1] = 1;
   state.deck[1][0] = card1;
   state.discard[1][0] = card2;

   state.coins = 0;
   state.numActions = 0;
   state.handCount[0] = 4;
   state.deckCount[0] = 5;

   _tribute(0, 1, &state);

}

void assertSuite(int actions, int coins, int handCount, int deckCount, int card1, int card2){
   printf("player has actions %d: ", actions);
   assertTrue(state.numActions, actions); 
   printf("player has coins %d:   ", coins);
   assertTrue(state.coins, coins);
   printf("player hand count %d:  ", handCount);
   assertTrue(state.handCount[0], handCount); 
   printf("player deck count %d:  ", deckCount);
   assertTrue(state.deckCount[0], deckCount); 
   printf("next player has on discard pile: %d, %d :", card1, card2);
   assertTrue(state.discard[1][0], card1);
   printf("                                      :");
   assertTrue(state.discard[1][1], card2);
}

int main(int argc, char* argv[])
{
   int testNumber = 0;
   printf("\n********************\n");
   printf("unittest4.c : tribute");
   printf("\n********************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("next player deck's top two are both estates\n");
   unitTest(estate, estate);
   assertSuite(0, 0, 6, 3, estate, estate);

   printf("\ntest number %d:\n", ++testNumber);
   printf("next player deck's top two are an estate and a duchy\n");
   unitTest(estate, duchy);
   assertSuite(0, 0, 8, 1, estate, duchy);

   printf("\ntest number %d:\n", ++testNumber);
   printf("next player deck's top two are copper and estate\n");
   unitTest(copper, estate);
   assertSuite(0, 2, 6, 3, copper, estate);

   printf("\ntest number %d:\n", ++testNumber);
   printf("next player deck's top two are silver and adventurer\n");
   unitTest(silver, adventurer);
   assertSuite(2, 2, 4, 5, silver, adventurer);

   printf("\ntest number %d:\n", ++testNumber);
   printf("next player deck's top two are baron and a curse\n");
   unitTest(baron, curse);
   assertSuite(2, 0, 4, 5, baron, curse);

   printf("\ntest number %d:\n", ++testNumber);
   printf("next player deck's top two are province and outpost\n");
   unitTest(province, outpost);
   assertSuite(2, 0, 6, 3, province, outpost);

   return 0;
}

/********************************************************************************************
 * Unit test 2
 * testing the minion function in dominion.c
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

void unitTest(int choice1, int choice2, int thisHandSize, int nextHandSize){
   memset(&state, 0, sizeof(struct gameState));
   initializeGame(2, k, 1, &state);
   for (int j = 0; j < 2; j++){
      for (int i = 0; i < 5; i++){
         drawCard(j, &state);
         state.hand[j][i] = minion;
      }
      for (int i = 0; i < 5; i++){
         state.deck[j][i] = gold;
      }
      for (int i = 5; i < 10; i++){
         state.deck[j][i] = copper;
         state.deckCount[j]++;
      }
   }
   for (int i = 5; i > thisHandSize; i--){
      discardCard(i-1, 0, &state, 0);
   }
   for (int i = 5; i > nextHandSize; i--){
      discardCard(i-1, 1, &state, 0);
   }
   minionEffect(choice1, choice2, 0, 0, &state);
}

void assertSuite(int thisHand, int nextHand, int actions, int coins){
   printf("cards in this player's hand should equal %d: ", thisHand);
   assertTrue(state.handCount[0], thisHand);
   printf("cards in next player's hand should equal %d: ", nextHand);
   assertTrue(state.handCount[1], nextHand);
   printf("actions remaining should equal           %d: ", actions);
   assertTrue(state.numActions, actions);
   printf("coins should equal                       %d: ", coins);
   assertTrue(state.coins, coins);
}

int main(int argc, char* argv[])
{
   int testNumber = 0;
   printf("\n********************\n");
   printf("unittest2.c : minion");
   printf("\n********************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("player has 5 cards and chooses +2 coins\n");
   unitTest(1, 0, 5, 5);
   assertSuite(4, 5, 2, 2);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player has 5 cards and chooses to discard\n");
   unitTest(0, 1, 5, 5);
   assertSuite(4, 4, 2, 0);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player has 3 cards and chooses to discard\n");
   unitTest(0, 1, 3, 5);
   assertSuite(4, 4, 2, 0);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player has 5 cards, opponent has 3 cards, player chooses to discard\n");
   unitTest(0, 1, 4, 3);
   assertSuite(4, 3, 2, 0);

   printf("\ntest number %d:\n", ++testNumber);
   printf("both players have 3 cards, player chooses +2 coins\n");
   unitTest(1, 0, 3, 3);
   assertSuite(2, 3, 2, 2);

   return 0;
}

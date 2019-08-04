/********************************************************************************************
 * Unit test 10
 * testing the drawCard function in dominion.c
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
void deckInit(int players){
   memset(&state, 0, sizeof(struct gameState));
   initializeGame(players, k, 1, &state);
}

int drawCards(int player, int cards) {
   for (int i = 0; i < cards; i++){
      drawCard(player, &state);
   }
   return 0;
}

void assertSuite(int player, int hand, int deck, int discard){
   printf("player %d's hand count is %d: ", player, hand);
   assertTrue(state.handCount[player], hand);

   printf("player %d's deck count is %d: ", player, deck);
   assertTrue(state.deckCount[player], deck);

   printf("player %d's discard count is %d: ", player, discard);
   assertTrue(state.discardCount[player], discard);
}

int main(int argc, char* argv[])
{
   srand(time(NULL));
   int testNumber = 0;
   printf("\n*************************\n");
   printf("cardtest5.c : drawCard");
   printf("\n*************************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("initialized game with 2 players and starter decks: ");
   deckInit(2);
   assertTrue(state.numPlayers, 2);

   assertSuite(0, 5, 5, 0);
   assertSuite(1, 0, 10, 0);

   printf("\ntest number %d:\n", ++testNumber);
   printf("forcing player 0 to draw a card: ");
   assertTrue(drawCard(0, &state), 0);

   assertSuite(0, 6, 4, 0);

   printf("\ntest number %d:\n", ++testNumber);
   printf("forcing player 1 to draw a card: ");
   assertTrue(drawCard(1, &state), 0);

   assertSuite(1, 1, 9, 0);

   printf("\ntest number %d:\n", ++testNumber);
   printf("forcing player 1 to draw 9 cards: ");
   
   assertTrue(drawCards(1, 9), 0);

   assertSuite(1, 10, 0, 0);


   printf("\ntest number %d:\n", ++testNumber);
   printf("moving player 0's hand to discard: ");
   for (int i = 0; i < state.handCount[0]; i++) {
      state.discard[0][i] = state.hand[0][i];
      state.hand[0][i] = -1;
      state.discardCount[0]++;
   }
   state.handCount[0] = 0;
   
   assertSuite(0, 0, 4, 6);

   printf("\ntest number %d:\n", ++testNumber);
   printf("forcing player 4 to draw 4 cards: ");
   assertTrue(drawCards(0, 4), 0);

   assertSuite(0, 4, 0, 6);


   printf("\ntest number %d:\n", ++testNumber);
   printf("forcing player 4 to draw another card: ");
   assertTrue(drawCard(0, &state), 0);


   assertSuite(0, 5, 5, 0);

   return 0;
}

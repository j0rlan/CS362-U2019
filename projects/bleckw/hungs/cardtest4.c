/********************************************************************************************
 * Unit test 9
 * testing the getWinners function in dominion.c
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

void assertSuite(){


   printf("\nit is player turn: ");
   assertTrue(1, 1);

}

void printHandAndDeck(int player) {
   printf("hand and deck for player %d:\n", player);

   for(int i = 0; i < state.handCount[player]; i++){
      printf("%d\t", state.hand[player][i]);
   }

   for(int i = 0; i < state.deckCount[player]; i++){
      printf("%d\t", state.deck[player][i]);
   }
   printf("\n");
}

int main(int argc, char* argv[])
{
   srand(time(NULL));
   int players[4] = {-1, -1, -1, -1};
   int testNumber = 0;
   printf("\n*************************\n");
   printf("cardtest4.c : getWinners");
   printf("\n*************************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("initialized game with 3 players and starter decks: ");
   deckInit(3);
   assertTrue(state.numPlayers, 3);

   for (int i = 0; i < 3; i++) { printHandAndDeck(i); }

   printf("printing scores for all 3 players: 0: %d, 1: %d, 2: %d\n", scoreFor(0, &state), scoreFor(1, &state), scoreFor(2, &state));

   printf("set current player to 4 to revoke tiebreaking: ");
   state.whoseTurn = 3;
   assertTrue(state.whoseTurn, 3);

   getWinners(players, &state);

   printf("show first 3 tied for win (result 1) and player 4 did not win (result 0): ");
   for (int i = 0; i < 4; i++) {
      if (i != 3) {
         assertTrue(players[i], 1);
      } else {
         assertFalse(players[i], 1);
      }
      printf("\n                                                                  ");
   }


   return 0;
}

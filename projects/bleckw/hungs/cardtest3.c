/********************************************************************************************
 * Unit test 8
 * testing the endTurn function in dominion.c
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
void deckInit(int deck[MAX_DECK], int deckSize, int players){
   memset(&state, 0, sizeof(struct gameState));
   initializeGame(players, &k[rand() % 10], 1, &state);
   for (int j = 0; j < players; j++) {
      for (int i = 0; i < deckSize; i++) {
         state.deck[j][i] = deck[i];
      }
      state.deckCount[j] = deckSize;
      state.handCount[j] = 0;
      state.coins = 0;
   }

}
void printHand(int player) {
   if (state.handCount[player] == 0) {
      printf("hand is empty\n");
   }
   else {
      for (int i = 0; i < state.handCount[player]; i++) {
         printf("%d \t", state.hand[player][i]);
      }
   }
}

int compareDecks(int deck1[MAX_DECK], int deckSize1, int deck2[MAX_DECK], int deckSize2) {
   int j = 0;
   for (int i = 0; i < deckSize1; i++) {
      if (deck1[i] == deck2[i]) { j++; }
   }

   return j;
}

void assertSuite(int player1, int player2, int actions, int coins, int buys, int deck){

   for (int i = 0; i < state.numPlayers; i++) {
      printf("\nplayer %d's hand: ", i);
      printHand(i);
   }
   
   printf("\nit is player %d's turn: ", state.whoseTurn);
   assertTrue(state.whoseTurn, player1);
   
   printf("\nPlayer %d's actions = %d: ", player2, actions);
   assertTrue(state.numActions, actions);
   
   printf("\nPlayer %d's coins != %d: ", player2, coins);
   assertFalse(state.coins, coins);

   printf("\nPlayer %d's buys = %d: ", player2, buys);
   assertTrue(state.numBuys, buys);

   printf("\nPlayer %d has %d cards in deck: ", player2, deck);
   assertTrue(state.deckCount[player2], deck);
}

void top5(int player, int newHand[MAX_HAND]){
   for (int i = 0; i < 5; i++) {
      newHand[i] = state.deck[player][i];
   }
}

int main(int argc, char* argv[])
{
   srand(time(NULL));
   int testNumber = 0;
   int starterDeck[10] = {4, 4, 4, 4, 4, 4, 4, 1, 1, 1};
   printf("\n*************************\n");
   printf("cardtest3.c : endTurn");
   printf("\n*************************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("initialize game with two players and a starter deck\n");

   deckInit(starterDeck, 10, 2);

   assertSuite(0, 0, 1, 1, 1, 10);  

   printf("\ntest number %d:\n", ++testNumber);
   printf("call endTurn to advance to player 1\n");
   endTurn(&state);
   assertSuite(1, 1, 1, 0, 1, 5);

   printf("\ntest number %d:\n", ++testNumber);
   printf("call endTurn to advance to player 0\n");
   endTurn(&state);
   assertSuite(0, 0, 1, 0, 1, 5);

   printf("\ntest number %d:\n", ++testNumber);
   printf("call endTurn to advance to player 1\n");
   endTurn(&state);
   assertSuite(1, 1, 1, 0, 1, 0);

   printf("\ntest number %d:\n", ++testNumber);
   printf("call endTurn to advance to player 0\n");
   endTurn(&state);
   assertSuite(0, 0, 1, 0, 1, 0);

   printf("\ntest number %d:\n", ++testNumber);
   printf("call endTurn to advance to player 1\n");
   endTurn(&state);
   assertSuite(1, 1, 1, 0, 1, 5);

   printf("\ntest number %d:\n", ++testNumber);
   printf("initialize game with 3 players\n");
   deckInit(starterDeck, 10, 3);

   printf("it is player 0's turn: ");
   assertTrue(state.whoseTurn, 0);
   
   printf("ending turn\n");
   endTurn(&state);
   
   printf("it is player 1's turn: ");
   assertTrue(state.whoseTurn, 1);

   
   printf("ending turn\n");
   endTurn(&state);
   
   printf("it is player 2's turn: ");
   assertTrue(state.whoseTurn, 2);
   
   

   return 0;
}

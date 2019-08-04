/********************************************************************************************
 * Unit test 7
 * testing the shuffle function in dominion.c
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
   initializeGame(2, &k[rand() % 10], 1, &state);
   for (int j = 0; j < players; j++) {
      for (int i = 0; i < deckSize; i++) {
         state.deck[j][i] = deck[i];
      }
      state.deckCount[j] = deckSize;
   }
}

int compareDecks(int deck1[MAX_DECK], int deckSize1, int deck2[MAX_DECK], int deckSize2) {
   int j = 0;
   for (int i = 0; i < deckSize1; i++) {
      if (deck1[i] == deck2[i]) { j++; }
   }
   
   return j;
}

void assertSuite(int deck[MAX_DECK], int deckSize){

   printf("deck size is %d: ", deckSize);
   assertTrue(state.deckCount[0], deckSize); 

   printf("deck ordering:\n");
   for (int i = 0; i < state.deckCount[0]; i++) {
      printf("[%d]: %d\t", i, state.deck[0][i]);
      if( i > 1 && i % 10 == 0 ) { printf("\n"); }
   }

   printf("\n");

}

int main(int argc, char* argv[])
{
   int deck[MAX_DECK];
   int deck2[MAX_DECK];
   int deckSize;
   int deckSize2;
   srand(time(NULL));
   int testNumber = 0;
   printf("\n*************************\n");
   printf("cardtest2.c : shuffle");
   printf("\n*************************\n");

   printf("\ntest number %d:\n", ++testNumber);
   printf("shuffle starter deck\n");
   deckSize = 10;
   for (int i = 0; i < MAX_DECK; i++){
      if (i < 3) { deck[i] = estate; }
      else if (i < deckSize) { deck[i] = copper; }
      else { deck[i] = -1; }
   }
   deckInit(deck, deckSize, 2);

   printf("deck appears at least pseudorandom\n");
   shuffle(0, &state);
   assertSuite(deck, deckSize);   

   printf("\ntest number %d:\n", ++testNumber);
   printf("reinitialize and shuffle starter deck again\n");
   for (int i = 0; i < state.deckCount[0]; i++) {
      deck2[i] = state.deck[0][i];
   }
   deckSize2 = state.deckCount[0];
   deckInit(deck, deckSize, 2);

   printf("first shuffle is not the same as second shuffle\n");
   printf("matched deck positioning (first vs second shuffle) is not same as deckSize (%d): ", deckSize2);
   shuffle(0, &state);
   assertFalse(compareDecks(deck2, deckSize2, state.deck[0], state.deckCount[0]), deckSize2);

   printf("\ntest number %d:\n", ++testNumber);
   printf("player gains silver to deck and shuffles twice\n");
   gainCard(silver, &state, 1, 0);
   printf("before shuffles\n");
   assertSuite(deck, 11);
   shuffle(0, &state);
   printf("after first shuffle\n");
   assertSuite(deck, 11);
   shuffle(0, &state);
   printf("after second shuffle\n");
   assertSuite(deck, 11);

   printf("\ntest number %d:\n", ++testNumber);
   printf("two players initially do not have the same shuffle\n");
   deckInit(deck, deckSize, 2);
   shuffle(0, &state);
   shuffle(1, &state);
   printf("matched deck positioning (player 0 vs player 1) is not same as deckSize (%d): ", deckSize);
   assertFalse(compareDecks(state.deck[1], state.deckCount[1], state.deck[0], state.deckCount[0]), deckSize);
   
   return 0;
}

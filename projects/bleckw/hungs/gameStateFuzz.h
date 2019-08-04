#include <math.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"

#define RTDEBUG 1
#define TESTVOLUME 5000

int rando(int n){
   return floor(Random() * n);
}

struct gameState * fuzzGameState(struct gameState *state){
   state = (struct gameState *)malloc(sizeof(struct gameState));
   int i;
   for (i = 0; i < sizeof(struct gameState); i++){
      ((char *)state)[i] = floor(Random() * 256);
   }

   state->numPlayers = rando(MAX_PLAYERS - 1) + 2;

   for (i = 0; i < treasure_map + 1; i++ ){
      state->supplyCount[i] = rando(MAX_DECK);
   }

   for (i = 0; i < treasure_map + 1; i++ ){
      state->embargoTokens[i] = rando(MAX_DECK);
   }

   state->outpostPlayed = rando(MAX_DECK);

   state->outpostTurn = rando(MAX_DECK);

   state->whoseTurn = rando(state->numPlayers);

   state->phase = rando(3);

   state->numActions = rando(MAX_HAND);

   state->coins = rando(MAX_HAND);

   state->numBuys = rando(MAX_HAND);

   for (i = 0; i < MAX_PLAYERS; i++ ){
      int j;
      for (j = 0; j < MAX_HAND; j++){
         state->hand[i][j] = rando(treasure_map + 1);
      }
   }

   for (i = 0; i < MAX_PLAYERS; i++ ){
      state->handCount[i] = rando(MAX_HAND);
   }

   for (i = 0; i < MAX_PLAYERS; i++ ){
      int j;
      for (j = 0; j < MAX_DECK; j++){
         state->deck[i][j] = rando(treasure_map + 1);
      }
   }

   for (i = 0; i < MAX_PLAYERS; i++ ){
      state->deckCount[i] = rando(MAX_DECK);
   }

   for (i = 0; i < MAX_PLAYERS; i++ ){
      int j;
      for (j = 0; j < MAX_DECK; j++){
         state->discard[i][j] = rando(treasure_map + 1);
      }
   }

   for (i = 0; i < MAX_PLAYERS; i++ ){
      state->discardCount[i] = rando(MAX_DECK);
   }

   for (i = 0; i < MAX_DECK; i++){
      state->playedCards[i] = rando(MAX_DECK);
   }
   
   state->playedCardCount = rando(MAX_DECK);

   return state;
}

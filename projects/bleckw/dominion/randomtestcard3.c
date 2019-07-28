/********************************************************************************************
  Jordan Bleck
  bleckw@oregonstate.edu
  2019.07.24
  CS 362 Software Engineering II
  Assignment 4: Random Testing

card: tribute
_tribute(int int currentPlayer, int nextPlayer, struct gameState *state)
 ******************************************************************************************/
#include "gameStateFuzz.h"
#include <stdio.h>
#include <time.h>
#include <string.h>


int checkTribute(int currentPlayer, int nextPlayer, struct gameState *state);

int main(int argc, char* argv[]){

   SelectStream(2);
   PutSeed(time(NULL));

   struct gameState *state = NULL;
   int currentPlayer, nextPlayer, i, testFailed;
   int fails = 0;


   for (i = 0; i < TESTVOLUME; i++){
      state = fuzzGameState(state);
      currentPlayer = state->whoseTurn;
      nextPlayer = (currentPlayer + 1) % state->numPlayers;

      testFailed = checkTribute(currentPlayer, nextPlayer, state);

      if (testFailed != 0) { fails++; }
   }

   for (i = 0; i < (TESTVOLUME / 100); i++){
      state = fuzzGameState(state);
      currentPlayer = state->whoseTurn;
      nextPlayer = (currentPlayer + 1) % state->numPlayers;
      state->discardCount[nextPlayer] = 0;
      state->deckCount[nextPlayer] = 0;
      testFailed = checkTribute(currentPlayer, nextPlayer, state);

      if (testFailed != 0) { fails++; }

      state = fuzzGameState(state);
      currentPlayer = state->whoseTurn;
      nextPlayer = (currentPlayer + 1) % state->numPlayers;
      state->discardCount[nextPlayer] = 1;
      state->deckCount[nextPlayer] = 0;
      testFailed = checkTribute(currentPlayer, nextPlayer, state);

      if (testFailed != 0) { fails++; }

      state = fuzzGameState(state);
      currentPlayer = state->whoseTurn;
      nextPlayer = (currentPlayer + 1) % state->numPlayers;
      state->discardCount[nextPlayer] = 0;
      state->deckCount[nextPlayer] = 1;
      testFailed = checkTribute(currentPlayer, nextPlayer, state);

      if (testFailed != 0) { fails++; }

      state = fuzzGameState(state);
      currentPlayer = state->whoseTurn;
      nextPlayer = (currentPlayer + 1) % state->numPlayers;
      state->discardCount[nextPlayer] = 1;
      state->deckCount[nextPlayer] = 1;
      testFailed = checkTribute(currentPlayer, nextPlayer, state);

      if (testFailed != 0) { fails++; }
   }

   printf("test failed %d%%\n", fails * 100 / TESTVOLUME);

   free(state);
   return 0;
}

int checkTribute(int currentPlayer, int nextPlayer, struct gameState *state){
   char *msg;
   if (RTDEBUG == 1){
      msg = "players: %d, currentplayer: %d, nextplayer: %d\n";
      printf(msg, state->numPlayers, currentPlayer, nextPlayer);
   }

   struct gameState pre;
   memcpy(&pre, state, sizeof(struct gameState));

   int i, r, check;
   r = _tribute(currentPlayer, nextPlayer, state);

   if (r != 0){
      printf("_tribute returned %d\n", r);
   }

   check = memcmp(&pre, state, sizeof(struct gameState));

   if (RTDEBUG !=0){
      if (check != 0){
         msg = "test %d failed with currentPlayer: %d, nextPlayer %d\n";
         printf(msg, i, currentPlayer, nextPlayer);
      }
   }
   return check;
}

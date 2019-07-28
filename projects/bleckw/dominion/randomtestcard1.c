/********************************************************************************************
  Jordan Bleck
  bleckw@oregonstate.edu
  2019.07.24
  CS 362 Software Engineering II
  Assignment 4: Random Testing

card: baron
_baron(int choice1, int currentPlayer, int nextPlayer, struct gameState *state)
 ******************************************************************************************/
#include "gameStateFuzz.h"
#include <stdio.h>
#include <time.h>
#include <string.h>


int checkBaron(int choice1, int currentPlayer, int nextPlayer, struct gameState *state);

int main(int argc, char* argv[]){

   SelectStream(2);
   PutSeed(time(NULL));

   struct gameState *state = NULL;
   int choice1, currentPlayer, nextPlayer, i, testFailed;
   int fails = 0;


   for (i = 0; i < TESTVOLUME; i++){
      state = fuzzGameState(state);
      choice1 = floor(Random() * 2);
      currentPlayer = state->whoseTurn;
      nextPlayer = (currentPlayer + 1) % state->numPlayers;

      testFailed = checkBaron(choice1, currentPlayer, nextPlayer, state);

      if (testFailed != 0) { fails++; }
      free(state);
   }

   for (i = 0; i < TESTVOLUME / 10; i++){
      // set first card in hand to estate
      state = fuzzGameState(state);
      // setting choice1 explicitly
      choice1 = floor(Random() * 2);
      currentPlayer = state->whoseTurn;
      nextPlayer = (currentPlayer + 1) % state->numPlayers;
      // setting estate in hand
      state->hand[currentPlayer][0] = estate;

      testFailed = checkBaron(choice1, currentPlayer, nextPlayer, state);

      if (testFailed != 0) { fails++; }
      free(state);
   }

   for (i = 0; i < 10; i++){
      state = fuzzGameState(state);
      // setting choice1 explicitly
      choice1 = floor(Random() * 2);
      currentPlayer = state->whoseTurn;
      nextPlayer = (currentPlayer + 1) % state->numPlayers;
      state->handCount[currentPlayer] = -1;
      state->hand[currentPlayer][0] = -1;
      state->supplyCount[estate] = 1;
      testFailed = checkBaron(choice1, currentPlayer, nextPlayer, state);

      if (testFailed != 0) { fails++; }
      free(state);
   }


   printf("test failed %d%%\n", fails * 100 / TESTVOLUME);


   return 0;
}

int checkBaron(int choice1, int currentPlayer, int nextPlayer, struct gameState *state){
   char *msg;
   if (RTDEBUG == 1){
      msg = "players: %d, currentplayer: %d, nextplayer: %d\n";
      printf(msg, state->numPlayers, currentPlayer, nextPlayer);
   }

   struct gameState pre;
   memcpy(&pre, state, sizeof(struct gameState));

   int i, r, check;
   r = _baron(choice1, currentPlayer, nextPlayer, state);

   if (r != 0){
      printf("_baron returned %d\n", r);
   }

   pre.numBuys++;

   if (choice1 == 0){
      // player chose not to reveal an estate
      if (pre.supplyCount[estate] > 0){
         pre.supplyCount[estate]--;
         pre.discardCount[currentPlayer]++;
         pre.discard[currentPlayer][pre.discardCount[currentPlayer] - 1] = estate;
      }
   }
   else {
      int estateFound = 0;
      for (i = 0; i < pre.handCount[currentPlayer]; i++){
         if (pre.hand[currentPlayer][i] == estate){
            pre.discardCount[currentPlayer]++;
            pre.discard[currentPlayer][pre.discardCount[currentPlayer] - 1] = estate;
            pre.coins += 4;
            estateFound = 1;
            break;
         }
      }
      if (estateFound == 0){
         if (pre.supplyCount[estate] > 0){
            pre.supplyCount[estate]--;
            pre.discardCount[currentPlayer]++;
            pre.discard[currentPlayer][pre.discardCount[currentPlayer] - 1] = estate;
         }
      }
   }

   check = memcmp(&pre, state, sizeof(struct gameState));

   if (RTDEBUG !=0){
      if (check != 0){
         msg = "test %d failed with choice1: %d, currentPlayer: %d, nextPlayer %d\n";
         printf(msg, i, choice1, currentPlayer, nextPlayer);
      }
   }
   return check;
}

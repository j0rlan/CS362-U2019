/********************************************************************************************
  Jordan Bleck
  bleckw@oregonstate.edu
  2019.07.24
  CS 362 Software Engineering II
  Assignment 4: Random Testing

card: minion
_minion(int choice2, int choice1, int handPos, int currentPlayer, struct gameState *state)
 ******************************************************************************************/
#include "gameStateFuzz.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

int checkMinion(int choice2, int choice1, int handPos, int currentPlayer, struct gameState *state);

int main(int argc, char* argv[]){

   SelectStream(2);
   PutSeed(time(NULL));

   struct gameState *state = NULL;
   int choice1, currentPlayer, i, testFailed, handPos, choice2;
   int fails = 0;


   for (i = 0; i < TESTVOLUME; i++){
      int j = -1;
      state = fuzzGameState(state);
      choice1 = floor(Random() * 2);
      choice2 = 0;
      if (choice1 == 0) { choice2 = 1; }


      state->numPlayers = floor(Random() * (MAX_PLAYERS - 1)) + 2; // 2 to MAX_PLAYERS
      state->whoseTurn = floor(Random() * state->numPlayers);
      currentPlayer = state->whoseTurn;
      // discardCard segfaulted on referencing playedcards - thanks gbd
      state->playedCardCount = floor(Random() * MAX_DECK) - 1;
      for (j = 0; j < state->numPlayers; j++){
         state->deckCount[j] = floor(Random() * MAX_DECK);
         state->discardCount[j] = floor(Random() * MAX_DECK);
         state->handCount[j] = floor(Random() * MAX_HAND);
      }
      handPos = floor(Random() * MAX_HAND);
      testFailed = checkMinion(choice2, choice1, handPos, currentPlayer, state);
      free(state);

      if (testFailed != 0) { fails++; }
   }



   printf("test failed %d%%\n", fails * 100 / TESTVOLUME);


   return 0;
}

int checkMinion(int choice2, int choice1, int handPos, int currentPlayer, struct gameState *state){
   char *msg;
   if (RTDEBUG == 1){
      msg = "players: %d, currentplayer: %d\n";
      printf(msg, state->numPlayers, currentPlayer);
   }

   struct gameState pre;
   memcpy(&pre, state, sizeof(struct gameState));

   int i, r, check;
   r = minionEffect(choice2, choice1, handPos, currentPlayer, state);

   if (r != 0){
      printf("_minion returned %d\n", r);
   }

   // setting expected results into pre

   pre.numActions++;

   if (choice1 == 1){
      pre.coins += 2;
   }

   if (choice2 == 1){
      // discard hand
      while (pre.handCount[currentPlayer] > 0){
         pre.discardCount[currentPlayer]++;
         pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = pre.hand[currentPlayer][pre.handCount[currentPlayer] - 1];
         pre.handCount[currentPlayer]--;
         pre.hand[currentPlayer][pre.handCount[currentPlayer]] = -1;
      }

      pre.handCount[currentPlayer] = 0;
      if (pre.deckCount[currentPlayer] >= 4){
         //draw 4 cards
      }
      else {
         //draw deckCount cards

         //then draw up to 4 if available
      }
      int j;
      // do the same for all players with > 5 cards in hand
      for (j = 0; j < pre.numPlayers; j++){

         if (pre.handCount[j] < 5) { continue; }

         while (pre.handCount[j] > 0){
            pre.discardCount[j]++;
            pre.discard[j][pre.discardCount[j]] = pre.hand[j][pre.handCount[j] - 1];
            pre.handCount[j]--;
            pre.hand[j][pre.handCount[j]] = -1;
         }

         pre.handCount[j] = 0;
         if (pre.deckCount[j] >= 4){
            //draw 4 cards
         }
         else {
            //draw deckCount cards

            //then draw up to 4 if available
         }
      }
   }

   check = memcmp(&pre, state, sizeof(struct gameState));

   if (RTDEBUG !=0){
      if (check != 0){
         msg = "test %d failed with choice1: %d";
         printf(msg, i, choice1);
      }
   }
   return check;
}

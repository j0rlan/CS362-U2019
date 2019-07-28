CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

########

unittestresults: dominion.o unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c
	gcc -o unittest1 unittest1.c -g  dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 unittest2.c -g  dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 unittest3.c -g  dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 unittest4.c -g  dominion.o rngs.o $(CFLAGS)
	gcc -o unittest5 unittest5.c -g  dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 cardtest1.c -g  dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 cardtest2.c -g  dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 cardtest3.c -g  dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 cardtest4.c -g  dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest5 cardtest5.c -g  dominion.o rngs.o $(CFLAGS)
	unittest1 > unittestresults.out
	unittest2 >> unittestresults.out
	unittest3 >> unittestresults.out
	unittest4 >> unittestresults.out
	unittest5 >> unittestresults.out
	cardtest1 >> unittestresults.out
	cardtest2 >> unittestresults.out
	cardtest3 >> unittestresults.out
	cardtest4 >> unittestresults.out
	cardtest5 >> unittestresults.out
	echo "" >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov | grep "function _baron" >> unittestresults.out
	cat dominion.c.gcov | grep "function _minion" >> unittestresults.out
	cat dominion.c.gcov | grep "function _ambassador" >> unittestresults.out
	cat dominion.c.gcov | grep "function _tribute" >> unittestresults.out
	cat dominion.c.gcov | grep "function _mine" >> unittestresults.out
	cat dominion.c.gcov | grep "function initializeGame" >> unittestresults.out
	cat dominion.c.gcov | grep "function shuffle" >> unittestresults.out
	cat dominion.c.gcov | grep "function endTurn" >> unittestresults.out
	cat dominion.c.gcov | grep "function getWinners" >> unittestresults.out
	cat dominion.c.gcov | grep "function drawCard" >> unittestresults.out

#######

randomtestresults: dominion.o randomtestcard1.c randomtestcard2.c randomtestcard3.c
	gcc -o randomtestcard1 randomtestcard1.c -g gameStateFuzz.h dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestcard2 randomtestcard2.c -g gameStateFuzz.h dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestcard3 randomtestcard3.c -g gameStateFuzz.h dominion.o rngs.o $(CFLAGS)
	randomtestcard1 > randomtestresults.out
	randomtestcard2 >> randomtestresults.out
	randomtestcard3 >> randomtestresults.out
	echo "" >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	cat dominion.c.gcov | grep "function _baron" >> randomtestresults.out
	cat dominion.c.gcov | grep "function _minion" >> randomtestresults.out
	cat dominion.c.gcov | grep "function _tribute" >> randomtestresults.out


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1 unittest2 unittest3 unittest4 unittest5
	rm -f cardtest1 cardtest2 cardtest3 cardtest4 cardtest5
	rm -f randomtestcard1 randomtestcard2 randomtestcard3

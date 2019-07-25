CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)
	./testme > result.out

gcov: testme
	gcov ./testme.c -b >> result.out

clean:
	rm *.out *.gcno *.gcda *.gcov testme

CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c -g -lgcov $(CFLAGS)
	./testme > result.out
	echo "" >> result.out
	gcov testme.c -b >> result.out

clean:
	rm *.out *.gcno *.gcda *.gcov testme

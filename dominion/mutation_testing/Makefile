CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c dominion_helpers.h rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

all: testdominion.o

clean:
	rm -f testdominion *.out *.o *.gcov *.gcda *.gcno *.so *.a *.dSYM
	
myassert.o: myassert.h myassert.c
	gcc -c myassert.c -g $(CFLAGS)
	
testdominion.o: myassert.o interface.o dominion.o testdominion.c 
	gcc -o testdominion testdominion.c -g dominion.o rngs.o myassert.o interface.o $(CFLAGS)
	
randomtestadventurer: myassert.o interface.o randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o myassert.o interface.o $(CFLAGS)
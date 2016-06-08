CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c dominion_helpers.h rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

all: testdominion.o unittest1.o unittest2.o unittest3.o unittest4.o cardtest1.o cardtest2.o cardtest3.o cardtest4.o randomtestadventurer randomtestcard1 randomtestcard2

clean:
	rm -f *.o randomcardtest1 randomcardtest2 randomtestadventurer testdominion unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *.gcov *.gcda *.gcno *.so *.a *.dSYM
	
myassert.o: myassert.h myassert.c
	gcc -c myassert.c -g $(CFLAGS)
	
testdominion.o: myassert.o interface.o dominion.o testdominion.c 
	gcc -o testdominion testdominion.c -g dominion.o rngs.o myassert.o interface.o $(CFLAGS)

unittest1.o: myassert.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o myassert.o $(CFLAGS)
	
unittest2.o: myassert.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o myassert.o $(CFLAGS)
	
unittest3.o: myassert.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o myassert.o $(CFLAGS)
	
unittest4.o: myassert.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o myassert.o $(CFLAGS)
	
cardtest1.o: myassert.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o myassert.o $(CFLAGS)
	
cardtest2.o: myassert.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o myassert.o $(CFLAGS)
	
cardtest3.o: myassert.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o myassert.o $(CFLAGS)
	
cardtest4.o: myassert.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o myassert.o $(CFLAGS)
	
randomtestadventurer: myassert.o interface.o randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o myassert.o interface.o $(CFLAGS)

randomtestcard1: myassert.o interface.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o myassert.o interface.o $(CFLAGS)

randomtestcard2: myassert.o interface.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o myassert.o interface.o $(CFLAGS)
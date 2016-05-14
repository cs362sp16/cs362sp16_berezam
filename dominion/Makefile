CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM
	
myassert.o: playdom.o myassert.h myassert.c
	gcc -c myassert.c -g $(CFLAGS)
	
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
	
randomtestcard1.out: randomtestcard1 playdom
	./randomtestcard1 42 > randomtestcard1.out
	echo "GCOV AFTER TEST SUITE" >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	
randomtestcard2.out: randomtestcard2 playdom
	./randomtestcard2 42 > randomtestcard2.out
	echo "GCOV AFTER TEST SUITE" >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	
randomtestadventurer.out: randomtestadventurer playdom
	./randomtestadventurer 42 > randomtestadventurer.out
	echo "GCOV AFTER TEST SUITE" >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
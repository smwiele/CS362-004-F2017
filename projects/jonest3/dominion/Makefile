CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

getCard.o: getCard.h getCard.c
	gcc -c getCard.c -g $(CLAGS)

#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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

all: playdom player testDrawCard testBuyCard badTestDrawCard getCard.o dominion.o tests randomtestcard1.out randomttestcard2.out randomtestadventurer.out

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe badTestDrawCard tests

# Random Tests
randomtestcard1: randomtestcard1.c dominion.o rngs.o getCard.o interface.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o getCard.o interface.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o getCard.o interface.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o getCard.o interface.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o getCard.o interface.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o getCard.o interface.o $(CFLAGS)

tests: randomtestcard1 randomtestcard2 randomtestadventurer

randomtestcard1.out: clean randomtestcard1
	./randomtestcard1 &> randomtestcard1.out
	gcov randomtestcard1.c -b >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: clean randomtestcard2
	./randomtestcard2 &> randomtestcard2.out
	gcov randomtestcard2.c -b >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: clean randomtestadventurer
	./randomtestadventurer &> randomtestadventurer.out
	gcov randomtestadventurer.c -b >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out   

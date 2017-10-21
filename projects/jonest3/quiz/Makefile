CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

clean: 
	rm -f *.o testme testme.exe *.gcov *.gcno *.gcda

all: testme


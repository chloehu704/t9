# CSE374 HW5 Makefile for the t9 predictive text

all: t9
t9: tnine.o trie.o
	gcc tnine.o trie.o -o t9

trie.o: trie.c trienode.h
	gcc -Wall -std=c11 -c trie.c

t9.o: tnine.c trienode.h
	gcc -Wall -g -std=c11 -c tnine.c

# remove built files and backups
clean:
	rm -f *.o t9 *~

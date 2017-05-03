CFLAGS = -ggdb3 -std=c++11 -O0 -Wall -Werror
CC = g++

EXE = atari
SRCS = atari.cpp reada26.cpp instructions.cpp
HEAD = reada26.h instructions.h
GAME=$(wildcard *.nes)

atari:
	rm -rf core $(EXE) *.o *.d *.dSYM
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS)

blackjack:
	rm -rf core $(EXE) *.o *.d *.dSYM
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS)
	./atari blackjack.a26

pacman:
	rm -rf core $(EXE) *.o *.d *.dSYM
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS)
	./atari pacman.bin

all: blackjack pacman

clean:
	rm -rf core $(EXE) *.o *.d *.dSYM

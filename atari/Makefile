CFLAGS = -ggdb3 -std=c++11 -O0 -Wall -Werror
CC = g++

EXE = atari
SRCS = atari.cpp reada26.cpp instructions.cpp
HEAD = reada26.h instructions.h
GAME=$(wildcard *.nes)

blackjack:
	rm -rf core $(EXE) *.o *.d *.dSYM
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS)
	./atari blackjack.a26

all: blackjack

clean:
	rm -rf core $(EXE) *.o *.d *.dSYM

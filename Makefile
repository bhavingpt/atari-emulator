CFLAGS = -ggdb3 -std=c++11 -O0 -Wall -Werror `/Users/Bhavin/Desktop/SDL2-2.0.5/sdl2-config --cflags --libs`
CC = g++

EXE = atari
SRCS = atari.cpp reada26.cpp instructions.cpp tia.cpp
HEAD = reada26.h instructions.h tia.h
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

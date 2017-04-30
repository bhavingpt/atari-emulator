CFLAGS = -ggdb3 -std=c++11 -O0 -Wall -Werror
CC = g++

EXE = nes
SRCS = nes.cpp hashmap.cpp readnes.cpp instructions.cpp
HEAD = hashmap.h readnes.h instructions.h
GAME=$(wildcard *.nes)

mario:
	rm -rf core $(EXE) *.o *.d *.dSYM
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS)
	./nes mario.nes

$(GAME):
	rm -rf core $(EXE) *.o *.d *.dSYM
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS)
	./nes $(GAME).nes

clean:
	rm -rf core $(EXE) *.o *.d *.dSYM

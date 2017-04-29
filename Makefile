CFLAGS = -ggdb3 -O0 -Wall -Werror
CC = g++

EXE = nes
SRCS = nes.cpp hashmap.cpp readnes.cpp
HEAD = hashmap.h readnes.h

mario:
	rm -rf core $(EXE) *.o *.d *.dSYM
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS)
	./nes mario.nes

clean:
	rm -rf core $(EXE) *.o *.d *.dSYM

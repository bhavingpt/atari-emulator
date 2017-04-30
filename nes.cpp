#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <math.h>
#include <string.h>
#include "hashmap.h"
#include "readnes.h"

uint16_t pc;
uint8_t a, x, y, sp, p;
char running = 1;

class Instruction {
  public:
    int length;
    void execute(unsigned char one, unsigned char two) {}
};

Instruction inst;
std::unordered_map<unsigned char, Instruction> table;

void next_instruction() {
    try {
        inst = table.at(prg[pc]);
        inst.execute(prg[pc + 1], prg[pc + 2]);
        pc += inst.length;
    } catch (const std::out_of_range& oor) {
        printf("didn't recognize opcode %02x, exiting\n", prg[pc]);
        running = 0;
    }
}

int main(int argc, char** argv) {
    init();
    setup(argv[1]);

    while (running) {
        next_instruction();
    }
}


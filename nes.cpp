#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <math.h>
#include <string.h>
#include "hashmap.h"
#include "readnes.h"
#include "instructions.h"

uint16_t pc;
uint8_t a, x, y, sp, p;
char running = 1;

void next_instruction() {
    try {
        table.at(prg[pc])->execute(prg[pc+1], prg[pc+2]);
        pc += 1;
    } catch (const std::out_of_range& oor) {
        printf("didn't recognize opcode %02x, exiting\n", prg[pc]);
        running = 0;
    }
}

int main(int argc, char** argv) {
    init();
    setup(argv[1]);
    initialize_instructions();

    while (running) {
        next_instruction();
    }
}


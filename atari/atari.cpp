#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "hashmap.h"
#include "readrom.h"
#include "instructions.h"

uint16_t pc;
uint8_t a, x, y, sp, p;
char running = 1;

void next_instruction() {
    try {
        table.at(prg[pc])->execute(prg[pc+1], prg[pc+2]);
        pc += table.at(prg[pc])->length();
    } catch (const std::out_of_range& oor) {
        printf("UNKNOWN OPCODE %02x\n", prg[pc]);
        running = 0;
    }
}

int main(int argc, char** argv) {
    initialize_instructions();
    setup(argv[1]);

    while (running) {
        next_instruction();
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "reada26.h"
#include "instructions.h"

uint16_t pc = 0x1000;
uint8_t a, x, y, sp, p;
char running = 1;

void next_instruction() {
    try {
        table.at(mem[pc])->execute(mem[pc+1], mem[pc+2]);
        pc += table.at(mem[pc])->length();
    } catch (const std::out_of_range& oor) {
        printf("UNKNOWN OPCODE %02x\n", mem[pc]);
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

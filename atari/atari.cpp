#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "reada26.h"
#include "instructions.h"
#include "tia.h"
#include "SDL.h"

uint16_t pc = 0x1000;
uint8_t a, x, y, p;
uint8_t sp = 0xFF;
int junk_cycles = 0;

void compute_cycle() {
    if (junk_cycles == 0) {
        try {
            int inst_length = table.at(mem(pc))->length();
            table.at(mem(pc))->execute(mem(pc+1), mem(pc+2));
            pc += inst_length;
            junk_cycles = table.at(mem(pc))->
                cycles(mem(pc+1), mem(pc+2)) - 1;
        } catch (const std::out_of_range& oor) {
            printf("\n%x: UNKNOWN OPCODE %02x\n\n", pc - 0x1000, mem(pc));
            exit(1);
        }
    } else {
        junk_cycles--;
    }
}

extern "C" int main(int argc, char** argv) {
    initialize_instructions();
    setup(argv[1]);

    init_graphics();
    return 0;
}

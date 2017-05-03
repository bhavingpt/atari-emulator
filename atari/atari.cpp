#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "reada26.h"
#include "instructions.h"
#include "SDL.h"

uint16_t pc = 0x1000;
uint8_t a, x, y, p;
uint8_t sp = 0xFF;
unsigned long long running = 1;

void next_instruction() {
    try {
        int inst_length = table.at(mem(pc))->length();
        table.at(mem(pc))->execute(mem(pc+1), mem(pc+2));
        pc += inst_length;
    } catch (const std::out_of_range& oor) {
        printf("\n%x: UNKNOWN OPCODE %02x\n\n", pc - 0x1000, mem(pc));
        exit(1);
    }
}

extern "C" int main(int argc, char** argv) { // cite stack overflow: see report
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Quit SDL
    SDL_Quit();

    initialize_instructions();
    setup(argv[1]);

    while (running) {
        next_instruction();
    }

    return 0;
}

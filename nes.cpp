#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <math.h>
#include <string.h>
#include "hashmap.h"
#include "readnes.h"

uint16_t pc;
uint8_t a, x, y, sp, p;
std::unordered_map<unsigned char, Instruction> table;

class Instruction {

}


int get_inst_len(unsigned char opcode) {

}

void get_next_instruction() {
    int currlen = get_inst_len(prg[pc]);

    for (int i=0;i < currlen; i++) {
        printf("%02x ", prg[pc + i]);
    }

    printf("\n");
    pc += currlen;
}

int main(int argc, char** argv) {
    init();
    setup(argv[1]);

    while (pc < 50 /*exe[4] * 16384*/) {
        get_next_instruction();
    }
}


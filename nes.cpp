#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <math.h>
#include <string.h>
#include "hashmap.h"
#include "readnes.h"

uint16_t pc;
uint8_t a, x, y, sp, p;
std::unordered_map<unsigned char, int> lengths;

void init_lengths();

void print_all_instructions() {
    while (pc < exe[4] * 16384) {
        int currlen;
        try {
            currlen = lengths.at(prg[pc]);
        } catch (const std::out_of_range& oor) {
            currlen = 1;
        }
        for (int i=0;i < currlen; i++) {
            printf("%02x ", prg[pc + i]);
        }
        printf("\n");
        pc += currlen;
    }
}

int main(int argc, char** argv) {
    init();
    setup(argv[1]);

    print_all_instructions();
}


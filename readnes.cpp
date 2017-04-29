#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hashmap.h"
#include "readnes.h"

unsigned char *temp, *exe, *prg, *chr;
int prg_pages;
int chr_pages;
int size;

void unhex(unsigned char one, unsigned char two, int pos) {
    int val_one = (one <= '9') ? one - '0' : one + 10 - 'a';
    int val_two = (two <= '9') ? two - '0' : two + 10 - 'a';
    exe[pos] = 16*val_one + val_two;
}

void read_nes_header() {
    int i = 0;
    int exe_pos = 0;
    while (i < size) {
        if (temp[i] != '\n' && temp[i] != ' ') {
            unhex(temp[i], temp[i+1], exe_pos);
            i++;
            exe_pos++;
        }
        i++;
    }
}

void load_into_memory() {
    prg = (unsigned char *) malloc(16384 * exe[4]);
    chr = (unsigned char *) malloc(8192 * exe[5]);

    for (int loc = 0; loc < exe[4] * 16384; loc++) {
        prg[loc] = exe[loc + 16];
    }
    for (int loc = 0; loc < exe[5] * 8192; loc++) {
        chr[loc] = exe[loc + 16 + prg_pages * 16384];
    }
}

uint16_t setup(char* filename) {
    FILE* fp = fopen(filename, "rb"); // file opening taken from my pc
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET); // rewind the file

    exe = (unsigned char *) malloc(size * sizeof(char));
    temp = (unsigned char *) malloc(size * sizeof(char));

    fread(temp, 1, size, fp); // read the file into temp
    fclose(fp);

    read_nes_header(); // the file is now in exe!
    load_into_memory();

    return 0; // TODO return the pc to start at!
}

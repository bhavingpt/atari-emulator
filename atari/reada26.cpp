#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "reada26.h"

unsigned char *exe, *memory;
int size;

void load_into_memory() {
    memory = (unsigned char *) malloc(8192 * sizeof(char));

    for (int i = 0; i < size; i++) {
        memory[i + 4096] = exe[i];
        if (size == 2048) memory[i + 6144] = exe[i];
    }
}

void setup(char* filename) {
    FILE* fp = fopen(filename, "rb"); // file opening taken from my pc
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET); // rewind the file

    exe = (unsigned char *) malloc(size * sizeof(char));

    fread(exe, 1, size, fp); // read the file into temp
    fclose(fp);

    load_into_memory();
}

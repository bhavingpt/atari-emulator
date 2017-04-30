#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hashmap.h"
#include "readnes.h"

unsigned char *mem, *exe;
int size;

void setup(char* filename) {
    FILE* fp = fopen(filename, "rb"); // file opening taken from my pc
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET); // rewind the file

    exe = (unsigned char *) malloc(size * sizeof(char));

    fread(mem, 1, size, fp); // read the file into temp
    fclose(fp);
}

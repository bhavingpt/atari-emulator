#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hashmap.h"
#include "readnes.h"

uint16_t pc;

void execute_instructions();

int main(int argc, char** argv) {
    init();
    pc = setup(argv[1]);
}

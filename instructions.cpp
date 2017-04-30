#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "instructions.h"
using namespace std;

unordered_map<unsigned char, Instruction*> table;

class CLD : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("Executing CLD...\n");
    }
};

void initialize_instructions() {
    table.insert(pair<unsigned char, Instruction*>('\xd8', new CLD()));
}

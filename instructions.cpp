#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "instructions.h"
#include "hashmap.h"
using namespace std;

unordered_map<unsigned char, Instruction*> table;

class _D8 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        p &= 0xF7;
    }
};

class _78 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        p &= 0xFB;
    }
};

class _AD : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish AD...\n");
    }
};

class _10 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish 10...\n");
    }
};

class _A2 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish A2...\n");
    }
};

class _8E : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish 8E...\n");
    }
};

class _CA : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish CA...\n");
    }
};

class _9A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish 9A...\n");
    }
};

class _A6 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish A6...\n");
    }
};

class _A0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish A0...\n");
    }
};

class _84 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish 84...\n");
    }
};

class _A9 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish A9...\n");
    }
};

class _91 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO finish 91...\n");
    }
};

void initialize_instructions() {
    init(); // start memory
    table.insert(pair<unsigned char, Instruction*>('\xd8', new _D8()));
    table.insert(pair<unsigned char, Instruction*>('\x78', new _78()));
    table.insert(pair<unsigned char, Instruction*>('\xad', new _AD()));
    table.insert(pair<unsigned char, Instruction*>('\x10', new _10()));
    table.insert(pair<unsigned char, Instruction*>('\xa2', new _A2()));
    table.insert(pair<unsigned char, Instruction*>('\x8e', new _8E()));
    table.insert(pair<unsigned char, Instruction*>('\xca', new _CA()));
    table.insert(pair<unsigned char, Instruction*>('\x9a', new _9A()));
    table.insert(pair<unsigned char, Instruction*>('\xa6', new _A6()));
    table.insert(pair<unsigned char, Instruction*>('\xa0', new _A0()));
    table.insert(pair<unsigned char, Instruction*>('\x84', new _84()));
    table.insert(pair<unsigned char, Instruction*>('\xa9', new _A9()));
    table.insert(pair<unsigned char, Instruction*>('\x91', new _91()));
}

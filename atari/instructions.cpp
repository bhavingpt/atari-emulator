#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "instructions.h"
#include "reada26.h"
using namespace std;

unordered_map<unsigned char, Instruction*> table;

void set(int idx) {
    p |= (1 << idx);
}

void clr(int idx) {
    p &= ~(1 << idx);
}

class _78 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        set(2);
    }
};

class _D8 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        set(3);
    }
};

class _A2 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        x = one;
        (x == 0) ? set(1) : clr(1);
        (x >> 7) ? set(7) : clr(7);
    }
};

class _9A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        sp = x;
    }
};

class _E8 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO E8: increment x by one\n");
        (x == 0) ? set(1) : clr(1);
        (x >> 7) ? set(7) : clr(7);
    }
};

class _8A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        a = x;
        (x == 0) ? set(1) : clr(1);
        (x >> 7) ? set(7) : clr(7);
    }
};

class _95 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 95: store X's value\n");
    }
};

class _D0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO D0: cond jump w signed offset\n");
    }
};

class _86 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 86: store X's value\n");
    }
};

class _BD : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO BD: load with signed offset\n");
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _A0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        y = one;
        (y == 0) ? set(1) : clr(1);
        (y >> 7) ? set(7) : clr(7);
    }
};

class _94 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 94: store Y's value\n");
    }
};

class _C8 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO C8: increment y by one\n");
        (y == 0) ? set(1) : clr(1);
        (y >> 7) ? set(7) : clr(7);
    }
};

class _CA : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO CA: decrement x by one\n");
        (x == 0) ? set(1) : clr(1);
        (x >> 7) ? set(7) : clr(7);
    }
};

class _10 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 10: cond jump w signed offset\n");
    }
};

class _84 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 10: store Y's value\n");
    }
};

class _20 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 20: stack and subroutine call\n");
    }
};

class _A9 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        a = one;
        (y == 0) ? set(1) : clr(1);
        (y >> 7) ? set(7) : clr(7);
    }
};

class _85 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 85: store A's value\n");
    }
};

class _8E : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 8E: store X's value\n");
    }
};

class _E6 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO E6: increment memory, set flags\n");
    }
};

class _A5 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        a = mem[one];
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _C6 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO C6: decrement memory, set flags\n");
    }
};

class _29 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        a &= one;
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _AD : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        a = mem[one + (two << 8)];
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _A8 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        y = a;
        (y == 0) ? set(1) : clr(1);
        (y >> 7) ? set(7) : clr(7);
    }
};

class _45 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        a ^= mem[one];
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _25 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        a &= mem[one];
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _09 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        a |= one;
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _0A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        (a >> 7) ? set(0) : clr(0);
        a = a << 1;
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _26 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 26: shifting memory, set flags\n");
    }
};

class _A6 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        x = mem[one];
        (x == 0) ? set(1) : clr(1);
        (x >> 7) ? set(7) : clr(7);
    }
};

void initialize_instructions() {
    printf("\n");
    table.insert(pair<unsigned char, Instruction*>('\x78', new _78()));
    table.insert(pair<unsigned char, Instruction*>('\xd8', new _D8()));
    table.insert(pair<unsigned char, Instruction*>('\xa2', new _A2()));
    table.insert(pair<unsigned char, Instruction*>('\x9a', new _9A()));
    table.insert(pair<unsigned char, Instruction*>('\xe8', new _E8()));
    table.insert(pair<unsigned char, Instruction*>('\x8a', new _8A()));
    table.insert(pair<unsigned char, Instruction*>('\x95', new _95()));
    table.insert(pair<unsigned char, Instruction*>('\xd0', new _D0()));
    table.insert(pair<unsigned char, Instruction*>('\x86', new _86()));
    table.insert(pair<unsigned char, Instruction*>('\xbd', new _BD()));
    table.insert(pair<unsigned char, Instruction*>('\xa0', new _A0()));
    table.insert(pair<unsigned char, Instruction*>('\x94', new _94()));
    table.insert(pair<unsigned char, Instruction*>('\xc8', new _C8()));
    table.insert(pair<unsigned char, Instruction*>('\xca', new _CA()));
    table.insert(pair<unsigned char, Instruction*>('\x10', new _10()));
    table.insert(pair<unsigned char, Instruction*>('\x84', new _84()));
    table.insert(pair<unsigned char, Instruction*>('\x20', new _20()));
    table.insert(pair<unsigned char, Instruction*>('\xa9', new _A9()));
    table.insert(pair<unsigned char, Instruction*>('\x85', new _85()));
    table.insert(pair<unsigned char, Instruction*>('\x8e', new _8E()));
    table.insert(pair<unsigned char, Instruction*>('\xe6', new _E6()));
    table.insert(pair<unsigned char, Instruction*>('\xa5', new _A5()));
    table.insert(pair<unsigned char, Instruction*>('\xc6', new _C6()));
    table.insert(pair<unsigned char, Instruction*>('\x29', new _29()));
    table.insert(pair<unsigned char, Instruction*>('\xad', new _AD()));
    table.insert(pair<unsigned char, Instruction*>('\xa8', new _A8()));
    table.insert(pair<unsigned char, Instruction*>('\x45', new _45()));
    table.insert(pair<unsigned char, Instruction*>('\x25', new _25()));
    table.insert(pair<unsigned char, Instruction*>('\x09', new _09()));
    table.insert(pair<unsigned char, Instruction*>('\x0a', new _0A()));
    table.insert(pair<unsigned char, Instruction*>('\x26', new _26()));
    table.insert(pair<unsigned char, Instruction*>('\xa6', new _A6()));
}

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

class _F0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO F0: cond jump w signed offset\n");
    }
};

class _18 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        clr(0);
    }
};

class _69 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 69: this one is hard\n");
    }
};

class _49 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        a ^= one;
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _AA : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        x = a;
        (x == 0) ? set(1) : clr(1);
        (x >> 7) ? set(7) : clr(7);
    }
};

class _05 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        a |= mem[one];
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _C9 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        (a < one) ? clr(0) : set(0);
        (a == one) ? set(1) : clr(1);
        (a < one) ? set(7) : clr(7);
    }
};

class _B0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO B0: cond jump w signed offset\n");
    }
};

class _B5 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO B5: load x w signed offset\n");
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _39 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 39: and w signed mem offset\n");
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _55 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 55: eor w signed mem offset\n");
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _88 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 88: decrement y by one\n");
        (y == 0) ? set(1) : clr(1);
        (y >> 7) ? set(7) : clr(7);
    }
};

class _4A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        (a & 0x1) ? set(0) : clr(0);
        a = a >> 1;
        a &= 0x7F;
        (a == 0) ? set(1) : clr(1);
        clr(7);
    }
};

class _59 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 59: eor w signed mem offset\n");
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _4C : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 4C: don't actually do jumps, seq\n");
    }
};

class _65 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 65: perform add w carry, flags\n");
    }
};

class _6A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        (a & 0x1) ? set(0) : clr(0);
        a = a >> 1;
        (p & 0x1) ? (a |= 0x80) : (a &= 0x7F);
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _99 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 99: store at signed offset\n");
    }
};

class _C0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        (y < one) ? clr(0) : set(0);
        (y == one) ? set(1) : clr(1);
        (y < one) ? set(7) : clr(7);
    }
};

class _B1 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO B1: complicated indexing w signed\n");
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _11 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 11: complicated or idx w signed\n");
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _48 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 48: push accumulator: write to mem\n");
    }
};

class _90 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 90: conditional jump instruction\n");
    }
};

class _68 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 68: pull accumulator from the stack\n");
    }
};

class _60 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 60: return from subroutine\n");
    }
};

class _51 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO 51: complicated eor indexing\n");
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _B9 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        printf("TODO B9: load signed offset\n");
        (a == 0) ? set(1) : clr(1);
        (a >> 7) ? set(7) : clr(7);
    }
};

class _C4 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        (y < mem[one]) ? clr(0) : set(0);
        (y == mem[one]) ? set(1) : clr(1);
        (y < mem[one]) ? set(7) : clr(7);
    }
};

class _F8 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        set(3);
    }
};

void initialize_instructions() {
    printf("\n");
    table.insert(pair<unsigned char, Instruction*>('\xf8', new _F8()));
    table.insert(pair<unsigned char, Instruction*>('\xc4', new _C4()));
    table.insert(pair<unsigned char, Instruction*>('\xb9', new _B9()));
    table.insert(pair<unsigned char, Instruction*>('\x51', new _51()));
    table.insert(pair<unsigned char, Instruction*>('\x60', new _60()));
    table.insert(pair<unsigned char, Instruction*>('\x68', new _68()));
    table.insert(pair<unsigned char, Instruction*>('\x90', new _90()));
    table.insert(pair<unsigned char, Instruction*>('\x48', new _48()));
    table.insert(pair<unsigned char, Instruction*>('\x11', new _11()));
    table.insert(pair<unsigned char, Instruction*>('\xb1', new _B1()));
    table.insert(pair<unsigned char, Instruction*>('\xc0', new _C0()));
    table.insert(pair<unsigned char, Instruction*>('\x99', new _99()));
    table.insert(pair<unsigned char, Instruction*>('\x6a', new _6A()));
    table.insert(pair<unsigned char, Instruction*>('\x65', new _65()));
    table.insert(pair<unsigned char, Instruction*>('\x4c', new _4C()));
    table.insert(pair<unsigned char, Instruction*>('\x59', new _59()));
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
    table.insert(pair<unsigned char, Instruction*>('\xf0', new _F0()));
    table.insert(pair<unsigned char, Instruction*>('\x18', new _18()));
    table.insert(pair<unsigned char, Instruction*>('\x69', new _69()));
    table.insert(pair<unsigned char, Instruction*>('\x49', new _49()));
    table.insert(pair<unsigned char, Instruction*>('\xaa', new _AA()));
    table.insert(pair<unsigned char, Instruction*>('\x05', new _05()));
    table.insert(pair<unsigned char, Instruction*>('\xc9', new _C9()));
    table.insert(pair<unsigned char, Instruction*>('\xb0', new _B0()));
    table.insert(pair<unsigned char, Instruction*>('\xb5', new _B5()));
    table.insert(pair<unsigned char, Instruction*>('\x39', new _39()));
    table.insert(pair<unsigned char, Instruction*>('\x55', new _55()));
    table.insert(pair<unsigned char, Instruction*>('\x88', new _88()));
    table.insert(pair<unsigned char, Instruction*>('\x4a', new _4A()));
}

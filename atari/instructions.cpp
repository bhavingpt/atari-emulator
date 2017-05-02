#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "instructions.h"
#include "reada26.h"
using namespace std;

unordered_map<unsigned char, Instruction*> table;
unsigned char temp;
unsigned char jumps = 1;

// TODO 0) implement decimal adds and subs
// TODO 1) test all instructions and debug result

void set(int idx) {
    p |= (1 << idx);
}

void clr(int idx) {
    p &= ~(1 << idx);
}

void flag(unsigned char value) {
    (value == 0) ? set(1) : clr(1);
    (value >> 7) ? set(7) : clr(7);
}

uint16_t mirror (uint16_t location) {
    location &= 0x1FFF;
    if (!(location >> 11)) { // A12 is 0
        if ((location & 0x80) == 0) { // A7 is 0
            location &= 0x7F;
        } else {
            if ((location & 0x200) == 0x200) { // A9 is 1
                location &= 0x287;
                if ((location & 0x4) == 0x4) { // fourth mirror
                    location &= 0x285;
                }
            } else { // A9 is 0
                location &= 0xFF;
            }
        }
    }
    return location;
}

void write(unsigned char value, uint16_t location) {
    memory[mirror(location)] = value;
}

unsigned char mem(uint16_t location) {
    return memory[mirror(location)];
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
        flag(x = one);
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
        flag(++x);
    }
};

class _8A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        flag(a = x);
    }
};

class _95 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        write(a, (one + x) & 0xFF);
    }
};

class _D0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps && ((p & 0x2) == 0)) {
            pc += (char) one;
        }
    }
};

class _86 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        write(x, one);
    }
};

class _BD : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        flag(a = mem(((one + (two << 8)) + x)));
    }
};

class _A0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(y = one);
    }
};

class _94 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        write(y, (one + x) & 0xFF);
    }
};

class _C8 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        flag(++y);
    }
};

class _CA : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        flag(--x);
    }
};

class _10 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps && ((p & 0x80) == 0)) {
            pc += (char) one;
        }
    }
};

class _84 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        write(y, one);
    }
};

class _20 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps) {
            write(((pc + 2) >> 8) & 0xFF, sp - 1);
            write((pc + 2) & 0xFF, sp - 2);
            sp -= 2;
            pc = (one + (two << 8)) - 3;
        }
    }
};

class _A9 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a = one);
    }
};

class _85 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        write(a, one);
    }
};

class _8E : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        write(x, (one + (two << 8)));
    }
};

class _E6 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        write(mem(one) + 1, one);
        flag(mem(one));
    }
};

class _A5 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a = mem(one));
    }
};

class _C6 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        write(mem(one) - 1, one);
        flag(mem(one));
    }
};

class _29 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a &= one);
    }
};

class _AD : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        flag(a = mem((one + (two << 8))));
    }
};

class _A8 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        flag(y = a);
    }
};

class _45 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a ^= mem(one));
    }
};

class _25 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a &= mem(one));
    }
};

class _09 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a |= one);
    }
};

class _0A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        (a >> 7) ? set(0) : clr(0);
        flag(a = a << 1);
    }
};

class _26 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        temp = mem(one) << 1;
        (mem(one) >> 7) ? set(0) : clr(0);
        if (p & 0x1) temp |= 0x1;
        flag(temp);
        write(temp, one);
    }
};

class _A6 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(x = mem(one));
    }
};

class _F0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps && ((p & 0x2) == 0x2)) {
            pc += (char) one;
        }
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
        if ((p & 0x8) == 0x8) { // binary mode
            uint16_t result = a + (p & 0x1) + one;
            (result == 0) ? set(1) : clr(1); // zero flag
            ((result & 0x100) == 0x100) ? set(0) : clr(0); // carry flag
            ((result & 0x80) == 0x80) ? set(7) : clr(7); // negative flag
            ( ( (a >> 7) && (one >> 7) && ((result & 0x80) == 0x0)  ) || // neg + neg = pos
              ( ((a >> 7) == 0) && ((one >> 7) == 0) && ((result & 0x80) == 0) ) ) ? // pos + pos = neg
                set(6) : clr(6); // overflow flag
            a = result & 0xFF; // set accumulator
        } else {
            printf("you need decimal mode!\n");
            exit(1);
        }
    }
};

class _49 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a ^= one);
    }
};

class _AA : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        flag(x = a);
    }
};

class _05 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a |= mem(one));
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
        if (jumps && (p & 0x1)) {
            pc += (char) one;
        }
    }
};

class _B5 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a = mem((one + x) & 0xFF));
    }
};

class _39 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        flag(a &= mem(((one + (two << 8)) + y)));
    }
};

class _55 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a ^= mem((one + x) & 0xFF));
    }
};

class _88 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        flag(--y);
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
        flag(a ^= mem(((one + (two << 8)) + y)));
    }
};

class _4C : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps) {
            pc = one + (two << 8) - 3;
        }
    }
};

class _65 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        if ((p & 0x8) == 0x8) { // binary mode
            uint16_t result = a + (p & 0x1) + mem(one);
            (result == 0) ? set(1) : clr(1); // zero flag
            ((result & 0x100) == 0x100) ? set(0) : clr(0); // carry flag
            ((result & 0x80) == 0x80) ? set(7) : clr(7); // negative flag
            ( ( (a >> 7) && (mem(one) >> 7) && ((result & 0x80) == 0x0)  ) || // neg + neg = pos
              ( ((a >> 7) == 0) && ((mem(one) >> 7) == 0) && ((result & 0x80) == 0) ) ) ? // pos + pos = neg
                set(6) : clr(6); // overflow flag
            a = result & 0xFF; // set accumulator
        } else {
            printf("you need decimal mode!\n");
            exit(1);
        }
    }
};

class _6A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        (a & 0x1) ? set(0) : clr(0);
        a = a >> 1;
        (p & 0x1) ? (a |= 0x80) : (a &= 0x7F);
        flag(a);
    }
};

class _99 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        write(a, ((one + (two << 8)) + y));
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
        flag(a = mem( (mem(one) + (mem(one + 1) << 8) + y)));
    }
};

class _11 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a |= mem( (mem(one) + (mem(one + 1) << 8) + y)));
    }
};

class _48 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        write(a, sp--);
    }
};

class _90 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps && ((p & 0x1) == 0)) {
            pc += (char) one;
        }
    }
};

class _68 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        a = mem(++sp);
    }
};

class _60 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps) {
            pc = mem(sp + 1) + (mem(sp + 2) << 8);
            sp += 2;
        }
    }
};

class _51 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a ^= mem( (mem(one) + (mem(one + 1) << 8) + y)));
    }
};

class _B9 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        flag(a = mem(((one + (two << 8)) + y)));
    }
};

class _C4 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        (y < mem(one)) ? clr(0) : set(0);
        (y == mem(one)) ? set(1) : clr(1);
        (y < mem(one)) ? set(7) : clr(7);
    }
};

class _F8 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        set(3);
    }
};

class _30 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps && (p >> 7)) {
            pc += (char) one;
        }
    }
};

class _E9 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        temp = ~one;
        if ((p & 0x8) == 0x8) { // binary mode
            uint16_t result = a - ~(p & 0x1) + temp;
            (result == 0) ? set(1) : clr(1); // zero flag
            ( a >= one ) ? set(0) : clr(0); // carry flag
            ((result & 0x80) == 0x80) ? set(7) : clr(7); // negative flag
            ( ( ((a >> 7) == 0) && (temp >> 7) && ((result & 0x80) == 0x0)  ) || // pos - neg = neg
              ( (a >> 7) && ((temp >> 7) == 0) && ((result & 0x80) == 0) ) ) ? // neg - pos = pos
                set(6) : clr(6); // overflow flag
            a = result & 0xFF; // set accumulator
        } else {
            printf("you need decimal mode!\n");
            exit(1);
        }
    }
};

class _3D : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        flag(a &= mem((one + (two << 8) + x)));
    }
};

class _E0 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        (x < one) ? clr(0) : set(0);
        (x == one) ? set(1) : clr(1);
        (x < one) ? set(7) : clr(7);
    }
};

class _06 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        temp = mem(one) << 1;
        (mem(one) >> 7) ? set(0) : clr(0);
        (temp == 0) ? set(1) : clr(1);
        (temp >> 7) ? set(7) : clr(7);
        write(temp, one);
    }
};

class _24 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        ((a & mem(one)) == 0) ? set(1) : clr(1);
        (mem(one) >> 7) ? set(7) : clr(7);
        (mem(one) & 0x40) ? set(6) : clr(6);
    }
};

class _98 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        flag(a = y);
    }
};

class _B4 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(y = mem((one + x) & 0xFF));
    }
};

class _D5 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        (a < ((one + x) & 0xFF)) ? clr(0) : set(0);
        (a == ((one + x) & 0xFF)) ? set(1) : clr(1);
        (a < ((one + x) & 0xFF)) ? set(7) : clr(7);
    }
};

class _A4 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(y = mem(one));
    }
};

class _BE : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        flag(x = mem((one + (two << 8) + y)));
    }
};

class _38 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        set(0);
    }
};

class _F5 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        temp = ~(mem((one + x) & 0xFF));
        if ((p & 0x8) == 0x8) { // binary mode
            uint16_t result = a - ~(p & 0x1) + temp;
            (result == 0) ? set(1) : clr(1); // zero flag
            ( a >= ~temp ) ? set(0) : clr(0); // carry flag
            ((result & 0x80) == 0x80) ? set(7) : clr(7); // negative flag
            ( ( ((a >> 7) == 0) && (temp >> 7) && ((result & 0x80) == 0x0)  ) || // pos - neg = neg
              ( (a >> 7) && ((temp >> 7) == 0) && ((result & 0x80) == 0) ) ) ? // neg - pos = pos
                set(6) : clr(6); // overflow flag
            a = result & 0xFF; // set accumulator
        } else {
            printf("you need decimal mode!\n");
            exit(1);
        }
    }
};

class _00 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps) {
            write(((pc + 2) >> 8) & 0xFF, sp);
            write((pc + 2) & 0xFF, sp - 1);
            write(p | 0x10, sp - 2);
            sp -= 3;

            pc = mem(0x1FFE) + (mem(0x1FFF) << 8) - 1;
        }
    }
};

class _75 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        temp = mem((one + x) & 0xFF);
        if ((p & 0x8) == 0x8) { // binary mode
            uint16_t result = a + (p & 0x1) + temp;
            (result == 0) ? set(1) : clr(1); // zero flag
            ((result & 0x100) == 0x100) ? set(0) : clr(0); // carry flag
            ((result & 0x80) == 0x80) ? set(7) : clr(7); // negative flag
            ( ( (a >> 7) && (temp >> 7) && ((result & 0x80) == 0x0)  ) || // neg + neg = pos
              ( ((a >> 7) == 0) && ((temp >> 7) == 0) && ((result & 0x80) == 0) ) ) ? // pos + pos = neg
                set(6) : clr(6); // overflow flag
            a = result & 0xFF; // set accumulator
        } else {
            printf("you need decimal mode!\n");
            exit(1);
        }
    }
};

class _C5 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        (a < mem(one)) ? clr(0) : set(0);
        (a == mem(one)) ? set(1) : clr(1);
        (a < mem(one)) ? set(7) : clr(7);
    }
};

class _08 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        write(p, sp--);
    }
};

class _28 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        p = mem(++sp);
    }
};

class _19 : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        flag(a |= mem((one + (two << 8) + y)));
    }
};

class _1E : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        temp = mem((one + (two << 8) + x)) << 1;
        (mem((one + (two << 8) + x)) >> 7) ? set(0) : clr(0);
        flag(temp);
        write(temp, (one + (two << 8) + x));
    }
};

class _01 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a |= mem( (mem((one + x) & 0xFF) + (mem((one + x + 1) & 0xFF) << 8))));
    }
};

class _2E : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        temp = mem((one + (two << 8))) << 1;
        (mem((one + (two << 8))) >> 7) ? set(0) : clr(0);
        if (p & 0x1) temp |= 0x1;
        flag(temp);
        write(temp, (one + (two << 8)));
    }
};

class _2C : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        ((a & mem((one + (two << 8)))) == 0) ? set(1) : clr(1);
        (mem((one + (two << 8))) >> 7) ? set(7) : clr(7);
        (mem((one + (two << 8))) & 0x40) ? set(6) : clr(6);
    }
};

class NOP : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {}
};

class _3E : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        uint16_t addr = (one + x + (two << 8));
        temp = mem(addr) << 1;
        (mem(addr) >> 7) ? set(0) : clr(0);
        if (p & 0x1) temp |= 0x1;
        flag(temp);
        write(temp, addr);
    }
};

class _0E : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        temp = mem((one + (two << 8))) << 1;
        (mem((one + (two << 8))) >> 7) ? set(0) : clr(0);
        flag(temp);
        write(temp, (one + (two << 8)));
    }
};

class _2A : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        temp = a << 1;
        (a >> 7) ? set(0) : clr(0);
        if (p & 0x1) temp |= 0x1;
        flag(a = temp);
    }
};

class _40 : public Instruction {
public:
    int length () { return 1; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps) {
            p = mem(sp + 1);
            pc = mem(sp + 2) + (mem(sp + 3) << 8) - 1;
            sp += 3;
        }
    }
};

class _70 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps && ((p & 0x40) == 0x40)) {
            pc += (char) one;
        }
    }
};

class _50 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        if (jumps && ((p & 0x40) == 0)) {
            pc += (char) one;
        }
    }
};

class _15 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        flag(a |= mem((one + x) & 0xFF));
    }
};

class _E4 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        (x < mem(one)) ? clr(0) : set(0);
        (x == mem(one)) ? set(1) : clr(1);
        (x < mem(one)) ? set(7) : clr(7);
    }
};

class _EE : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        write(mem(one + (two << 8)) + 1, (one + (two << 8)));
        flag(mem((one + (two << 8))));
    }
};

class _AE : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        flag(x = mem((one + (two << 8))));
    }
};

class _6D : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        temp = mem(one + (two << 8));
        if ((p & 0x8) == 0x8) { // binary mode
            uint16_t result = a + (p & 0x1) + temp;
            (result == 0) ? set(1) : clr(1); // zero flag
            ((result & 0x100) == 0x100) ? set(0) : clr(0); // carry flag
            ((result & 0x80) == 0x80) ? set(7) : clr(7); // negative flag
            ( ( (a >> 7) && (temp >> 7) && ((result & 0x80) == 0x0)  ) || // neg + neg = pos
              ( ((a >> 7) == 0) && ((temp >> 7) == 0) && ((result & 0x80) == 0) ) ) ? // pos + pos = neg
                set(6) : clr(6); // overflow flag
            a = result & 0xFF; // set accumulator
        } else {
            printf("you need decimal mode!\n");
            exit(1);
        }
    }
};

class _FE : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        unsigned char temp_two = ((one + (two << 8)) + x);
        write(mem(temp_two) + 1, temp_two);
        flag(mem(temp_two));
    }
};

class _8C : public Instruction {
public:
    int length () { return 3; }
    void execute (unsigned char one, unsigned char two) {
        write(y, (one + (two << 8)));
    }
};

class _76 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        uint16_t addr = (one + x) & 0XFF;
        temp = mem(addr) >> 1;
        (mem(addr) & 0x1) ? set(0) : clr(0);
        if (p & 0x1) temp |= 0x80;
        flag(temp);
        write(temp, addr);
    }
};

class _36 : public Instruction {
public:
    int length () { return 2; }
    void execute (unsigned char one, unsigned char two) {
        uint16_t addr = (one + x) & 0XFF;
        temp = mem(addr) << 1;
        (mem(addr) >> 7) ? set(0) : clr(0);
        if (p & 0x1) temp |= 0x1;
        flag(temp);
        write(temp, addr);
    }
};

void initialize_instructions() {
    printf("\n");
    table.insert(pair<unsigned char, Instruction*>('\x36', new _36()));
    table.insert(pair<unsigned char, Instruction*>('\x76', new _76()));
    table.insert(pair<unsigned char, Instruction*>('\x8c', new _8C()));
    table.insert(pair<unsigned char, Instruction*>('\xfe', new _FE()));
    table.insert(pair<unsigned char, Instruction*>('\x6d', new _6D()));
    table.insert(pair<unsigned char, Instruction*>('\xae', new _AE()));
    table.insert(pair<unsigned char, Instruction*>('\xee', new _EE()));
    table.insert(pair<unsigned char, Instruction*>('\xe4', new _E4()));
    table.insert(pair<unsigned char, Instruction*>('\x15', new _15()));
    table.insert(pair<unsigned char, Instruction*>('\x50', new _50()));
    table.insert(pair<unsigned char, Instruction*>('\x70', new _70()));
    table.insert(pair<unsigned char, Instruction*>('\x40', new _40()));
    table.insert(pair<unsigned char, Instruction*>('\x2a', new _2A()));
    table.insert(pair<unsigned char, Instruction*>('\x0e', new _0E()));
    table.insert(pair<unsigned char, Instruction*>('\x3e', new _3E()));
    table.insert(pair<unsigned char, Instruction*>('\x3c', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x80', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\xf4', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\xc7', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\xf7', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x7f', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x3f', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\xff', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x1c', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x1a', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x12', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x14', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x44', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x42', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x72', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x02', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x77', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x07', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x22', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x17', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x03', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x04', new NOP()));
    table.insert(pair<unsigned char, Instruction*>('\x2c', new _2C()));
    table.insert(pair<unsigned char, Instruction*>('\x2e', new _2E()));
    table.insert(pair<unsigned char, Instruction*>('\x01', new _01()));
    table.insert(pair<unsigned char, Instruction*>('\x1e', new _1E()));
    table.insert(pair<unsigned char, Instruction*>('\x19', new _19()));
    table.insert(pair<unsigned char, Instruction*>('\x28', new _28()));
    table.insert(pair<unsigned char, Instruction*>('\x08', new _08()));
    table.insert(pair<unsigned char, Instruction*>('\xc5', new _C5()));
    table.insert(pair<unsigned char, Instruction*>('\x75', new _75()));
    table.insert(pair<unsigned char, Instruction*>('\x00', new _00()));
    table.insert(pair<unsigned char, Instruction*>('\xF5', new _F5()));
    table.insert(pair<unsigned char, Instruction*>('\x38', new _38()));
    table.insert(pair<unsigned char, Instruction*>('\xbe', new _BE()));
    table.insert(pair<unsigned char, Instruction*>('\xa4', new _A4()));
    table.insert(pair<unsigned char, Instruction*>('\xd5', new _D5()));
    table.insert(pair<unsigned char, Instruction*>('\xb4', new _B4()));
    table.insert(pair<unsigned char, Instruction*>('\x98', new _98()));
    table.insert(pair<unsigned char, Instruction*>('\x24', new _24()));
    table.insert(pair<unsigned char, Instruction*>('\x06', new _06()));
    table.insert(pair<unsigned char, Instruction*>('\xe0', new _E0()));
    table.insert(pair<unsigned char, Instruction*>('\x3d', new _3D()));
    table.insert(pair<unsigned char, Instruction*>('\xe9', new _E9()));
    table.insert(pair<unsigned char, Instruction*>('\x30', new _30()));
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

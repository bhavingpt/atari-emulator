#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

class Instruction {
public:
   virtual void execute(unsigned char one, unsigned char two) = 0;
   virtual int length() = 0;
};

extern std::unordered_map<unsigned char, Instruction*> table;
extern uint16_t pc;
extern uint8_t a, x, y, sp, p;

void initialize_instructions();
unsigned char mem(uint16_t location);

#endif

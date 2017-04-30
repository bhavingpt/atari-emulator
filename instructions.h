#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

class Instruction {
public:
   virtual void execute(unsigned char one, unsigned char two) = 0;
   virtual int length() = 0;
};

extern std::unordered_map<unsigned char, Instruction*> table;

void initialize_instructions();

#endif

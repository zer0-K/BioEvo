#pragma once

#include <map>
#include <iostream>

enum instruction { 
    XXX,    // 0    does nothing
    MOV,    // 1    move data into data
    CPY,    // 2    copy data into data
    CPYIN,  // 3    move input into data
    CPYOUT, // 4    move data into output
    INC,    // 5    increment data
    DEC,    // 6    decrement data
    ADD,    // 7    add data
    SUB,    // 8    substract data
    MUL,    // 9    multiply data
    DIV,    // 10   divide data
    CMP,    // 11   compare data
    JMP,    // 12   jump prog 
    JRA,    // 13   jump relative add (curr prog ptr + x)
    JRS,    // 14   jump relative substract (curr prog ptr - x)
    JRE,    // 15   jump relative add if equal to 0
    JE,     // 16   jump if equal to 0
    JL,     // 17   jump if < 0
    JG,     // 18   jump if > 0
    HALT,   // 19   halt
    // ******* instructions EvoX
    GINS,   // 20   gene insertion
    GDEL,   // 21   gene deletion
    GSET,   // 22   set gene value
    GADD,   // 23   add value to gene
    size
};

extern std::map<instruction, std::string> instruction_str;
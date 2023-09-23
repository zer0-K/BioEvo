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
    OPP,    // 11   opposite number
    CPYIS,  // 12   get input size
    SETOS,  // 13   set output size
    CMP,    // 14   compare data
    // ******* jumps
    JMP,    // 15   jump prog 
    JRA,    // 16   jump relative add (curr prog ptr + x)
    JRS,    // 17   jump relative substract (curr prog ptr - x)
    JE,     // 18   jump if equal
    JL,     // 19   jump if <
    JG,     // 20   jump if >
    JLE,    // 21   jump if <=
    JGE,    // 22   jump if >=
    JRE,    // 23   relative jump if equal
    JRL,    // 24   relative jump if <
    JRG,    // 25   relative jump if >
    JRLE,   // 26   relative jump if <=
    JRGE,   // 27   relative jump if >=
    BEG,    // 28   begin/start
    HALT,   // 29   halt
    // ******* random
    RUD,    // 30   random uniform double : between 0 and 1
    RUI,    // 31   random uniform int
    RN,     // 32   random normal : mu=0, sigma=1
    // ******* instructions EvoX
    GR,     // 33   read gene
    GINS,   // 34   gene insertion
    GDEL,   // 35   gene deletion
    GDELW,  // 36   delete 3 genes at once
    GSET,   // 37   set gene value
    GADD,   // 38   add value to gene
    GCPY,   // 39   copy input into genes (insertion)
    MARKER, // 40   genetic marker
    GCPYM,  // 41   copy input into genes at first genetic marker
    size
};

extern std::map<instruction, std::string> instruction_str;
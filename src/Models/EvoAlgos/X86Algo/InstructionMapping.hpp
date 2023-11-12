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
    AIF,    // 14   add input flow
    RIF,    // 15   remove input flow
    AOF,    // 16   add ouput flow
    ROF,    // 17   remove output flow
    CMP,    // 18   compare data
    // ******* jumps
    JMP,    // 19   jump prog 
    JRA,    // 20   jump relative add (curr prog ptr + x)
    JRS,    // 21   jump relative substract (curr prog ptr - x)
    JE,     // 22   jump if equal
    JL,     // 23   jump if <
    JG,     // 24   jump if >
    JLE,    // 25   jump if <=
    JGE,    // 26   jump if >=
    JRE,    // 27   relative jump if equal
    JRL,    // 28   relative jump if <
    JRG,    // 29   relative jump if >
    JRLE,   // 30   relative jump if <=
    JRGE,   // 31   relative jump if >=
    GPTR,   // 32   get prog ptr
    BEG,    // 33   begin/start
    HALT,   // 34   halt
    // ******* random
    RUD,    // 35   random uniform double : between 0 and 1
    RUI,    // 36   random uniform int
    RN,     // 37   random normal : mu=0, sigma=1
    // ******* instructions EvoX
    GR,     // 38   read gene
    GINS,   // 39   gene insertion
    GDEL,   // 40   gene deletion
    GDELW,  // 41   delete 3 genes at once
    GSET,   // 42   set gene value
    GADD,   // 43   add value to gene
    GCPY,   // 44   copy input into genes (insertion)
    MARKER, // 45   genetic marker
    GCPYM,  // 46   copy input into genes at first genetic marker
    EXEC,   // 47   execute genome specified in args
    EXECD,  // 48   execute code as genome
    size
};

extern std::map<instruction, std::string> instruction_str;
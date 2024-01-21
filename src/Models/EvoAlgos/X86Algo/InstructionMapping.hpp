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
    CPYUS,  // 14   get universe size
    EMPTY,  // 15   tell if a place is empty
    READ,   // 16   read a place
    WRITE,  // 17   write on a place
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
    RG,     // 38   random geometric : p=a/b
    // ******* instructions EvoX
    GR,     // 39   read gene
    GINS,   // 40   gene insertion
    GDEL,   // 41   gene deletion
    GDELW,  // 42   delete 3 genes at once
    GSET,   // 43   set gene value
    GADD,   // 44   add value to gene
    GCPY,   // 45   copy data into genes (insertion)
    MARKER, // 46   genetic marker
    GCPYM,  // 47   copy input into genes at first genetic marker
    EXEC,   // 48   execute genome specified in args
    CALL,   // 49   call function (AD HOC)
    REGEN,  // 50   regenerate code from genome
    size
};

extern std::map<instruction, std::string> instruction_str;
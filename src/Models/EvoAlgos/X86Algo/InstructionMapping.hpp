#pragma once

enum instruction { 
    XXX,    // does nothing
    MOV,    // move data into data
    CPY,    // copy data into data
    CPYIN,  // move input into data
    CPYOUT, // move data into output
    INC,    // increment data
    DEC,    // decrement data
    ADD,    // add data
    SUB,    // substract data
    MUL,    // multiply data
    DIV,    // divide data
    CMP,    // compare data
    JMP,    // jump prog 
    JRA,    // jump relative add (curr prog ptr + x)
    JRS,    // jump relative substract (curr prog ptr - x)
    JRE,    // jump relative add if equal to 0
    JE,     // jump if equal to 0
    JL,     // jump if < 0
    JG,     // jump if > 0
    HALT,   // halt
    // ******* instructions EvoX
    GINS,   // gene insertion
    GDEL,   // gene deletion
    GSET,   // set gene value
    GADD    // add value to gene
};
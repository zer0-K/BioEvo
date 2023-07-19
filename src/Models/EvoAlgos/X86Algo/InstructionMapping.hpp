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
    JE,
    JL,
    JG,
    HALT    // halt
};
#pragma once

enum instruction {
    XXX,    // does nothing
    MOV,    // move data into data
    MOVIN,  // move input into data
    MOVOUT, // move data into output
    CPY,    // copy data into data
    INC,    // increment data
    DEC,    // decrement data
    ADD,    // add data
    SUB,    // substract data
    MUL,    // multiply data
    DIV,    // divide data
    CMP,    // compare data
    JMP,    // jump prog 
    JLE,
    JGE,
    HALT    // halt
};
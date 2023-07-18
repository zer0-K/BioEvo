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
    JLE,
    JGE,
    HALT    // halt
};
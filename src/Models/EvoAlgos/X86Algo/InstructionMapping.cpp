#include "InstructionMapping.hpp"

std::map<instruction, std::string> instruction_str = {
    { instruction::XXX, "XXX" },        // 0
    { instruction::MOV, "MOV" },        // 1
    { instruction::CPY, "CPY" },        // 2
    { instruction::CPYIN, "CPYIN" },    // 3
    { instruction::CPYOUT, "CPYOUT" },  // 4
    { instruction::INC, "INC" },        // 5
    { instruction::DEC, "DEC" },        // 6
    { instruction::ADD, "ADD" },        // 7
    { instruction::SUB, "SUB" },        // 8
    { instruction::MUL, "MUL" },        // 9
    { instruction::DIV, "DIV" },        // 10
    { instruction::OPP, "OPP" },        // 11
    { instruction::CPYIS, "CPYIS" },    // 12
    { instruction::SETOS, "SETOS" },    // 13
    { instruction::CPYUS, "CPYUS" },    // 14
    { instruction::EMPTY, "EMPTY" },    // 15
    { instruction::READ, "READ" },      // 16
    { instruction::WRITE, "WRITE" },    // 17
    { instruction::CMP, "CMP" },        // 18
    { instruction::JMP, "JMP" },        // 19
    { instruction::JRA, "JRA" },        // 20
    { instruction::JRS, "JRS" },        // 21
    { instruction::JE, "JE" },          // 22
    { instruction::JL, "JL" },          // 23
    { instruction::JG, "JG" },          // 24
    { instruction::JLE, "JLE" },        // 25
    { instruction::JGE, "JGE" },        // 26
    { instruction::JRE, "JRE" },        // 27
    { instruction::JRL, "JRL" },        // 28
    { instruction::JRG, "JRG" },        // 29
    { instruction::JRLE, "JRLE" },      // 30
    { instruction::JRGE, "JRGE" },      // 31
    { instruction::GPTR, "GPTR" },      // 32
    { instruction::BEG, "BEG" },        // 33
    { instruction::HALT, "HALT" },      // 34
    { instruction::RUD, "RUD" },        // 35
    { instruction::RUI, "RUI" },        // 36
    { instruction::RN, "RN" },          // 37
    { instruction::RG, "RG" },          // 38
    { instruction::GR, "GR" },          // 39
    { instruction::GINS, "GINS" },      // 40
    { instruction::GDEL, "GDEL" },      // 41
    { instruction::GDELW, "GDELW" },    // 42
    { instruction::GSET, "GSET" },      // 43
    { instruction::GADD, "GADD" },      // 44
    { instruction::GCPY, "GCPY"},       // 45
    { instruction::MARKER, "MARKER"},   // 46
    { instruction::GCPYM, "GCPYM"},     // 47
    { instruction::EXEC, "EXEC" },      // 48
    { instruction::CALL, "CALL" },      // 49
    { instruction::REGEN, "REGEN" }     // 50
}; 
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
    { instruction::AIF, "AIF" },        // 14
    { instruction::RIF, "RIF" },        // 15
    { instruction::AOF, "A0F" },        // 16
    { instruction::ROF, "R0F" },        // 17
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
    { instruction::JRL, "JL" },         // 28
    { instruction::JRG, "JG" },         // 29
    { instruction::JRLE, "JLE" },       // 30
    { instruction::JRGE, "JGE" },       // 31
    { instruction::GPTR, "GPTR" },      // 32
    { instruction::BEG, "BEG" },        // 33
    { instruction::HALT, "HALT" },      // 34
    { instruction::RUD, "RUD" },        // 35
    { instruction::RUI, "RUI" },        // 36
    { instruction::RN, "RN" },          // 37
    { instruction::GR, "GR" },          // 38
    { instruction::GINS, "GINS" },      // 39
    { instruction::GDEL, "GDEL" },      // 40
    { instruction::GDELW, "GDELW" },    // 41
    { instruction::GSET, "GSET" },      // 42
    { instruction::GADD, "GADD" },      // 43
    { instruction::GCPY, "GCPY"},       // 44
    { instruction::MARKER, "MARKER"},   // 45
    { instruction::GCPYM, "GCPYM"},     // 46
    { instruction::EXEC, "EXEC" },      // 47
    { instruction::EXECD, "EXECD" },    // 48
    { instruction::REGEN, "REGEN" }    // 49
}; 
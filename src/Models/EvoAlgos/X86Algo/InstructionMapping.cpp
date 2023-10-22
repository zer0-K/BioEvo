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
    { instruction::BEG, "BEG" },        // 32
    { instruction::HALT, "HALT" },      // 33
    { instruction::RUD, "RUD" },        // 34
    { instruction::RUI, "RUI" },        // 35
    { instruction::RN, "RN" },          // 36
    { instruction::GR, "GR" },          // 37
    { instruction::GINS, "GINS" },      // 38
    { instruction::GDEL, "GDEL" },      // 39
    { instruction::GDELW, "GDELW" },    // 40
    { instruction::GSET, "GSET" },      // 41
    { instruction::GADD, "GADD" },      // 42
    { instruction::GCPY, "GCPY"},       // 43
    { instruction::MARKER, "MARKER"},   // 44
    { instruction::GCPYM, "GCPYM"},     // 45
    { instruction::EXEC, "EXEC" },      // 46
    { instruction::EXECD, "EXECD" }     // 47
}; 
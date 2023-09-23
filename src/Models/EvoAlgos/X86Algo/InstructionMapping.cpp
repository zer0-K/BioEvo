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
    { instruction::CMP, "CMP" },        // 14
    { instruction::JMP, "JMP" },        // 15
    { instruction::JRA, "JRA" },        // 16
    { instruction::JRS, "JRS" },        // 17
    { instruction::JE, "JE" },          // 18
    { instruction::JL, "JL" },          // 19
    { instruction::JG, "JG" },          // 20
    { instruction::JLE, "JLE" },        // 21
    { instruction::JGE, "JGE" },        // 22
    { instruction::JRE, "JRE" },        // 23
    { instruction::JRL, "JL" },         // 24
    { instruction::JRG, "JG" },         // 25
    { instruction::JRLE, "JLE" },       // 26
    { instruction::JRGE, "JGE" },       // 27
    { instruction::BEG, "BEG" },        // 28
    { instruction::HALT, "HALT" },      // 29
    { instruction::RUD, "RUD" },        // 30
    { instruction::RUI, "RUI" },        // 31
    { instruction::RN, "RN" },          // 32
    { instruction::GR, "GR" },          // 33
    { instruction::GINS, "GINS" },      // 34
    { instruction::GDEL, "GDEL" },      // 35
    { instruction::GDELW, "GDELW" },    // 36
    { instruction::GSET, "GSET" },      // 37
    { instruction::GADD, "GADD" },      // 38
    { instruction::GCPY, "GCPY"},       // 39
    { instruction::MARKER, "MARKER"},   // 40
    { instruction::GCPYM, "GCPYM"}      // 41
};
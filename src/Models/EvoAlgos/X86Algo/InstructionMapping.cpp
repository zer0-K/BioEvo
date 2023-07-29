#include "InstructionMapping.hpp"

std::map<instruction, std::string> instruction_str = {
    { instruction::XXX, "XXX" },
    { instruction::MOV, "MOV" },
    { instruction::CPY, "CPY" },
    { instruction::CPYIN, "CPYIN" },
    { instruction::CPYOUT, "CPYOUT" },
    { instruction::INC, "INC" },
    { instruction::DEC, "DEC" },
    { instruction::ADD, "ADD" },
    { instruction::SUB, "SUB" },
    { instruction::MUL, "MUL" },
    { instruction::DIV, "DIV" },
    { instruction::CMP, "CMP" },
    { instruction::JMP, "JMP" },
    { instruction::JRA, "JRA" },
    { instruction::JRS, "JRS" },
    { instruction::JRE, "JRE" },
    { instruction::JE, "JE" },
    { instruction::JL, "JL" },
    { instruction::JG, "JG" },
    { instruction::HALT, "HALT" },
    { instruction::GINS, "GINS" },
    { instruction::GDEL, "GDEL" },
    { instruction::GSET, "GSET" },
    { instruction::GADD, "GADD" }
};
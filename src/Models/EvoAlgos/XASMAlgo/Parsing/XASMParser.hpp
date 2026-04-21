#pragma once

#include <string>
#include <vector>
#include <array>
#include <map>
#include <istream>

#include "../../../../Utils/Constants.hpp"
#include "../InstructionMapping.hpp"

// xasm parsing utilities used by the .evox parser 
class XASMParser {
protected:
    struct ProgteinDef { int id; std::vector<std::array<int, SIZE_INSTR>> code; };
    struct GeneDef     { int id; std::vector<int> content; };
    struct BodyDef {
        std::vector<std::array<int, SIZE_INSTR>> raw_rows;
        std::vector<ProgteinDef> progteins;
        std::vector<GeneDef>    genes;
        int dna_extra_pad = 0;  // explicit zeros appended to DNA before alignment
        std::vector<std::array<int, SIZE_INSTR>> trail_rows;  // appended after DNA
    };

    static const std::map<std::string, int>& instr_map();
    static int  str_to_instr(const std::string& s);
    static int  parse_id(const std::string& token);  // "id=42" or "42" → 42
    static std::vector<std::string> tokenize(const std::string& line);
    static std::array<int, SIZE_INSTR> parse_instr(const std::vector<std::string>& tokens);

    static std::vector<int> assemble(const BodyDef& def);
};

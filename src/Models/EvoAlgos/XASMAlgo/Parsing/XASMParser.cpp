#include "XASMParser.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

#include "../../../../Utils/Constants.hpp"

// ── helpers ────────────────────────────────────────────────────────────────

static std::string to_upper(std::string s) {
    for (auto& c : s) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return s;
}

// ── static members ─────────────────────────────────────────────────────────

const std::map<std::string, int>& XASMParser::instr_map() {
    static std::map<std::string, int> m;
    if (m.empty())
        for (auto& [instr, name] : instruction_str)
            m[name] = static_cast<int>(instr);
    return m;
}

int XASMParser::str_to_instr(const std::string& s) {
    auto it = instr_map().find(to_upper(s));
    if (it == instr_map().end())
        throw std::runtime_error("XASMParser: unknown instruction '" + s + "'");
    return it->second;
}

int XASMParser::parse_id(const std::string& token) {
    auto eq = token.find('=');
    return std::stoi(eq == std::string::npos ? token : token.substr(eq + 1));
}

// "test 0 1" -> ["test", "0", "1"]
std::vector<std::string> XASMParser::tokenize(const std::string& line) {
    std::string stripped = line.substr(0, line.find("//"));
    std::istringstream ss(stripped);
    std::vector<std::string> tokens;
    std::string tok;
    while (ss >> tok) tokens.push_back(tok);
    return tokens;
}

std::array<int, SIZE_INSTR> XASMParser::parse_instr(const std::vector<std::string>& t) {
    if (t.size() < 7)
        throw std::runtime_error(
            "XASMParser: instruction needs 7 tokens, got " + std::to_string(t.size())
            + " (first token: '" + (t.empty() ? "" : t[0]) + "')");
    return { str_to_instr(t[0]),
             std::stoi(t[1]), std::stoi(t[2]), std::stoi(t[3]),
             std::stoi(t[4]), std::stoi(t[5]), std::stoi(t[6]) };
}

// ── assembler ──────────────────────────────────────────────────────────────

std::vector<int> XASMParser::assemble(const BodyDef& def) {
    std::vector<int> body;

    // verbatim header rows
    for (auto& row : def.raw_rows)
        for (int v : row) body.push_back(v);

    // progteins: MARKER(id) + instructions
    for (auto& p : def.progteins) {
        body.insert(body.end(), {46, 0, p.id, 0, 0, 0, 0});
        for (auto& instr : p.code)
            for (int v : instr) body.push_back(v);
    }

    // DNA section
    if (!def.genes.empty()) {
        body.insert(body.end(), {46, 0, -1, 0, 0, 0, 0});  // DNA start marker

        std::vector<int> dna;
        for (auto& g : def.genes) {
            dna.push_back(GSTART_ID);
            dna.push_back(g.id);
            dna.insert(dna.end(), g.content.begin(), g.content.end());
            dna.push_back(GSTOP_ID);
            // pad each gene block to a multiple of SIZE_INSTR
            while (dna.size() % SIZE_INSTR != 0) dna.push_back(0);
        }
        // optional explicit extra padding after all genes
        for (int i = 0; i < def.dna_extra_pad; i++) dna.push_back(0);
        // final alignment
        while (dna.size() % SIZE_INSTR != 0) dna.push_back(0);
        body.insert(body.end(), dna.begin(), dna.end());

        body.insert(body.end(), {46, 0, -1, 0, 0, 0, 0});  // DNA end marker
    }

    for (auto& row : def.trail_rows)
        for (int v : row) body.push_back(v);

    return body;
}

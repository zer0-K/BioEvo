#include "EvoXParser.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>

// ── helpers ────────────────────────────────────────────────────────────────

// make string upper case
static std::string evox_upper(std::string s) {
    for (auto& c : s) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return s;
}

// Resolve one DNA token:
//   @name  → look up progtein id in names map
//   name   → try tRNA name lookup (e.g. "CALLcst", "tRNA_SIJ", "ret")
//   int    → parse as integer (fallback)
int EvoXParser::resolve_token(const std::string& tok, const NameMap& names) {
    if (!tok.empty() && tok[0] == '@') {
        auto it = names.find(tok.substr(1));
        if (it == names.end())
            throw std::runtime_error("EvoXParser: unknown progtein reference '" + tok + "'");
        return it->second;
    }
    int id = tRNA_id(tok);
    if (id >= 0) return id;
    // fallback: raw integer (throws std::invalid_argument if not numeric)
    try { return std::stoi(tok); }
    catch (...) {
        throw std::runtime_error("EvoXParser: cannot resolve token '" + tok + "'");
    }
}

// ── body parser ────────────────────────────────────────────────────────────

// parse .evox file into a body definition
XASMParser::BodyDef EvoXParser::parse_evox_body_def(std::istream& in, NameMap& names) {
    BodyDef def;
    std::string line;

    while (std::getline(in, line)) {
        auto tokens = tokenize(line);
        if (tokens.empty()) continue;
        std::string kw = evox_upper(tokens[0]);

        if (kw == "RAW") {
            while (std::getline(in, line)) {
                auto t = tokenize(line);
                if (t.empty()) continue;
                if (evox_upper(t[0]) == "END") break;
                if (t.size() < 7)
                    throw std::runtime_error("EvoXParser: RAW row needs 7 ints");
                std::array<int, SIZE_INSTR> row;
                for (int i = 0; i < SIZE_INSTR; i++) row[i] = std::stoi(t[i]);
                def.raw_rows.push_back(row);
            }

        } else if (kw == "PROGTEIN") {
            // PROGTEIN [name] id=N  OR  PROGTEIN id=N  OR  PROGTEIN N
            ProgteinDef p;
            p.id = 0;
            std::string label;
            for (size_t i = 1; i < tokens.size(); i++) {
                const auto& tok = tokens[i];
                if (tok.find("id=") == 0)
                    p.id = std::stoi(tok.substr(3));
                else if (!tok.empty() && (std::isdigit(tok[0]) || tok[0] == '-'))
                    p.id = std::stoi(tok);
                else
                    label = tok;  // optional name label
            }
            if (!label.empty()) names[label] = p.id;

            while (std::getline(in, line)) {
                auto t = tokenize(line);
                if (t.empty()) continue;
                if (evox_upper(t[0]) == "END") break;
                p.code.push_back(parse_instr(t));
            }
            def.progteins.push_back(std::move(p));

        } else if (kw == "TRAIL") {
            while (std::getline(in, line)) {
                auto t = tokenize(line);
                if (t.empty()) continue;
                if (evox_upper(t[0]) == "END") break;
                if (t.size() < 7)
                    throw std::runtime_error("EvoXParser: TRAIL row needs 7 ints");
                std::array<int, SIZE_INSTR> row;
                for (int i = 0; i < SIZE_INSTR; i++) row[i] = std::stoi(t[i]);
                def.trail_rows.push_back(row);
            }

        } else if (kw == "DNA") {
            while (std::getline(in, line)) {
                auto t = tokenize(line);
                if (t.empty()) continue;
                if (evox_upper(t[0]) == "END") break;
                if (evox_upper(t[0]) == "GENE") {
                    GeneDef g;
                    g.id = (t.size() > 1) ? parse_id(t[1]) : 0;
                    while (std::getline(in, line)) {
                        auto gt = tokenize(line);
                        if (gt.empty()) continue;
                        if (evox_upper(gt[0]) == "END") break;
                        for (auto& tok : gt)
                            g.content.push_back(resolve_token(tok, names));
                    }
                    def.genes.push_back(std::move(g));
                } else if (evox_upper(t[0]) == "PAD") {
                    if (t.size() > 1) def.dna_extra_pad += std::stoi(t[1]);
                }
            }
        }
    }
    return def;
}

// ── public API ─────────────────────────────────────────────────────────────

std::vector<int> EvoXParser::parse_body(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open())
        throw std::runtime_error("EvoXParser: cannot open '" + path + "'");
    NameMap names;
    return assemble(parse_evox_body_def(f, names));
}

#pragma once

#include "XASMParser.hpp"
#include "tRNATable.hpp"

// Parses .evox files — same block structure as .xasm body mode but with
// human-friendly names instead of raw integers.
//
// Differences from .xasm:
//   • PROGTEIN accepts an optional name label before id=N:
//       PROGTEIN meta_exec id=0
//   • DNA gene content uses tRNA names (with or without "tRNA_" prefix,
//     case-insensitive) and @name references to progtein IDs:
//       GENE id=1000
//           CALLcst @meta_exec   // → 11500, 0
//           SIJ                  // → 10600
//           RET                  // → 9999
//       END
//   • Raw integers still work (fallback when no name matches).
//
// XASM instructions inside PROGTEIN blocks are parsed the same as in .xasm.

class EvoXParser : public XASMParser {
public:
    static std::vector<int> parse_body(const std::string& path);

private:
    using NameMap = std::map<std::string, int>;  // progtein_name → id

    static BodyDef parse_evox_body_def(std::istream& in, NameMap& names);
    static int     resolve_token(const std::string& tok, const NameMap& names);
};

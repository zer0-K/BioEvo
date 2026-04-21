#pragma once

#include <map>
#include <string>

struct TRNAInfo { std::string name; int arity; };

// ID → {name, arity}
extern const std::map<int, TRNAInfo> tRNA_by_id;

// Lowercase name → ID.  Accepts full name ("trna_ret") or short form ("ret").
extern const std::map<std::string, int> tRNA_by_name;

int  tRNA_arity(int id);              // -1 if unknown
int  tRNA_id(const std::string& name); // -1 if unknown
bool is_tRNA_id(int id);              // true iff id in [9999, 29999]

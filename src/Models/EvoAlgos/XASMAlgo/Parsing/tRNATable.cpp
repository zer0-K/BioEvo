#include "tRNATable.hpp"
#include <algorithm>
#include <cctype>

const std::map<int, TRNAInfo> tRNA_by_id = {
    // Variable management
    {9999,  {"tRNA_RET",       0}},
    {10000, {"tRNA_CVARS",     2}},
    {10001, {"tRNA_IVARS",     0}},
    // Store / load local variables
    {10100, {"tRNA_SLVcst",    2}},
    {10101, {"tRNA_SDLVcst",   2}},
    {10110, {"tRNA_SLVLV",     2}},
    {10111, {"tRNA_SDLVLV",    2}},
    {10112, {"tRNA_SLVDLV",    2}},
    {10113, {"tRNA_SDLVDLV",   2}},
    {10114, {"tRNA_ScstLV",    2}},
    {10115, {"tRNA_SLVaddr",   2}},
    // Gene read / write
    {10150, {"tRNA_RGLVLV",    2}},
    {10170, {"tRNA_WGDLV",     3}},
    // Get input
    {10200, {"tRNA_GILV",      2}},
    {10201, {"tRNA_GDILV",     2}},
    {10202, {"tRNA_GIDLV",     2}},
    {10203, {"tRNA_GDIDLV",    2}},
    // Stack get
    {10210, {"tRNA_GTSLV",     1}},
    {10211, {"tRNA_GTSLVD",    1}},
    {10212, {"tRNA_GTSDLV",    1}},
    {10250, {"tRNA_GLVO",      2}},
    // Control flow
    {10500, {"tRNA_IF0",       1}},
    {10600, {"tRNA_SIJ",       0}},
    {10700, {"tRNA_SEJ",       0}},
    {10800, {"tRNA_SWJ",       1}},
    {10900, {"tRNA_JLV",       1}},
    // Stack output (push/pop)
    {11000, {"tRNA_SOScst",    1}},
    {11001, {"tRNA_SOSLV",     1}},
    {11010, {"tRNA_GISLV",     1}},
    {11100, {"tRNA_PCSI",      1}},
    {11150, {"tRNA_PLVSI",     1}},
    {11200, {"tRNA_PCSWI",     1}},
    {11250, {"tRNA_PLVSWI",    1}},
    // Compare
    {11300, {"tRNA_CMPLVcst",  4}},
    {11350, {"tRNA_CMPLVLV",   4}},
    // Arithmetic operations
    {11400, {"tRNA_OPEcstcst", 3}},
    {11401, {"tRNA_OPEcstLV",  3}},
    {11402, {"tRNA_OPELVcst",  3}},
    {11403, {"tRNA_OPELVLV",   3}},
    // Increment / decrement
    {11450, {"tRNA_INCcst",    2}},
    {11451, {"tRNA_INCLV",     2}},
    {11452, {"tRNA_INCDLV",    2}},
    {11453, {"tRNA_INCS",      1}},
    // Function call
    {11500, {"tRNA_CALLcst",   1}},
    {11501, {"tRNA_CALLLV",    1}},
    // Recursive unsigned integer (RUI)
    {11600, {"tRNA_RUIcstcst", 3}},
    {11601, {"tRNA_RUIcstLV",  3}},
    {11602, {"tRNA_RUILVcst",  3}},
    {11603, {"tRNA_RUILVLV",   3}},
    // Gene op (get/set slice)
    {12000, {"tRNA_GScstcst",  2}},
    {12001, {"tRNA_GScstLV",   2}},
    {12002, {"tRNA_GSLVcst",   2}},
    {12003, {"tRNA_GSLVLV",    2}},
    {12500, {"tRNA_GADD",      2}},
    // Universe interaction
    {13000, {"tRNA_USLV",      1}},
    {13001, {"tRNA_RULV",      1}},
    {13100, {"tRNA_EMPTY",     2}},
    {13200, {"tRNA_WRITE",     2}},
    // Halt
    {14999, {"tRNA_HALT",      0}},
    // Meta tRNAs (used in tRNA definitions)
    {14000, {"tRNA_MP",        0}},
    {14010, {"tRNA_ME",        0}},
    {14100, {"tRNA_Mcst",      1}},
    {14101, {"tRNA_M0",        0}},
    {14102, {"tRNA_M1",        0}},
    {14103, {"tRNA_M2",        0}},
    {14104, {"tRNA_M3",        0}},
    {14200, {"tRNA_MInstr",    1}},
    {14201, {"tRNA_MCPY",      0}},
    {14300, {"tRNA_Marg",      0}},
    {14301, {"tRNA_MargW",     0}},
    {14310, {"tRNA_MLV",       0}},
    {14311, {"tRNA_MLVW",      0}},
    // Special / stack pointer tRNAs
    {15000, {"tRNA_SP_GPTR",   0}},
    {15001, {"tRNA_SP_FCTADD", 0}},
    {15002, {"tRNA_SP_GFPTRLV",1}},
    {15003, {"tRNA_SP_GSPLV",  1}},
    {15004, {"tRNA_SP_GCPY",   3}},
};

static std::string to_lower(std::string s) {
    for (auto& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

const std::map<std::string, int> tRNA_by_name = []() {
    std::map<std::string, int> m;
    for (auto& [id, info] : tRNA_by_id) {
        std::string full = to_lower(info.name);  // "trna_ret"
        m[full] = id;
        if (full.size() > 5)
            m[full.substr(5)] = id;  // "ret" (strip "trna_")
    }
    return m;
}();

int tRNA_arity(int id) {
    auto it = tRNA_by_id.find(id);
    return it != tRNA_by_id.end() ? it->second.arity : -1;
}

int tRNA_id(const std::string& name) {
    auto it = tRNA_by_name.find(to_lower(name));
    return it != tRNA_by_name.end() ? it->second : -1;
}

bool is_tRNA_id(int id) { return id >= 9999 && id <= 29999; }

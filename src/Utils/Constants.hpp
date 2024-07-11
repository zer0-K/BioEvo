#pragma once

#include <string>

#include "Colors.hpp"

// ------------------------------------------------------------ other

const bool verbose_unit_tests = true;
const bool verbose_unit_tests_1 = true;
const bool verbose_unit_tests_2 = true;
const bool verbose_experiment_1 = false;

const std::string project_folder = "/home/adrien/Programmation/Projets/BioEvo/";


// ------------------------------------------------------------ colors

const ColorMod defcol(FG_DEFAULT);
const ColorMod greencol(FG_GREEN);
const ColorMod redcol(FG_RED);


// ------------------------------------------------------------ entity types

const std::string TYPE_ENTITY = "entity";
const std::string TYPE_VOID = "void";
const std::string TYPE_BOOL = "bool";
const std::string TYPE_INT  = "int";

const std::string TYPE_LIST = "list";


// -------------------- CLASSICAL ALGOS


const std::string CA_DATA  = "classical data";
const std::string CA_DATA_TEST = "classical test data";
const std::string CA_DATA_VALIDATION = "classical validation data";

const std::string CA_INDIVIDUAL = "classical algo";
const std::string CA_LIN_SIMP = "simple linear";


// -------------------- CODE EATER


const std::string TYPE_META = "meta";
const std::string TYPE_OP_COUNTER = "operation counter";
const std::string TYPE_EXEC_INDEX = "execution index";


const std::string TYPE_OP = "operation";
const std::string TYPE_OP_BOOL = "operation boolean";
const std::string TYPE_OP_INT = "operation int";


const std::string TYPE_BOOLID = "boolean id";
const std::string TYPE_NOT = "not";
const std::string TYPE_BOOLIDIN = "in place boolean id";
const std::string TYPE_NOTIN = "in place not";
const std::string TYPE_AND = "and";
const std::string TYPE_NAND = "nand";
const std::string TYPE_ANDIN = "andin";
const std::string TYPE_NANDIN = "nandin";
const std::string TYPE_OR = "or";
const std::string TYPE_NOR = "nor";
const std::string TYPE_ORIN = "orin";
const std::string TYPE_NORIN = "norin";
const std::string TYPE_XOR = "xor";
const std::string TYPE_NXOR = "nxor";
const std::string TYPE_XORIN = "xorin";
const std::string TYPE_NXORIN = "nxorin";

const std::string TYPE_INCR = "increment";
const std::string TYPE_ADDINT = "int addition";
const std::string TYPE_ADDINTIN = "in place int addition";
const std::string TYPE_SUBINT = "int substraction";
const std::string TYPE_SUBINTIN = "in place int substraction";
const std::string TYPE_MULTINT = "int multiplication";
const std::string TYPE_MULTINTIN = "in place int multiplication";
const std::string TYPE_DIVINT = "int division";
const std::string TYPE_DIVINTIN = "in place int division";

const std::string TYPE_COPY = "copy";
const std::string TYPE_SHUFFLE = "shuffle";

const std::string TYPE_CE = "code eater";

const std::string TYPE_LINEAR = "linear";


// -------------------- EVO ALGOS

const std::string X86_ALGO = "x86 algo";
const int DEFAULT_X86_DATA_SIZE = 10000;
const int DEFAULT_X86_CODE_SIZE = 100;
const int MAX_OUTPUT_SIZE_X86 = 10000;
const int SIZE_INSTR = 7;

const std::string EVOX = "evo x86 algo";
const std::string FREEGENES = "free code";

inline bool EVOX_LOGGING = false;
const std::string LOG_FILE_DEFAULT = "/home/adrien/Disque/Programmation/Projets/BioEvo/log/autopoiesis_1.csv";

// ---------- Genetic constants

const int GSTART_ID = -51451;
const int GSTOP_ID = -77142;


// ------------------------------------------------------------ Experiment names



// -------------------- CLASSICAL INFO

const std::string name_exp_classical_info = "classical info experiments";
const std::string name_exp_console_app = "console app";

// ---------- FUNCTION EXECUTION

const std::string name_exp_classical_info_func_exec = "experiments on function executions";
const std::string name_exp_classical_info_func_exec_evox = "EvoX function execution";
const std::string name_exp_classical_info_func_acqu_evox = "EvoX genetic function acquisition";

// -------------------- BIO EVO

const std::string name_exp_bioevo = "bio evo experiments";

// ---------- TRAIT

const std::string name_exp_bioevo_traits = "experiments on traits";
const std::string name_exp_bioevo_traits_evox = "EvoX driving traits";

// ---------- GENE

const std::string name_exp_bioevo_genes = "experiments on genes";
const std::string name_exp_bioevo_genes_evox_fgc = "Evox free gene creation";
const std::string name_exp_bioevo_genes_evox_gtp = "Evox gene to progtein";
const std::string name_exp_bioevo_genes_evox_selfc = "Evox gene self-compilation";

// tRNAs
const int id_tRNA_RET = 9999;

const int id_tRNA_CVARS = 10000; // heap pos, nb vars
const int id_tRNA_IVARS = 10001;

const int id_tRNA_SLVcst = 10100; // var nb, cst val
const int id_tRNA_SDLVcst = 10101; // var nb, cst val
const int id_tRNA_SLVLV = 10110; // var nb, var nb
const int id_tRNA_SDLVLV = 10111; // var nb, var nb
const int id_tRNA_SLVDLV = 10112; // var nb, var nb
const int id_tRNA_SDLVDLV = 10113; // var nb, var nb
const int id_tRNA_ScstLV = 10114; // addr, var nb
const int id_tRNA_SLVaddr = 10115; // var nb, addr
const int id_tRNA_RGLVLV = 10150; // var nb, var nb
const int id_tRNA_WGDLV = 10170; // var nb, var nb, var nb
const int id_tRNA_GILV = 10200; // var nb, input index
const int id_tRNA_GDILV = 10201; // var nb, input index
const int id_tRNA_GIDLV = 10202; // var nb, input index
const int id_tRNA_GDIDLV = 10203; // var nb, input index
const int id_tRNA_GTSLV = 10210; // var nb
const int id_tRNA_GTSLVD = 10211; // var nb
const int id_tRNA_GTSDLV = 10212; // var nb
const int id_tRNA_GLVO = 10250; // output index, var nb

const int id_tRNA_IF0 = 10500; // var nb
const int id_tRNA_SIJ = 10600;
const int id_tRNA_SEJ = 10700;
const int id_tRNA_SWJ = 10800; // var nb
const int id_tRNA_JLV = 10900; // var nb

const int id_tRNA_SOScst = 11000; // cst
const int id_tRNA_GISLV = 11001; // var nb
const int id_tRNA_PCSI = 11100; // cst
const int id_tRNA_PLVSI = 11150; // var nb
const int id_tRNA_PCSWI = 11200; // cst
const int id_tRNA_PLVSWI = 11250; // var nb

const int id_tRNA_CMPLVcst = 11300; // CMP OP, var nb, cst, var nb
const int id_tRNA_CMPLVLV = 11350; // CMP OP, var nb, var nb, var nb

const int id_tRNA_OPELVcst = 11400; // OP, var nb, cst
const int id_tRNA_OPELVLV = 11401; // OP, var nb, var nb
const int id_tRNA_INCcst = 11450; // inc/dec flag, cst
const int id_tRNA_INCLV = 11451; // inc/dec flag, var nb
const int id_tRNA_INCDLV = 11452; // inc/dec flag, var nb
const int id_tRNA_INCS = 11453; // inc/dec flag

const int id_tRNA_CALLcst = 11500; // cst
const int id_tRNA_CALLLV = 11501; // var nb

const int id_tRNA_GScstcst = 12000; // cst, cst
const int id_tRNA_GScstLV = 12001; // cst, var
const int id_tRNA_GSLVcst = 12002; // var, cst
const int id_tRNA_GSLVLV = 12003; // var, var

const int id_tRNA_USLV = 13000; // var nb
const int id_tRNA_RULV = 13001; // var nb


const int id_tRNA_MP = 14000;
const int id_tRNA_ME = 14010;

const int id_tRNA_M0 = 14100;
const int id_tRNA_M1 = 14101;
const int id_tRNA_MInstr = 14200;
const int id_tRNA_MCPY = 14201;

const int id_tRNA_Marg = 14300;
const int id_tRNA_MLV = 14310;


const int id_tRNA_HALT = 14999;

const int id_tRNA_SP_GPTR = 15000;
const int id_tRNA_SP_FCTADD = 15001;
const int id_tRNA_SP_GFPTRLV = 15002; // var nb
const int id_tRNA_SP_GSPLV = 15003; // var nb
const int id_tRNA_SP_GCPY = 15004; // var nb, var nb, var nb


// ---------- GENESIS

const std::string name_exp_bioevo_genesis = "generation of base evoX";
const std::string name_exp_bioevo_genesis_1 = "generation of base evoX 1";
const std::string name_exp_bioevo_genesis_2 = "generation of base evoX 2";


// ---------- REPLICATORS

const std::string name_exp_bioevo_replication = "experiments on replication";
const std::string name_exp_bioevo_replication_evox_quine = "EvoX quine replication";

// ---------- TELEONOMY

const std::string name_exp_bioevo_teleonomy = "experiments on teleonomy";
const std::string name_exp_bioevo_teleonomy_design_evox = "teleonomical design of evox algos";

// -------------------- EVO ALGOS

const std::string name_exp_evoalgos = "evo algos experiments";

// -------------------- MATHS

const std::string name_exp_maths = "maths experiments";

// ---------- RECURSIVE OPS

const std::string name_exp_maths_playground = "maths playground";
const std::string name_exp_maths_gen_recursive_ops = "recursive operations generation";
#pragma once

#include <string>

#include "Colors.hpp"

// ------------------------------------------------------------ other

const bool verbose_unit_tests = true;
const bool verbose_unit_tests_1 = true;
const bool verbose_unit_tests_2 = true;
const bool verbose_experiment_1 = false;


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
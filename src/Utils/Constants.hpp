#pragma once

#include <string>

#include "Colors.hpp"

// ---------------------------------------- other

const bool verbose_unit_tests = true;


// ---------------------------------------- colors

const ColorMod defcol(FG_DEFAULT);
const ColorMod greencol(FG_GREEN);
const ColorMod redcol(FG_RED);


// ---------------------------------------- entity types

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
const int DEFAULT_X86_DATA_SIZE = 1000;
const int DEFAULT_X86_CODE_SIZE = 1000;

const std::string EVOX = "evo x86 algo";


// ---------------------------------------- Experiment names

const std::string name_exp_console_app = "console app";
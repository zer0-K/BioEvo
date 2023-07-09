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


const std::string TYPE_META = "meta";
const std::string TYPE_OP_COUNTER = "operation counter";
const std::string TYPE_EXEC_INDEX = "execution index";


const std::string TYPE_OP = "operation";
const std::string TYPE_OP_BOOL = "operation boolean";
const std::string TYPE_OP_INT = "operation int";


const std::string TYPE_UID = "unary id";
const std::string TYPE_UNOT = "unary not";
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

const std::string TYPE_COPY = "copy";

const std::string TYPE_LINEAR = "linear";


// ---------------------------------------- Experiment names

const std::string name_exp_console_app = "console app";
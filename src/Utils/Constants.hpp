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

const std::string TYPE_VOID = "void";
const std::string TYPE_BOOL = "bool";
const std::string TYPE_INT  = "int";

const std::string TYPE_LIST = "list";

const std::string TYPE_UID = "unary id";
const std::string TYPE_UNOT = "unary not";

const std::string TYPE_LINEAR = "linear";


// ---------------------------------------- Experiment names

const std::string name_exp_console_app = "console app";
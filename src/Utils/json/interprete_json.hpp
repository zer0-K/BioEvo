#pragma once

#include <boost/json.hpp>

#include "../../Framework.hpp"


extern std::vector<boost::json::object> convert_to_objs(std::string);
extern std::string exec_instr(Framework*, std::string, boost::json::object*);

extern std::string add_universe(Framework*, boost::json::object*);
extern std::string add_environment(Framework*, boost::json::object*);
extern std::string set_individuals(Framework*, boost::json::object*);
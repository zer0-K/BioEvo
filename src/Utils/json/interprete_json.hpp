#pragma once

#include <boost/json.hpp>

#include "../../Framework.hpp"


extern std::vector<boost::json::object> convert_to_objs(std::string);
extern std::string exec_instr(sp_framework, std::string, boost::json::object*);

extern std::string add_universe(sp_framework, boost::json::object*);
extern std::string add_environment(sp_framework, boost::json::object*);
extern std::string set_individuals(sp_framework, boost::json::object*);
extern std::string add_individual(sp_framework, boost::json::object*);
extern std::string add_individuals(sp_framework, boost::json::object*);
extern std::string launch(sp_framework, boost::json::object*);
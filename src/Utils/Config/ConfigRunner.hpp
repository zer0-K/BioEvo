#pragma once

#include "../../Framework.hpp"

#include <boost/json.hpp>

class ConfigRunner
{
private:
    Framework* framework;

    std::vector<std::string> executed_instructions;
    std::vector<boost::json::object>* instructions_list;
    size_t nb_list_instructions;

    bool is_running;

public:
    ConfigRunner(Framework* framework);

    void add_instructions(std::vector<boost::json::object> instructions);

    void continue_exec();

    bool is_executing();
};
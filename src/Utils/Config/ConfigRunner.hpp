#pragma once

#include "../../Framework.hpp"

#include <boost/json.hpp>

class ConfigRunner
{
private:
    //sp_framework framework;
    sp_framework framework;

    std::vector<std::string> executed_instructions;
    std::vector<std::vector<boost::json::object>> instructions_list;

    bool is_running;

public:
    //ConfigRunner(sp_framework framework);
    ConfigRunner(sp_framework framework);

    void add_instructions(std::vector<boost::json::object> instructions);

    /**
     * @brief execute the instructions in the instruction set
     * 
     * @return message (success, error,...)
    */
    std::string continue_exec();

    bool is_executing();
};

typedef std::shared_ptr<ConfigRunner> sp_configrunner;
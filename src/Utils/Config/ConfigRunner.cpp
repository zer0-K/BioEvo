#include "ConfigRunner.hpp"

#include "../json/interprete_json.hpp"

ConfigRunner::ConfigRunner(sp_framework framework)
{
    this->framework = framework;

    this->executed_instructions = std::vector<std::string>();
    this->instructions_list = std::vector<std::vector<boost::json::object>>();

    this->is_running = false;
}

void ConfigRunner::add_instructions(std::vector<boost::json::object> instructions)
{
    this->instructions_list.push_back(instructions); 
}

void ConfigRunner::continue_exec()
{
    this->is_running = true;

    while(this->is_running)
    {
        // always execute the first instruction of the first set of instructions
        boost::json::object instr = this->instructions_list[0][0];
        std::string instr_name = boost::json::value_to<std::string>( instr["name"] );

        if(instr_name == "END")
        {
            // remove 'end' instruction
            this->instructions_list[0].erase(this->instructions_list[0].begin());

            // remove the first set of instruction since it is over
            this->instructions_list.erase(this->instructions_list.begin());
        } 
        else 
        {
            if(instr_name == "BREAK")
            {
                // pause execution if 'break' was given
                this->is_running = false;
            }
            else
            {
                boost::json::object* params = instr["params"].if_object();
                exec_instr(this->framework, instr_name, params);
            }

            // remove 'break' instruction
            this->instructions_list[0].erase(this->instructions_list[0].begin());
        }
        
        // if we have executed all the sets of instructions, we are finnished
        if(this->instructions_list.empty())
        {
            this->is_running = false;
        }
    }
}

bool ConfigRunner::is_executing()
{
    return this->is_running;
}

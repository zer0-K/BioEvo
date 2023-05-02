#include "ConfigRunner.hpp"

#include "../Convert/json_interprete.hpp"

ConfigRunner::ConfigRunner(Framework* framework)
{
    this->framework = framework;

    this->executed_instructions = std::vector<std::string>();
    this->instructions_list = new std::vector<boost::json::object>();
    this->nb_list_instructions = 0;

    this->is_running = false;
}

void ConfigRunner::add_instructions(std::vector<boost::json::object> instructions)
{
    this->nb_list_instructions++;

    std::vector<boost::json::object>* instructions_old = this->instructions_list;
    this->instructions_list = new std::vector<boost::json::object>[this->nb_list_instructions];

    // place the new set of instructions at the beginning of the list to exec them first
    this->instructions_list[0] = instructions;
    for(int i=1; i<this->nb_list_instructions;i++)
    {
        this->instructions_list[i] = instructions_old[i];
    } 
}

void ConfigRunner::continue_exec()
{
    this->is_running = true;

    // index of the current set of instructions
    int set_instr_curr_ind = 0;
    int instr_curr_ind = 0;

    while(this->is_running)
    {
        boost::json::object instr = this->instructions_list[set_instr_curr_ind][instr_curr_ind];
        std::string instr_name = boost::json::value_to<std::string>( instr["name"] );

        if(instr_name == "END")
        {
            set_instr_curr_ind++;
            instr_curr_ind = 0;

            this->is_running = false;
        } 
        else if(instr_name == "BREAK")
        {
            this->is_running = false;

            // shift all the instructions left for the current set
            std::vector<boost::json::object> curr_set = std::vector<boost::json::object>();
            for(int i=instr_curr_ind+1;i<this->instructions_list[set_instr_curr_ind].size();i++)
                curr_set.push_back(this->instructions_list[set_instr_curr_ind][i]);
            this->instructions_list[set_instr_curr_ind] = curr_set;

            // shift all the sets left
            auto set_instr_old = this->instructions_list;
            this->instructions_list = new std::vector<boost::json::object>[this->nb_list_instructions-set_instr_curr_ind];
            for(int i=0;i<this->nb_list_instructions-set_instr_curr_ind;i++)
            {
                this->instructions_list[i] = set_instr_old[set_instr_curr_ind+i];
            }
            this->nb_list_instructions -= set_instr_curr_ind;
        }
        else
        {
            boost::json::object* params = instr["params"].if_object();
            exec_instr(this->framework, instr_name, params);

            instr_curr_ind++;
        }

        if(set_instr_curr_ind == this->nb_list_instructions)
        {
            this->is_running = false;
            this->nb_list_instructions = 0;
        }
    }
}

bool ConfigRunner::is_executing()
{
    return this->is_running;
}

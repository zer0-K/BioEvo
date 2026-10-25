#pragma once

#include <array>
#include <map>
#include <vector>
#include <functional>

#include "../../../../Utils/Constants.hpp"


class BiologicalDebugger
{
protected:
    bool _stop;

    bool activated = false;
    std::vector<int> progteins_to_stop_at;
    std::array<int,SIZE_INSTR> current_line;
    int program_pointer;
    int program_pointer_stop;
    int instr_counter_stop;
    int current_progtein;
    std::vector<int> previous_progteins;

    // for each progtein, tell how long we spent at each line
    std::map<int, std::map<int, int>> profiler;


    //- Replication debugging -----------------------------------------------

    bool is_replication;
    std::vector<int> progteins_to_replicate;
    int current_replicated_progtein;
    // for each progtein transciption, 
    // profile how long we spent in each progtein
    std::map<int, std::map<int, int>> replication_profiler;
    std::map<int, int> nb_instr_per_replicated_gene;

    bool is_building_func_ID_list;

    //- Replication debugging (end) -----------------------------------------

public:

    BiologicalDebugger()
    {
        progteins_to_stop_at = std::vector<int>{};
        reset();
        reset_replication_info();
    }

    void activate()
    {
        activated = true;
    }

    void add_breakpoint_at_progtein(int progtein_nb)
    {
        for(size_t i=0; i<progteins_to_stop_at.size();i++)
            if (progteins_to_stop_at[i] == progtein_nb)
                return;
        
        progteins_to_stop_at.push_back(progtein_nb);
    }

    void check_current_line()
    {
        if(program_pointer <= 30)
            current_progtein = 0;

        // progtein begin recognition
        if(current_line[0] == 46 && program_pointer > 4)
        {
            for (size_t i=0; i<progteins_to_stop_at.size();i++)
            {
                if(current_line[2] == progteins_to_stop_at[i])
                {
                    _stop = true;
                }
            }

            current_progtein = current_line[2];
            previous_progteins.push_back(current_progtein);
        }

        // after a return
        if(program_pointer > 40 && current_progtein == 0)
            current_progtein = previous_progteins[previous_progteins.size() - 1];
        
        profile();

        if(is_replication)
            replication_info();
        
        // return : we exit the progtein -> current_progtein = 0
        if(current_line[0] == 19 && current_line[1] == 2 
            && current_line[2] == 0 && current_line[3] == 0 
            && current_line[4] == 0 && current_line[5] == 0 
            && current_line[6] == 0)
        {
            previous_progteins.pop_back();
            current_progtein = 0;
        }
    }

    void check(std::array<int,SIZE_INSTR> line, int program_pointer, int instr_counter)
    {
        if(!activated)
            return;
        
        this->program_pointer = program_pointer;
        current_line = line;

        bool was_stopped = _stop;
        check_current_line();

        if (_stop && !was_stopped)
        {
            program_pointer_stop = program_pointer;
            instr_counter_stop = instr_counter;
        }
    }

    void check_input(std::vector<int> in)
    {
        if(!activated)
            return;
        
        // if not building func ID list during replication:
        // it's transcribing a gene
        if(is_replication && !is_building_func_ID_list)
        {
            current_replicated_progtein = progteins_to_replicate[progteins_to_replicate.size()-1];
            progteins_to_replicate.pop_back();
        }
        
        if(in.size()>1 && in[0] == -1 && in[1] == id_self_compil_func_ID_list)
        {
            is_replication = true;
            is_building_func_ID_list = true;
        }
    }

    void check_end_of_step(std::vector<int> data, int instr_counter)
    {
        if(!activated)
            return;

        if(is_replication && !is_building_func_ID_list)
        {
            nb_instr_per_replicated_gene[current_replicated_progtein] = instr_counter;
            
            if(progteins_to_replicate.size() == 0)
            {
                is_replication = false;
            }
        }

        if(is_building_func_ID_list)
        {
            int stack_pos = data[99];
            int nb_genes = data[stack_pos+4];
            int func_id_list_pos = stack_pos+5;

            for(int i = 0; i<nb_genes; i++)
            {
                progteins_to_replicate.push_back(data[func_id_list_pos + i]);
            }

            is_building_func_ID_list = false;
        }
    }

    bool stop()
    {
        return activated && _stop;
    }

    void resume()
    {
        _stop = false;
    }

    void reset()
    {
        _stop = false;
        program_pointer = 0;
        program_pointer_stop = 0;
        instr_counter_stop = 0;
        current_progtein = 0;
        previous_progteins = {};

        profiler = {};
    }

    void reset_replication_info()
    {
        is_replication = false;
        progteins_to_replicate = {};
        current_replicated_progtein = -1;
        replication_profiler = {};
        nb_instr_per_replicated_gene = {};
    }

    void profile()
    {
        // init info in case of beginning of progtein
        if(auto s = profiler.find(current_progtein); s == profiler.end())
        {
            profiler[current_progtein] = {};
        }

        // init info in case of first time entering a progtein
        if(auto s = profiler[current_progtein].find(program_pointer);
            s == profiler[current_progtein].end())
        {
            profiler[current_progtein][current_progtein] = 0;
        }
        
        profiler[current_progtein][program_pointer]++;
    }

    void replication_info()
    {
        // init info in case of beginning of progtein replication
        if(auto s = replication_profiler.find(current_replicated_progtein);
            s == replication_profiler.end())
        {
            replication_profiler[current_replicated_progtein] = {};
        }

        // init info in case of first time entering a progtein
        if(auto s = replication_profiler[current_replicated_progtein].find(current_progtein);
            s == replication_profiler[current_replicated_progtein].end())
        {
            replication_profiler[current_replicated_progtein][current_progtein] = 0;
        }

        replication_profiler[current_replicated_progtein][current_progtein]++;
    }

    int get_previous_program_pointer() { return program_pointer_stop; }
    int get_previous_instr_counter() { return instr_counter_stop; }
};

#pragma once

#include <array>
#include <vector>
#include <functional>

#include "../../../../Utils/Constants.hpp"


class BiologicalDebugger
{
protected:
    bool _stop = false;

public:
    bool activated = false;
    std::vector<int> progteins_to_stop_at;
    int program_counter;
    int instr_counter;

    BiologicalDebugger()
    {
        progteins_to_stop_at = std::vector<int>{};
        reset();
    }

    void add_breakpoint_at_progtein(int progtein_nb)
    {
        for(size_t i=0; i<progteins_to_stop_at.size();i++)
            if (progteins_to_stop_at[i] == progtein_nb)
                return;
        
        progteins_to_stop_at.push_back(progtein_nb);
    }

    void check_line(std::array<int,SIZE_INSTR> line)
    {
        if(line[0] == 46)
        {
            for (size_t i=0; i<progteins_to_stop_at.size();i++)
            {
                if(line[2] == progteins_to_stop_at[i])
                {
                    _stop = true;
                }
            }
        }
    }

    void check(std::array<int,SIZE_INSTR> line, int program_counter, int instr_counter)
    {
        if(!activated)
            return;

        bool was_stopped = _stop;
        check_line(line);

        if (_stop && !was_stopped)
        {
            this->program_counter = program_counter;
            this->instr_counter = instr_counter;
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
        program_counter = 0;
        instr_counter = 0;
    }
};

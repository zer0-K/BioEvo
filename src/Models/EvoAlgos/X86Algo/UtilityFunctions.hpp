#pragma once

#include "EvoX.hpp"

bool evox_comp_genes(std::vector<int> genome_1, std::vector<int> genome_2)
{
    bool comp_vectors(std::vector<int>, std::vector<int>);

    // for the moment, genomes are only int vectors
    return comp_vectors(genome_1, genome_2);
}

bool x86_comp_code(std::vector<std::array<int, 3>> code_1, std::vector<std::array<int, 3>> code_2)
{
    if(code_1.size() != code_2.size())
    {
        return false;
    }

    for(int i=0; i<code_1.size();i++)
    {
        std::array<int, 3> instr_1 = code_1[i];
        std::array<int, 3> instr_2 = code_2[i];

        if(instr_1[0] != instr_2[0] || instr_1[1] != instr_2[1] 
            || instr_1[2] != instr_2[2])
        {
            return false;
        }
    }

    return true;
}

bool x86_comp_output(std::vector<int> out_1, std::vector<int> out_2)
{
    bool comp_vectors(std::vector<int>, std::vector<int>);

    // for the moment, outputs are just int vectors
    return comp_vectors(out_1, out_2);
}

bool comp_vectors(std::vector<int> v1, std::vector<int> v2)
{
    if(v1.size() != v2.size())
    {
        return false;
    }

    for(int i=0; i<v1.size();i++)
    {
        if(v1[i] != v2[i])
        {
            return false;
        }
    }

    return true;
}
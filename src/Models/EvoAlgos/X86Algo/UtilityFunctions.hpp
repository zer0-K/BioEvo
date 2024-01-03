#pragma once

#include "EvoX.hpp"
#include "InstructionMapping.hpp"

inline bool evox_comp_genes(std::vector<int> genome_1, std::vector<int> genome_2)
{
    bool comp_vectors(std::vector<int>, std::vector<int>);

    // for the moment, genomes are only int vectors
    return comp_vectors(genome_1, genome_2);
}

inline bool x86_comp_code(std::vector<std::array<int,SIZE_INSTR>> code_1, std::vector<std::array<int,SIZE_INSTR>> code_2)
{
    if(code_1.size() != code_2.size())
    {
        return false;
    }

    for(int i=0; i<code_1.size();i++)
    {
        std::array<int,SIZE_INSTR> instr_1 = code_1[i];
        std::array<int,SIZE_INSTR> instr_2 = code_2[i];

        if(instr_1[0] != instr_2[0] || instr_1[1] != instr_2[1] 
            || instr_1[2] != instr_2[2])
        {
            return false;
        }
    }

    return true;
}

inline bool x86_comp_output(std::vector<int> out_1, std::vector<int> out_2)
{
    bool comp_vectors(std::vector<int>, std::vector<int>);

    // for the moment, outputs are just int vectors
    return comp_vectors(out_1, out_2);
}

inline bool comp_vectors(std::vector<int> v1, std::vector<int> v2)
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

inline bool comp_flows(std::vector<std::array<int,2>> f1, std::vector<std::array<int,2>> f2)
{
    if(f1.size() != f2.size())
    {
        return false;
    }

    for(int i=0;i<f1.size();i++)
    {
        bool isin = false;
        for(int j=0;j<f2.size();j++)
        {
            if(f1[i][0] == f2[i][0] && f1[i][1] == f2[i][1])
            {
                isin = true;
                break;
            }
        }

        if(!isin)
        {
            return false;
        }
    }

    return true;
}

inline std::vector<int> get_func_IDs_in_genome(std::vector<int> genome)
{
    std::vector<int> func_IDs(0);

    // find funcs in genome
    for(int i=0;i<genome.size()/SIZE_INSTR;i++)
    {
        if(genome[7*i] == instruction::MARKER && genome[7*i+1] != -1)
        {
            // get func ID
            func_IDs.push_back(genome[7*i+2]);
        }
    }

    // remove duplicates
    std::vector<int> funcs_no_duplicates(0);
    for(int i=0;i<func_IDs.size();i++)
    {
        bool isin = false;
        for(int j=0;j<funcs_no_duplicates.size();j++)
        {
            if(func_IDs[i] == funcs_no_duplicates[j])
            {
                isin = true;
                break;
            }
        }

        if(!isin)
        {
            funcs_no_duplicates.push_back(func_IDs[i]);
        }
    }

    return funcs_no_duplicates;
}
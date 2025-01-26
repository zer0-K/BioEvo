#pragma once

#include <fstream>
#include <sstream>

#include "EvoX.hpp"
#include "InstructionMapping.hpp"

inline bool evox_comp_phenotypic_body(std::vector<int> phenotypic_body_1, std::vector<int> phenotypic_body_2)
{
    bool comp_vectors(std::vector<int>, std::vector<int>);

    // for the moment, phenotypic bodys are only int vectors
    return comp_vectors(phenotypic_body_1, phenotypic_body_2);
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

inline std::vector<int> get_func_IDs_in_phenotypic_body(std::vector<int> phenotypic_body)
{
    std::vector<int> func_IDs(0);

    // find funcs in phenotypic body
    for(int i=0;i<phenotypic_body.size()/SIZE_INSTR;i++)
    {
        if(phenotypic_body[7*i] == instruction::MARKER && phenotypic_body[7*i+1] != -1)
        {
            // get func ID
            func_IDs.push_back(phenotypic_body[7*i+2]);
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

inline void write_phenotypic_body_to_csv(std::vector<int> phenotypic_body, std::string file_name_relative)
{
    std::string file_name_absolute = project_folder + "data/" + file_name_relative;
    std::ofstream mfile;

    mfile.open(file_name_absolute, std::ios::out | std::ios::app);

    // iterate line by line
    for(int i=0;i<phenotypic_body.size()/SIZE_INSTR;i++)
    {
        mfile << phenotypic_body[SIZE_INSTR*i] << ",";

        for(int j=1;j<SIZE_INSTR; j++)
        {
            mfile << " " << phenotypic_body[SIZE_INSTR*i + j] << ",";
        }
        mfile << std::endl;
    }

    mfile.close();
}

/**
 * @brief read a csv encoding a phenotypic body
 *
 * @param file_name_relative file name in data/ folder
 */
inline std::vector<int> get_phenotypic_body_from_csv(std::string file_name_relative)
{
    // io file stream related variables
    std::string file_name_absolute = project_folder + "data/" + file_name_relative;
    std::ifstream mfile(file_name_absolute);
    std::string line;

    // phenotypic body to get
    std::vector<int> phenotypic_body(0);

    if(mfile.is_open())
    {
        while( std::getline(mfile, line) )
        {
            std::string val;
            std::stringstream s(line);
            // parse line into numbers
            while (getline (s, val, ','))
                if(val != " ")
                    phenotypic_body.push_back(std::stoi(val));

        }
        mfile.close();
    }
    else
    {
        std::cout << "Unable to open following file : data/" << file_name_relative
                << std::endl;
    }

    return phenotypic_body;
}
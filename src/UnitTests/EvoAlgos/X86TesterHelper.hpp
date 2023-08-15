#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

class X86TesterHelper
{
private:
    sp_x86algo algo;

    std::string unit_test_name;

    std::vector<std::string> test_names;
    std::vector<std::vector<std::array<int,SIZE_INSTR>>> test_codes;
    std::vector<std::vector<int>> test_inputs;
    std::vector<std::vector<int>> expected_outputs;

    X86TesterHelper(std::string unit_test_name)
    {
        algo = std::make_shared<X86Algo>("algo");

        test_names = std::vector<std::string>(0);
        test_codes = std::vector<std::vector<std::array<int,SIZE_INSTR>>>(0);
        test_inputs = std::vector<std::vector<int>>(0);
        expected_outputs = std::vector<std::vector<int>>(0);
    }
    
public:
    void add_test(std::string test_name, std::vector<std::array<int,SIZE_INSTR>> test_code,
        std::vector<int> test_input, std::vector<int> expected_output)
    {
        test_names.push_back(test_name);
        test_codes.push_back(test_code);
        test_inputs.push_back(test_input);
        expected_outputs.push_back(expected_output);
    }

    bool run()
    {
        bool is_passed = true;

        for(int i=0;i<test_names.size();i++)
        {
            algo->init();

            algo->set_code(test_codes[i], 0);
            algo->set_input(test_inputs[i]);
            algo->set_output_size(expected_outputs.size());

            // execute
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto res = algo->get_output();

            bool is_passed_i = expected_outputs[i].size() == res.size();

            if(is_passed_i)
            {
                for(int j=0;j<expected_outputs[i].size();j++)
                {
                    is_passed_i &= expected_outputs[i][j] == res[j];
                }
            }
            
            std::cout << unit_test_name << " - " << test_names[i] << " :";
            passed_print(is_passed_i);
            
            is_passed &= is_passed_i;

            if(!is_passed_i)
            {
                std::string exp_out_str = "{ " + std::to_string(expected_outputs[i][0]);
                for(int j=1;j<expected_outputs[i].size();j++)
                {
                    exp_out_str += ", " + std::to_string(expected_outputs[i][j]);
                }
                exp_out_str += " }";

                std::string curr_out_str = "{ " + std::to_string(res[0]);
                for(int j=1;j<res.size();j++)
                {
                    curr_out_str += ", " + std::to_string(res[j]);
                }
                curr_out_str += " }";


                std::cout << "\tError : expected output : " 
                          << "\t\t" << exp_out_str << std::endl;
                std::cout << "\tError : current output : "
                          << "\t\t" << curr_out_str << std::endl;
            }
        }

        std::cout << unit_test_name << " :";
        passed_print(is_passed);

        return is_passed;
    }
};

typedef std::shared_ptr<X86TesterHelper> sp_ut_helper_x86;

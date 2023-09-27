#include "FunctionExecutionEvoX.hpp"

#include "../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
//#include "../../../../Utils/Functions.hpp"
//#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

FunctionExecutionEvoX::FunctionExecutionEvoX()
    :Experiment::Experiment(name_exp_classical_info_func_exec_evox)
{
    init();
}

void FunctionExecutionEvoX::init()
{

}

void FunctionExecutionEvoX::launch()
{
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();

    //---------- GENOME

    // genomes coding simple programs
    // 
    // insert args as genes
    std::vector<int> genome_1 { 
        instruction::CPYIN, 0, 0, 0, 1, 0, 0,       // 0
        instruction::CPYIS, 0, 0, 0, 10, 0, 0,      // 1 (input size) 
        // build 28
        instruction::INC, 0, 0, 0, 2, 0, 0,         // 2 (d[2] = 1)
        instruction::ADD, 0, 0, 0, 2, 2, 2,         // 3 (d[2] = 2)
        instruction::ADD, 0, 0, 0, 2, 2, 2,         // 4 (d[2] = 4)
        instruction::CPY, 0, 0, 0, 6, 2, 0,         // 5 
        instruction::ADD, 0, 0, 0, 2, 2, 2,         // 6 (d[2] = 8)
        instruction::CPY, 0, 0, 0, 7, 2, 0,         // 7 
        instruction::ADD, 0, 0, 0, 2, 2, 2,         // 8 (d[2] = 16)
        instruction::ADD, 0, 0, 0, 2, 2, 6,         // 9 (d[2] = 20)
        instruction::ADD, 0, 0, 0, 2, 2, 7,         // 10 (d[2] = 28)
        // build other constants
        // iteration vars at 100+
        instruction::DEC, 0, 0, 0, 25, 0, 0,        // 11 (i: halt in)
        instruction::DEC, 0, 0, 0, 26, 0, 0,        // 12 (j: halt genes)
        instruction::DEC, 0, 0, 0, 27, 0, 0,        // 13 (k: marker)
        // for jumps
        instruction::INC, 0, 0, 0, 4, 0, 0,         // 14
        instruction::INC, 0, 0, 0, 4, 0, 0,         // 15 (d[4]=2)
        instruction::INC, 0, 0, 0, 5, 0, 0,         // 16
        instruction::INC, 0, 0, 0, 5, 0, 0,         // 17
        instruction::INC, 0, 0, 0, 5, 0, 0,         // 18 (d[5]=3)
        // MARKER
        instruction::ADD, 0, 0, 0, 3, 2, 7,         // 19
        instruction::ADD, 0, 0, 0, 3, 3, 6,         // 20 (d[3] = 40 also : jump at end)
        instruction::INC, 0, 0, 0, 6, 0, 0,         // 21
        instruction::INC, 0, 0, 0, 6, 0, 0,         // 22 (d[6]=6)
        // check BEGIN
        instruction::JRE, 0, 0, 0, 5, 1, 2,         // 23
        instruction::JRA, 0, 0, 0, 3, 0, 0,         // 24
        instruction::XXX, 0, 0, 0, 0, 0, 0,         // 25
        instruction::INC, 0, 0, 0, 2, 0, 0,         // 26 (d[2] = 29)
        //
        instruction::DEC, 0, 0, 0, 10, 0, 0,        // 27 (in.size()-1)
        // find first halt in input
        instruction::INC, 0, 0, 0, 25, 0, 0,        // 28 (i++)
        instruction::CPYIN, 0, 1, 0, 11, 25, 0,     // 29 (in[i])
        instruction::CMP, 0, 0, 0, 30, 11, 2,       // 30 (in[i]==halt)
        instruction::CMP, 0, 0, 0, 31, 11, 10,      // 31 (in[i]==in.size())
        instruction::MUL, 0, 0, 0, 30, 30, 31,      // 32 (OR)
        instruction::JRE, 0, 0, 0, 4, 30, 0,        // 33
        instruction::JRS, 0, 0, 0, 6, 0, 0,         // 34
        instruction::CPY, 0, 0, 0, 15, 25, 0,       // 35
        instruction::DEC, 0, 0, 0, 15, 0, 0,        // 36 (pos before in halt)
        instruction::INC, 0, 0, 0, 6, 0, 0,         // 37 (d[6]=7)
        // find first halt of genes
        instruction::INC, 0, 0, 0, 26, 0, 0,        // 38 (i++)
        instruction::GR, 0, 1, 0, 14, 26, 0,        // 39
        instruction::JRE, 0, 0, 0, 4, 14, 2,        // 40
        instruction::JRS, 0, 0, 0, 5, 0, 0,         // 41
        instruction::CPY, 0, 0, 0, 17, 26, 0,       // 42
        instruction::ADD, 0, 0, 0, 17, 17, 6,       // 43 (pos just after gene halt)
        // get pos of first marker
        instruction::INC, 0, 0, 0, 27, 0, 0,        // 44 
        instruction::GR, 0, 1, 0, 14, 27, 0,        // 45
        instruction::JRE, 0, 0, 0, 4, 14, 3,        // 46
        instruction::JRS, 0, 0, 0, 5, 0, 0,         // 47
        instruction::CPY, 0, 0, 0, 20, 26, 0,       // 48
        // get val of first marker
        instruction::INC, 0, 0, 0, 20, 0, 0,        // 49 
        instruction::GR, 0, 1, 0, 22, 20, 0,        // 50 (d[22]=marker val)
        // copy input 
        instruction::CPY, 0, 0, 0, 31, 3, 0,        // 51
        instruction::CPY, 0, 0, 0, 30, 3, 0,        // 52
        instruction::CPY, 0, 0, 0, 28, 6, 0,        // 53
        instruction::DEC, 0, 0, 0, 31, 0, 0,        // 54
        instruction::DEC, 0, 0, 0, 28, 0, 0,        // 55
        instruction::INC, 0, 0, 0, 5, 0, 0,         // 56
        instruction::INC, 0, 0, 0, 28, 0, 0,        // 57
        instruction::INC, 0, 0, 0, 31, 0, 0,        // 58
        instruction::CPYIN, 1, 1, 0, 31, 28, 0,     // 59
        instruction::JRE, 0, 0, 0, 4, 28, 15,       // 60
        instruction::JRS, 0, 0, 0, 5, 0, 0,         // 61
        instruction::GCPYM, 1, 1, 1, 22, 30, 31,    // 62
        // create new marker
        instruction::CPY, 0, 0, 0, 23, 22, 0,       // 63
        instruction::INC, 0, 0, 0, 23, 0, 0,        // 64
        instruction::GINS, 1, 0, 0, 17, 0, 0,       // 65 insert 7th gene : 0
        instruction::GINS, 1, 0, 0, 17, 0, 0,       // 66 insert 6th gene : 0
        instruction::GINS, 1, 0, 0, 17, 0, 0,       // 67 insert 5th gene : 0
        instruction::GINS, 1, 0, 0, 17, 0, 0,       // 68 insert 4th gene : 0
        instruction::GINS, 1, 0, 0, 17, 0, 0,       // 69 insert 3rd gene : 0
        instruction::GINS, 1, 0, 0, 17, 23, 0,      // 70 insert 2nd gene : ID
        instruction::GINS, 1, 0, 0, 17, 3, 0,       // 71 insert 1st gene : MARKER
        instruction::HALT, 0, 0, 0, 0, 0, 0,        // 72
        instruction::MARKER, 0, 0, 0, 0, 0, 0       // 73
    };
    /*
        0-1 : dummy input (as 'template'), useless here
        2-11 : create the number 29 (and save other numbers)
        12-15 : builds some variables for jumps (loops)
        16-19 :first loop : identify length of the genome
        15-24 : builds some vars for the next loop, and change output size
        25-29 : second loop (copying genome into output)
        17 : end


        c 3650
    */

    std::vector<std::vector<int>> genomes {
        genome_1
    };

    //---------- INPUTS

    // input (here, same for all tests for simplicity)
    std::vector<int> input_1_1 {
        instruction::BEG, 0, 0, 0, 0, 0, 0,
        instruction::MOV, 1, 1, 1, 1, 1, 1,
        instruction::HALT, 0, 0, 0, 0, 0, 0
    };

    std::vector<std::vector<int>> inputs_1 {
        input_1_1
    };

    std::vector<std::vector<std::vector<int>>> inputs {
        inputs_1
    };

       
    //---------- EXECUTE

    // set genome and execute
    algo->set_genes(genomes[0]);

    algo->set_input(inputs[0][0]);
    algo->exec(std::vector<sp_entity>(0));

    // compare genes
    auto genes = algo->get_genes();
    for(int i=0;i<genes.size();i++)
    {
        if(i<genome_1.size())
        {
            if(genes[i] != genome_1[i])
            {
                std::cout << "Difference at " 
                    << i << " : old genome : "
                    << genome_1[i] << ", new : " << genes[i]
                    << std::endl;
            }
        }
        else
        {
            std::cout << "Added genome at " << i << " : "
                << genes[i] << std::endl;  
        }
    }

    // get result
    auto out_res = algo->get_output();

    std::cout << "Output of function execution : " << std::endl;
    for(int i=0; i<out_res.size();i++)
    {
        std::cout << out_res[i] << " ";
    }
    std::cout << std::endl;
}

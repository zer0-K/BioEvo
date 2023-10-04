#include "ReplicationEvoXQuine.hpp"

#include "../../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../../Utils/Functions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

ReplicationEvoXQuine::ReplicationEvoXQuine()
    :Experiment::Experiment(name_exp_bioevo_replication_evox_quine)
{
    init();
}

void ReplicationEvoXQuine::init()
{

}

void ReplicationEvoXQuine::launch()
{
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();

    //---------- GENOME

    // genomes for a simple quine
    // 
    std::vector<int> genome_1 { 
            instruction::SUB, 1, 1, 0, 10, 10, 7,
            instruction::ADD, 1, 1, 0, 10, 10, 7,
            instruction::GR, 1, 2, 0, 0, 10, 0,
            instruction::JRE, 0, 0, 1, 2, instruction::HALT, 0,
            instruction::JRS, 0, 0, 0, 3, 0, 0,     // 19
            instruction::ADD, 1, 1, 0, 10, 10, 7,
            instruction::SETOS, 1, 0, 0, 10, 0, 0,   // 23
            instruction::DEC, 1, 0, 0, 11, 0, 0,     // 24 
            instruction::INC, 1, 0, 0, 11, 0, 0,     // 25
            instruction::GR, 1, 2, 0, 0, 11, 0,      // 26
            instruction::CPYOUT, 2, 1, 0, 11, 0, 0,  // 27
            instruction::JRE, 0, 1, 1, 2, 10, 11,     // 28
            instruction::JRS, 0, 0, 0, 4, 0, 0,     // 29
            instruction::HALT, 0, 0, 0, 0, 0, 0     // 30
   };
    /*
        0-1 : dummy input (as 'template'), useless here
        2-11 : creates the number 29 (and save other numbers)
        12-15 : builds some variables for jumps (loops)
        16-19 :first loop : identify length of the genome
        20-24 : builds some vars for the next loop, and change output size
        25-20 : second loop (copying genome into output)
        30 : end
    */

    std::vector<std::vector<int>> genomes {
        genome_1
    };

    //---------- INPUTS

    // input (here, same for all tests for simplicity)
    std::vector<int> input_1_1 {
        0, 0
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

    // get result
    auto out_res = algo->get_output();

    std::cout << "Output of quine : " << std::endl;
    for(int i=0; i<out_res.size();i++)
    {
        std::cout << out_res[i] << " ";
    }
    std::cout << std::endl;
}

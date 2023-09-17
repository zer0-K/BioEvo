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

    // genomes coding simple programs
    // 
    // insert args as genes
    std::vector<int> genome_1 { 
        instruction::CPYIN, 0, 0, 0, 0, 0, 0,   // 0
        instruction::CPYIN, 0, 0, 0, 1, 1, 0,   // 1
        instruction::INC, 0, 0, 0, 2, 0, 0,     // 2 (d[2] = 1)
        instruction::ADD, 0, 0, 0, 2, 2, 2,     // 3 (d[2] = 2)
        instruction::ADD, 0, 0, 0, 2, 2, 2,     // 4 (d[2] = 4)
        instruction::CPY, 0, 0, 0, 3, 2, 0,     // 5 (d[3] = 4)
        instruction::ADD, 0, 0, 0, 2, 2, 2,     // 6 (d[2] = 8)
        instruction::CPY, 0, 0, 0, 4, 2, 0,     // 7 (d[4] = 8)
        instruction::ADD, 0, 0, 0, 2, 2, 2,     // 8 (d[2] = 16)
        instruction::ADD, 0, 0, 0, 2, 2, 3,     // 9 (d[2] = 20)
        instruction::ADD, 0, 0, 0, 2, 2, 4,     // 10 (d[2] = 28)
        instruction::DEC, 0, 0, 0, 3, 0, 0,     // 11 (d[3] = 3)
        instruction::INC, 0, 0, 0, 6, 0, 0,     // 12 (d[6] = 1)
        instruction::INC, 0, 0, 0, 6, 0, 0,     // 13 (d[6] = 2)
        instruction::DEC, 0, 0, 0, 7, 0, 0,     // 14 (d[7] = -1)
        instruction::INC, 0, 0, 0, 7, 0, 0,     // 15 (d[7]++ (i))
        instruction::GR, 0, 1, 0, 5, 7, 0,      // 16 (d[5] = gene at i)
        instruction::JRE, 0, 0, 0, 6, 2, 5,     // 17
        instruction::JRS, 0, 0, 0, 3, 0, 0,     // 18
        instruction::ADD, 0, 0, 0, 7, 7, 4,     // 19
        instruction::DEC, 0, 0, 0, 7, 0, 0,     // 20
        instruction::DEC, 0, 0, 0, 8, 0, 0,     // 21 (j)
        instruction::SETOS, 0, 0, 0, 7, 0, 0,   // 22
        instruction::INC, 0, 0, 0, 3, 0, 0,     // 23 (d[3] = 4)
        instruction::INC, 0, 0, 0, 8, 0, 0,     // 24
        instruction::GR, 0, 1, 0, 5, 8, 0,      // 25
        instruction::CPYOUT, 1, 0, 0, 8, 5, 0,  // 26
        instruction::JRE, 0, 0, 0, 6, 7, 8,     // 27
        instruction::JRS, 0, 0, 0, 3, 0, 0,     // 28
        instruction::HALT, 0, 0, 0, 0, 0, 0     // 29
    };
    /*
    i=0, while gene_at(i) != HALT (28) : i+=1
    when while stops : gene_at(i) == HALT
    store i in d1
    --------> first, generate 28
    --------> compare gene at i and 28
    --------> jump at previous (incrementation instr) if not equal

    set output size = i+6 (the 6 at the end are 0s)
    loop again from 0 to d1
    copy gene at i to output
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
}
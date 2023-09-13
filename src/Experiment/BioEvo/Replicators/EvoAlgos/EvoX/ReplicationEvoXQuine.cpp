#include "ReplicationEvoXQuine.hpp"

#include "../../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
//#include "../../../../../Utils/Functions.hpp"
//#include "../../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
//#include "../../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

//#include "../../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

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
    //sp_evox algo = std::make_shared<EvoX>("evox algo");
    //algo->init();

    //---------- GENOME

    // genomes coding simple programs
    // 
    // insert args as genes
    std::vector<int> genome_1 { 
    //    instruction::CPYIN, 0, 0, 0, 0, 0, 0,   // 0
    //    instruction::CPYIN, 0, 0, 0, 1, 1, 0,   // 1
    //    instruction::GINS, 0, 0, 0, 3, 0, 0,    // 13 insert 1st gene arg at 0
    //    instruction::CPYOUT, 0, 0, 0, 0, 7, 0   // 14 copy val at 4
    };

    std::vector<std::vector<int>> genomes {
        genome_1
    };

    //---------- INPUTS

    // input (here, same for all tests for simplicity)
    std::vector<int> input_1_1 {
    //    instruction::INC, 0, 0, 0, 7, 0, 0
    };

    std::vector<std::vector<int>> inputs_1 {
        input_1_1
    };

    std::vector<std::vector<std::vector<int>>> inputs {
        inputs_1
    };

       
    //---------- EXECUTE

    // set genome and execute
    //algo->set_genes(genomes[0]);
    //algo->reset_data();

    //algo->set_input(inputs[0][0]);
    //algo->exec(std::vector<sp_entity>(0));

    // get result
    //auto out_res = algo->get_output();
}

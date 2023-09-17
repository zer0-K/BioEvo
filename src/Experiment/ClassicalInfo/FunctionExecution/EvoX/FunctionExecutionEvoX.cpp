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
       instruction::HALT, 0, 0, 0, 0, 0, 0     // 29
    };
    /*
 
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

    std::cout << "Output of function execution : " << std::endl;
    for(int i=0; i<out_res.size();i++)
    {
        std::cout << out_res[i] << " ";
    }
    std::cout << std::endl;
}

#include "EvoXDriveTrait.hpp"

#include "../../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../../Utils/Functions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

EvoXDriveTrait::EvoXDriveTrait()
    :Experiment::Experiment(name_exp_bioevo_traits_evox)
{
    init();
}

void EvoXDriveTrait::init()
{

}

void EvoXDriveTrait::launch()
{
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();

    //---------- GENOME

    // genome for an ranom gene mutation
    // 
    // code template comes from FunctionExecutionEvoX
    std::vector<int> genome_1 { 
        instruction::JMP, 0, 0, 0, 25, 0, 0,    // skip meta-exec func

    //----- exec fct with given id
        // args :
        //      1 - func id
        instruction::MARKER, 0, 0, 0, 0, 0, 0,
        
        // find marker with given id
        instruction::CPY, 1, 2, 1, 100, 99, 0,  // get arg 1 from stack
        instruction::CPY, 1, 0, 0, 110, -7, 0,
        instruction::ADD, 1, 1, 0, 110, 110, 7,
        instruction::GR, 1, 2, 0, 101, 110, 0,
        instruction::JRE, 0, 1, 0, 2, 101, instruction::MARKER, // marker found
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        // check func id
        instruction::ADD, 1, 1, 0, 110, 110, 2,
        instruction::GR, 1, 2, 0, 101, 110, 0,
        instruction::JRE, 0, 1, 1, 3, 101, 100,
        instruction::SUB, 1, 1, 0, 110, 110, 2,
        instruction::JRS, 0, 0, 0, 8, 0, 0,

        // update data stack (args of func to exec are just before the func id)
        instruction::DEC, 1, 0, 0, 99, 0, 0,

        // set prog ptr for exec
        instruction::DIV, 1, 1, 0, 110, 110, 7,
        instruction::INC, 1, 0, 0, 0, 0, 0,
        instruction::GPTR, 2, 0, 0, 0, 0, 0,    // update prog ptr stack
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 1, 0, 0, 110, 0, 0,

        // clean the stacks
        instruction::DEC, 1, 0, 0, 0, 0, 0,     // update prog ptr stack
        instruction::CPY, 1, 2, 0, 103, 0, 0,
        instruction::DEC, 1, 0, 0, 0, 0, 0,
        instruction::JMP, 1, 0, 0, 103, 0, 0,

        instruction::MARKER, 0, 0, 0, 0, 0, 0,

    //----- main func
        instruction::MARKER, 0, 1, 0, 0, 0, 0,

        instruction::CPY, 1, 0, 0, 99, 130, 0,  // data stack begins at 130
        // call muti-level exec func
        instruction::CPY, 2, 0, 0, 99, 2, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func 
        // end
        instruction::HALT, 0, 0, 0, 0, 0, 0,

        instruction::MARKER, 0, 1, 0, 0, 0, 0,

    //----- function 'main' calls
        instruction::MARKER, 0, 2, 0, 0, 0, 0,

        // call func 1
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 3, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        // arg1 = return of func 1, build arg2 (arg2 = 4)
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 4, 0,
        // call func 2
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 4, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,    // prepare exec of func
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        // call func 3
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 5, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,    // prepare exec of func
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
 
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 2, 0, 0, 0, 0,
 

    //----- first func : get input
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        instruction::CPYIN, 1, 1, 0, 100, 0, 0,     // get input value
        instruction::INC, 1, 0, 0, 99, 0, 0,        // increment stack for return value
        instruction::CPY, 2, 1, 0, 99, 100, 0,      // store return value at top of stack +1

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 3, 0, 0, 0, 0,
 
     //----- second func : return = arg1 + arg2
        instruction::MARKER, 0, 4, 0, 0, 0, 0,

        instruction::CPY, 1, 2, 0, 100, 99, 0,        
        instruction::DEC, 1, 0, 0, 99, 0, 0,        // remove second arg from stack
        instruction::ADD, 2, 2, 1, 99, 99, 100,     // return = arg1 + arg2

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 4, 0, 0, 0, 0,
 
     //----- third func : copy arg to output
        instruction::MARKER, 0, 5, 0, 0, 0, 0,

        instruction::CPYOUT, 1, 2, 0, 0, 99, 0,     // copy arg to out

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 5, 0, 0, 0, 0 
    };



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


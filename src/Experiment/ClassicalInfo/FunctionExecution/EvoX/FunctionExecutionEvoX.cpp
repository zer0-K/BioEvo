#include "FunctionExecutionEvoX.hpp"

#include "../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../Utils/Functions.hpp"
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

    /*
     * stack-based function executer
     * Execute functions between two markers by moving prog ptr
     * Maybe not be able to call a exec inside a function called by exec
     * 
     * prog ptr stack : at 0
     * data stack ptr : 99
     * data stack pos : 1000
     *
     * !! the return value of a func is stored at top of the data stack+1 !!
     *
     * When executing a func :
     *  1 - push the arguments on the data stack
     *  2 - just before executing the function, push the prog ptr to prog ptr stack
     *  3 - execute the function
     *  4 - remove the func arg from the data stack
     *  5 - push the return addr to the data stack
     *  6 - reset the prog ptr to last one in prog ptr stack
     */
    std::vector<int> genome_simple {
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
        instruction::CPY, 2, 0, 0, 99, 2, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 1, 0, 0, 1, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        instruction::HALT, 0, 0, 0, 0, 0, 0,

        instruction::MARKER, 0, 1, 0, 0, 0, 0,

    //----- first func : no arg
        instruction::MARKER, 0, 2, 0, 0, 0, 0,

        instruction::CPYOUT, 1, 0, 0, 0, 667, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 2, 0, 0, 0, 0
    };

    /**
     * multi-level exec : function call inside function call
     */
    std::vector<int> genome_multilevel {
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
        genome_simple, genome_multilevel
    };


    //---------- INPUTS

    std::vector<int> input_1_1 {};

    std::vector<std::vector<int>> inputs_1 {
        input_1_1
    };

    std::vector<int> input_2_1 { 30 };
    std::vector<int> input_2_2 { 99 };
    std::vector<int> input_2_3 { 271828 };

    std::vector<std::vector<int>> inputs_2 {
        input_2_1, input_2_2, input_2_3
    };


    std::vector<std::vector<std::vector<int>>> inputs {
        inputs_1, inputs_2
    };

       
    //---------- EXECUTE

    for(int i=0;i<genomes.size();i++)
    {
        // set genome and execute
        algo->set_output_size(1);
        algo->set_genes(genomes[i]);
        algo->reset_data();

        for(int j=0;j<inputs[i].size();j++)
        {
            algo->set_input(inputs[i][j]);
            algo->exec(std::vector<sp_entity>(0));

            // get result
            auto out_res = algo->get_output();

            std::cout << "Output of function execution (genome " 
                << i << ", input : " << to_str(inputs[i][j]) << ") : " 
                << std::endl
                << to_str(out_res) << std::endl;
        }

    }

}

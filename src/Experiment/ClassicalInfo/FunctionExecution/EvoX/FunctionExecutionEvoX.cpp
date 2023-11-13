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

    /*
     * stack-based fucntion executer
     * Execute functions between two markers by moving prog ptr
     * Might not be able to call a exec inside a function called by exec
     * 
     * prog ptr stack : at 0
     * data stack ptr : 99
     * data stack pos : 1000 ?
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
        instruction::DEC, 2, 0, 0, 99, 0, 0,

        // set prog ptr for exec
        instruction::DIV, 1, 1, 0, 110, 110, 7,
        instruction::INC, 1, 0, 0, 0, 0, 0,
        instruction::GPTR, 2, 0, 0, 0, 0, 0,    // update prog ptr stack
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 1, 0, 0, 110, 0, 0,

        // clean the stacks
        instruction::DEC, 1, 0, 0, 0, 0, 0,     // update prog ptr stack
        instruction::CPY, 1, 0, 0, 103, 0, 0,
        instruction::DEC, 1, 0, 0, 0, 0, 0,
        instruction::JMP, 1, 0, 0, 103, 0, 0,

        instruction::MARKER, 0, 0, 0, 0, 0, 0,

    //----- main func
        instruction::MARKER, 0, 1, 0, 0, 0, 0,

        instruction::CPY, 1, 0, 0, 99, 1000, 0,  // data stack begins at 100
        instruction::CPY, 2, 0, 0, 99, 2, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 1, 0, 0, 1, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 2,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        instruction::HALT, 0, 0, 0, 0, 0, 0,

        instruction::MARKER, 0, 1, 0, 0, 0, 0,

    //----- first func : no arg
        instruction::MARKER, 0, 2, 0, 0, 0, 0,

        instruction::CPYOUT, 1, 0, 0, 0, 667, 0,

        instruction::MARKER, 0, 2, 0, 0, 0, 0
    };

    std::vector<int> genome_temp {
        instruction::JMP, 0, 0, 0, 21, 0, 0,    // skip meta-exec func (from 1 to 26 (with markers))
    //----- meta exec function : execute a whole function (between two markers)
        // args :
        //      1 - func id
        //      2 - type of exec : 0 - all at once, 1 : one by one
        instruction::MARKER, 2, 0, 0, 0, 0, 0,

        // get the arg pos
        instruction::CPY, 1, 1, 0, 5, 0, 0,
        // get the marker of the function to execute, and the exec type
        instruction::CPY, 1, 1, 0, 1, 5, 0, 
        instruction::INC, 1, 0, 0, 5, 0, 0,
        instruction::CPY, 1, 1, 0, 6, 5, 0, 
        // find the corresponding marker positions in genome
        instruction::CPY, 1, 0, 0, 10, -7, 0,   // pos in genome (%7)
        instruction::CPY, 1, 0, 0, 11, 0, 0,    // to handle beg/end of func to find 
        instruction::ADD, 1, 0, 0, 10, 7, 0,
        instruction::GR, 1, 2, 0, 12, 10, 0,    // get instr type 
        instruction::JRE, 0, 1, 0, 2, 12, instruction::MARKER,  // ensure we are reading a marker
        instruction::JRS, 0, 0, 0, 3, 0, 0, 
        instruction::ADD, 1, 1, 0, 13, 12, 2,
        instruction::GR, 1, 2, 0, 2, 13, 0,     // get marker id
        instruction::JRE, 0, 1, 1, 2, 1, 2,     // ensure marker id 
        instruction::JRS, 0, 0, 0, 7, 0, 0,
        instruction::JRE, 0, 1, 0, 3, 11, 1,    // ensure begin/end 
        instruction::CPY, 1, 1, 0, 3, 10, 0,    // save begin pos at 3
        instruction::JRS, 0, 0, 0, 10, 0, 0,
        instruction::CPY, 1, 1, 0, 4, 10, 0,    // save end pos at 4
        // exec function (select type)
        instruction::JRE, 0, 1, 0, 3, 6, 1,     // if arg1==1, exec one line by one line
        // execute the whole function
        instruction::SUB, 1, 1, 1, 12, 4, 3,    // get func size (+1, fencepost count)
        instruction::EXEC, 1, 1, 0, 3, 12, 0,   // execute the marker (fencepost compensated)
        instruction::JRA, 0, 0, 0, 4, 0, 0, // skip one by one exec
        // execute one by one the lines
        instruction::INC, 1, 0, 0, 3, 0, 0,
        instruction::EXEC, 1, 0, 0, 3, 1, 0,
        instruction::JRL, 0, 1, 1, -2, 3, 4, 

        instruction::MARKER, 2, 0, 0, 0, 0, 0,

    //----- while loop
        instruction::MARKER, 0, -2, 0, 0, 0, 0,

        instruction::HALT, 0, 0, 0, 0, 0, 0, 0,

        instruction::MARKER, 0, -2, 0, 0, 0, 0,


    //----- main program (entry point)
        instruction::MARKER, 1, -1, 0, 0, 0, 0,



        instruction::MARKER, 1, -1, 0, 0, 0, 0,


    //----- function 1 : mov input to data
        instruction::MARKER, 2, 1, 0, 0, 0, 0,



        instruction::MARKER, 2, 1, 0, 0, 0, 0,

    //----- function 2 : add
        instruction::MARKER, 2, 2, 0, 0, 0, 0,



        instruction::MARKER, 2, 2, 0, 0, 0, 0,

    //----- function 3 : mov data to output
        instruction::MARKER, 2, 3, 0, 0, 0, 0,



        instruction::MARKER, 2, 3, 0, 0, 0, 0,


        instruction::MARKER, -1, 0, 0, 0, 0, 0,  // end of genome
    };


    /*
     * Complex function executer
     * Can call the meta-exec inside a function called by meta-exec
     */
    std::vector<int> genome_complex { 

    };


    std::vector<std::vector<int>> genomes {
        genome_simple
    };

    //---------- INPUTS

    // input
    std::vector<int> input_1_1 {
    };

    std::vector<std::vector<int>> inputs_1 {
        input_1_1
    };

    std::vector<std::vector<std::vector<int>>> inputs {
        inputs_1
    };

       
    //---------- EXECUTE

    // set genome and execute
    algo->set_output_size(1);
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

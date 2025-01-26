#include "ReplicationEvoXQuine.hpp"

#include "../../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../../Utils/Functions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/FreeMolecules.hpp"

#include "../../../../../Entities/EntityVoid.hpp"
#include "../../../../../Entities/EntityInt.hpp"

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

    //simple_quine(algo);
    //quine_function_trigger(algo);
    finding_empty_place(algo);
}

void ReplicationEvoXQuine::simple_quine(sp_evox algo)
{
    std::cout << "Simple quine experiment running" << std::endl << std::endl;

    //---------- PHENOTYPIC BODY

    // phenotypic body for a simple quine
    // 
    std::vector<int> phenotypic_body { 
        instruction::SUB, 1, 1, 0, 10, 10, 7,
        instruction::ADD, 1, 1, 0, 10, 10, 7,
        instruction::GR, 1, 2, 0, 0, 10, 0,
        instruction::JRE, 0, 0, 1, 2, instruction::HALT, 0,
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        instruction::ADD, 1, 1, 0, 10, 10, 7,       
        instruction::SETOS, 1, 0, 0, 10, 0, 0,
        instruction::DEC, 1, 0, 0, 11, 0, 0, 
        instruction::INC, 1, 0, 0, 11, 0, 0,
        instruction::GR, 1, 2, 0, 0, 11, 0,
        instruction::CPYOUT, 2, 1, 0, 11, 0, 0,
        instruction::JRE, 0, 1, 1, 2, 10, 11,
        instruction::JRS, 0, 0, 0, 4, 0, 0,
        instruction::HALT, 0, 0, 0, 0, 0, 0
   };

    //---------- INPUTS

    // input (here, same for all tests for simplicity)
    std::vector<int> input {
        0, 0
    };

    //---------- EXECUTE

    algo->reset_data();

    // set phenotypic body and execute
    algo->set_phenotypic_body(phenotypic_body);

    algo->set_input(input);
    algo->exec(std::vector<sp_entity>(0));

    // get result
    auto out_res = algo->get_output();

    std::cout << "Output of quine : " << std::endl;
    for(int i=0; i<out_res.size();i++)
        std::cout << out_res[i] << " ";
    std::cout << std::endl;

    std::cout << std::endl << "Output == phenotypic body : " << x86_comp_output(out_res, phenotypic_body)
        << std::endl
        << "Simple quine experiment done" 
        << std::endl << std::endl;
}


void ReplicationEvoXQuine::quine_function_trigger(sp_evox algo)
{
    std::cout << "Quine replication trigger experiment running"
        << std::endl << std::endl;

    //---------- PHENOTYPIC BODY

    // phenotypic body for a simple quine
    // 
    std::vector<int> phenotypic_body { 
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

        instruction::JRGE, 0, 1, 0, 3, 149, 1,
        instruction::CPY, 1, 0, 0, 149, 1, 0,
        instruction::CPY, 1, 0, 0, 99, 150, 0,  // data stack begins at 150
        // clean output
        instruction::SETOS, 0, 0, 0, 0, 0, 0,
        // call muti-level exec func
        instruction::INC, 1, 0, 0, 99, 0, 0,
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

        // replicate only if phase flag==2
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPYIS, 2, 0, 0, 99, 0, 0,  // store input size at top of of stack
        instruction::JRG, 0, 2, 0, 2, 99, 1,    // HALT if input size < 2
        instruction::HALT, 0, 0, 0, 0, 0, 0,
        instruction::CPYIN, 2, 1, 0, 99, 0, 0,  // store phase flag at top of stack
        instruction::JRE, 0, 2, 0, 2, 99, 2,    // HALT if phase is not replication (phase==2)
        instruction::HALT, 0, 0, 0, 0, 0, 0,
        // call replication function
        instruction::CPY, 2, 0, 0, 99, 3, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 2, 0, 0, 0, 0,
 

    //----- replication func : output = phenotypic body
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        // find end of phenotypic body
        instruction::XXX, 0, 0, 0, 0, 0, 0,
        instruction::CPY, 1, 0, 0, 100, -7, 0,
        instruction::ADD, 1, 1, 0, 100, 100, 7,
        instruction::GR, 1, 2, 0, 101, 100, 0,
        instruction::JRE, 0, 0, 1, 2, instruction::MARKER, 101, // check if we are on a marker
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::GR, 1, 2, 0, 101, 100, 0,
        instruction::DEC, 1, 0, 0, 100, 0, 0,
        instruction::JRE, 0, 0, 1, 2, -1, 101,  // check that marker ID is -1
        instruction::JRS, 0, 0, 0, 8, 0, 0,
        instruction::ADD, 1, 1, 0, 100, 100, 7, // end of phenotypic body
        instruction::SETOS, 1, 0, 0, 100, 0, 0, // output size = phenotypic body size
        // copy phenotypic body
        instruction::CPY, 1, 0, 0, 102, -1, 0, 
        instruction::INC, 1, 0, 0, 102, 0, 0,
        instruction::GR, 1, 2, 0, 103, 102, 0,
        instruction::CPYOUT, 2, 1, 0, 102, 103, 0,
        instruction::JRE, 0, 1, 1, 2, 100, 102,
        instruction::JRS, 0, 0, 0, 4, 0, 0,
 
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        instruction::MARKER, -1, 0, 0, 0, 0, 0  // ENDING OF PHENOTYPIC BODY (for quine)
    };

    //---------- INPUTS

    // inputs (if first element is !=2, algo's out should be of size 0)
    std::vector<int> input_0 { 0, 0, 0 };
    std::vector<int> input_1 { 1, 0, 0 };
    std::vector<int> input_2 { 2, 0, 0 };
    std::vector<int> input_3 { 0, 2, 0 };
    std::vector<int> input_4 { 2 };
    std::vector<int> input_5 { 1, 2, 0 };
    std::vector<int> input_6 { 2, -1, 0 };

    std::vector<std::vector<int>> inputs = {
        input_0, input_1, input_2, input_3,
        input_4, input_5, input_6
    };

    //---------- EXECUTE

    algo->reset_data();

    // set phenotypic body and execute
    algo->set_phenotypic_body(phenotypic_body);

    for(int i=0; i<inputs.size();i++)
    {
        algo->set_input(inputs[i]);
        algo->exec(std::vector<sp_entity>(0));

        // get result
        auto out_res = algo->get_output();

        bool is_valid = false;
        bool is_replication_phase = inputs[i][0] == 2 && inputs[i].size()>1;
        if(is_replication_phase)
        {
            is_valid =x86_comp_output(out_res, phenotypic_body); 
            std::cout << "Replication phase, output is ";
        }
        else
        {
            is_valid = out_res.size() == 0;
            std::cout << "Not replication phase, output is ";
        }
            
        if(is_valid)
        {
            std::cout << greencol << "valid" << defcol;
        }
        else
        {
            std::cout << redcol << "not valid" << defcol << std::endl;

            if(is_replication_phase)
            {
                int diff_index = first_diff_index(phenotypic_body, out_res);

                if(diff_index == -1)
                {
                    std::cout << "\tOutput size = " << out_res.size()
                        << " (expected : " << phenotypic_body.size() << ")" << std::endl;
                }
                else
                {
                    std::cout << "\tFirst diff is at " << diff_index
                        << "(phenotypic_body = " << phenotypic_body[i] << ", out = " << out_res[i]
                        << ")" << std::endl;
                }
            }
        }
        std::cout << std::endl;
   }

    std::cout << std::endl << "Simple quine experiment done"
        << std::endl << std::endl;
}


void ReplicationEvoXQuine::finding_empty_place(sp_evox algo)
{
    std::cout << "Complex quine duplicating on empty place" << std::endl << std::endl;

    //---------- ALGOS

    // phenotypic body for an ranom gene mutation
    // 
    // code template comes from FunctionExecutionEvoX
    std::vector<int> phenotypic_body { 
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

        instruction::JRGE, 0, 1, 0, 3, 149, 1,      //----- l.25
        instruction::CPY, 1, 0, 0, 149, 1, 0,
        instruction::CPY, 1, 0, 0, 99, 150, 0,  // data stack begins at 150
        // clean output
        instruction::SETOS, 0, 0, 0, 0, 0, 0,
        // call muti-level exec func
        instruction::INC, 1, 0, 0, 99, 0, 0,
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

        // replicate only if phase flag==2
        instruction::INC, 1, 0, 0, 99, 0, 0,      //----- l.38
        instruction::CPYIS, 2, 0, 0, 99, 0, 0,  // store input size at top of of stack
        instruction::JRG, 0, 2, 0, 2, 99, 1,    // HALT if input size < 2
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::CPYIN, 2, 1, 0, 99, 0, 0,  // store phase flag at top of stack
        instruction::JRE, 0, 2, 0, 2, 99, 2,
        instruction::JRA, 0, 0, 0, 7, 0, 0,     // skip if phase is not replication (phase==2)

        // call replication function
        instruction::CPY, 2, 0, 0, 99, 3, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // check if train (phase flag = 0)
        instruction::JRE, 0, 2, 0, 2, 99, 0,      //----- l.51
        instruction::JRA, 0, 0, 0, 7, 0, 0,     // skip if phase is not train (phase==0)

        // call train function
        instruction::CPY, 2, 0, 0, 99, 4, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        
        // check if test (phase flag = 1)
        instruction::JRE, 0, 2, 0, 2, 99, 1,      //----- l.59
        instruction::JRA, 0, 0, 0, 7, 0, 0,     // skip if phase is not test (phase==1)

        // call test function
        instruction::CPY, 2, 0, 0, 99, 5, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 2, 0, 0, 0, 0,

    //----- replication func : output = phenotypic body
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        // mutate phenotypic body
        instruction::INC, 1, 0, 0, 99, 0, 0,      //----- l.69
        instruction::CPY, 2, 0, 0, 99, 8, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        // find end of phenotypic body
        instruction::CPY, 1, 0, 0, 100, -7, 0,
        instruction::ADD, 1, 1, 0, 100, 100, 7,
        instruction::GR, 1, 2, 0, 101, 100, 0,
        instruction::JRE, 0, 0, 1, 2, instruction::MARKER, 101, // check if we are on a marker
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::GR, 1, 2, 0, 101, 100, 0,
        instruction::DEC, 1, 0, 0, 100, 0, 0,
        instruction::JRE, 0, 0, 1, 2, -1, 101,  // check that marker ID is -1
        instruction::JRS, 0, 0, 0, 8, 0, 0,
        instruction::ADD, 1, 1, 0, 100, 100, 7, // end of phenotypic body
        instruction::SETOS, 1, 0, 0, 100, 0, 0, // output size = phenotypic body size
        // copy phenotypic body
        instruction::CPY, 1, 0, 0, 102, -1, 0,      //----- 87 
        instruction::INC, 1, 0, 0, 102, 0, 0,
        instruction::GR, 1, 2, 0, 103, 102, 0,
        instruction::CPYOUT, 2, 1, 0, 102, 103, 0,
        instruction::JRE, 0, 1, 1, 2, 100, 102,
        instruction::JRS, 0, 0, 0, 4, 0, 0,
        // find a vacant place
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 9, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        instruction::CPY, 1, 2, 0, 100, 99, 0,  // get return arg
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 1, 0, 2, 100, -1,
        instruction::WRITE, 1, 1, 0, 101, 100, 0, 
  
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

    //----- train phase evaluation func
        instruction::MARKER, 0, 4, 0, 0, 0, 0,

        // check error flag
        instruction::CPYIN, 1, 1, 0, 100, 1, 0,      //----- l.105
        instruction::JRE, 0, 1, 0, 2, 100, 0,
        instruction::JRA, 0, 0, 0, 8, 0, 0,     // does not evaluate if error flag is 1

        // call evaluation function
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 6, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // if error flag is 1, update phenotypic body
        instruction::CPYIN, 1, 1, 0, 100, 1, 0,
        instruction::JRE, 0, 1, 0, 2, 100, 1,
        instruction::JRA, 0, 0, 0, 8, 0, 0,     // does not evaluate if error flag is 1

        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 7, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 4, 0, 0, 0, 0,

    //----- test phase evaluation func
        instruction::MARKER, 0, 5, 0, 0, 0, 0,

        // call evaluation function
        instruction::INC, 1, 0, 0, 99, 0, 0,      //----- l.127
        instruction::CPY, 2, 0, 0, 99, 5, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 5, 0, 0, 0, 0,

    //----- evaluation func
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

        // for the moment : just output a constant from phenotypic body
        instruction::CPY, 1, 0, 0, 100, 6, 0,      //----- l.136
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 1, 0, 0, 100, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

    //----- update after error func
        instruction::MARKER, 0, 7, 0, 0, 0, 0,

        // for the moment : randomly change phenotypic body
        instruction::CPY, 1, 0, 0, 101, 1000, 0,      //----- l.142
        instruction::CPYIN, 1, 1, 0, 101, 2, 0,
        instruction::GR, 1, 1, 0, 102, 136*7+5, 0,
        instruction::ADD, 1, 1, 1, 103, 102, 101,
        instruction::SUB, 1, 1, 1, 102, 102, 101, 
        instruction::RUI, 1, 1, 1, 101, 102, 103,
        instruction::GSET, 1, 1, 0, 136*7+5, 101, 0,    // randomly change the output numbert is set there
        instruction::REGEN, 0, 0, 0, 0, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 7, 0, 0, 0, 0,

    //----- mutate before replciating func
        instruction::MARKER, 0, 8, 0, 0, 0, 0,

        // for the moment : randomly change phenotypic body
        instruction::RUI, 1, 0, 0, 101, -1000, 1000,      //----- l.153
        instruction::GSET, 1, 1, 0, 136*7+5, 101, 0,    // randomly change the output number

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 8, 0, 0, 0, 0,

    //----- find an empty place
        instruction::MARKER, 0, 9, 0, 0, 0, 0,

        instruction::CPYUS, 1, 0, 0, 100, 0, 0,         //----- 158
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, -1, 0,
        instruction::INC, 2, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 2, 1, 5, 99, 100,
        instruction::EMPTY, 1, 2, 0, 101, 99, 0,
        instruction::JRE, 0, 2, 1, 3, 101, 1, 
        instruction::JRS, 0, 0, 0, 4, 0, 0,
        instruction::CPY, 2, 0, 0, 99, -1, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 9, 0, 0, 0, 0,

    //----- end of phenotypic body
        instruction::MARKER, -1, 0, 0, 0, 0, 0          //----- 169
    };

    algo->set_phenotypic_body(phenotypic_body);

    sp_entity_void entity_void = std::make_shared<EntityVoid>("entity void");
    entity_void->init();

    sp_entity_int entity_int_1 = std::make_shared<EntityInt>("entity int 1");
    entity_int_1->init();

    std::vector<sp_place> places {
        std::make_shared<Place>(entity_int_1, 0),
        std::make_shared<Place>(algo, 1),
        std::make_shared<Place>(entity_void, 2)
    };

    //---------- UNIVERSE

    sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);
    universe->link_universe_functions_to_individuals();


    //---------- EXEC

    
    int nb_phases = 0;

    int error=0;

    for(int i=0;i<nb_phases;i++)
    {
        std::cout << "Training : in=(0,0)." << std::endl;

        algo->set_input({0,0});
        algo->exec(std::vector<sp_entity>(0));


        std::vector<int> out_res = algo->get_output();
        std::cout << "Training, output:" << to_str(out_res) << std::endl;

        if(out_res.size()!=1)
        {
            std::cout << redcol << "\tInvalid : " << defcol
                << "Output size is " << out_res.size() 
                << ", should be 1."
                << std::endl;
        }
        else
        {
            error = 314 - out_res[0];
            error = error<0 ? -error : error;
            std::cout << "Test. Error is " << error 
                << ", in=(0,1," << error << ")"
                << std::endl;
            
            std::vector<int>::const_iterator beg = algo->get_phenotypic_body().begin()+129*7;
            std::vector<int>::const_iterator end = algo->get_phenotypic_body().begin()+130*7;

            std::vector<int> phenotypic_body(beg, end);

            std::cout << "Old phenotypic body : " << to_str(phenotypic_body) << std::endl;
            algo->set_input({0,1,error});
            algo->exec(std::vector<sp_entity>(0));

            beg = algo->get_phenotypic_body().begin()+136*7;
            end = algo->get_phenotypic_body().begin()+137*7;

            std::vector<int> new_phenotypic_body(beg, end);

            std::cout << "New phenotypic body : " << to_str(new_phenotypic_body) << std::endl; 
        }
    }

    std::cout << "Replication..." << std::endl;

    algo->set_input({2,0});
    algo->exec(std::vector<sp_entity>(0));

    sp_entity entity1 = places[0]->get_entity();
    sp_entity entity2 = places[1]->get_entity();
    sp_entity entity3 = places[2]->get_entity();

    if( !( entity1->is_type(TYPE_INT) && entity2->is_type(X86_ALGO) && entity3->is_type(FREEGENES) ))
    {
        std::cout << "Wrong entity types : entity 1 should be int (" 
            << entity1->is_type(TYPE_INT) << "), entity 2 should be x86 algo ("
            << entity2->is_type(X86_ALGO) << "), entity 3 should be free molecules ("
            << entity3->is_type(FREEGENES) << ")." << std::endl;
    }
    else
    {
        std::cout << "Genes copied";
        if(!x86_comp_output(std::dynamic_pointer_cast<FreeMolecules>(entity3)->get_phenotypic_body(),algo->get_phenotypic_body()))
        {
            std::cout << " not";
        }

        std::cout << " successfully." << std::endl;
    }

    std::cout << "Replication : end" << std::endl;

    std::cout << std::endl  << "Complex quine duplicating on empty place" << std::endl << std::endl;

}

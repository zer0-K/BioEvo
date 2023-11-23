#include "ReplicationEvoXQuine.hpp"

#include "../../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../../Utils/Functions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"


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
    quine_function_trigger(algo);
}

void ReplicationEvoXQuine::simple_quine(sp_evox algo)
{
    std::cout << "Simple quine experiment running" << std::endl << std::endl;

    //---------- GENOME

    // genome for a simple quine
    // 
    std::vector<int> genome { 
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

    // set genome and execute
    algo->set_genes(genome);

    algo->set_input(input);
    algo->exec(std::vector<sp_entity>(0));

    // get result
    auto out_res = algo->get_output();

    std::cout << "Output of quine : " << std::endl;
    for(int i=0; i<out_res.size();i++)
        std::cout << out_res[i] << " ";
    std::cout << std::endl;

    std::cout << std::endl << "Output == genes : " << x86_comp_output(out_res, genome)
        << std::endl
        << "Simple quine experiment done" 
        << std::endl << std::endl;
}


void ReplicationEvoXQuine::quine_function_trigger(sp_evox algo)
{
    std::cout << "Quine replication trigger experiment running"
        << std::endl << std::endl;

    //---------- GENOME

    // genome for a simple quine
    // 
    std::vector<int> genome { 
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
 

    //----- replication func : output = genes
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        // find end of genome
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
        instruction::ADD, 1, 1, 0, 100, 100, 7, // end of genome
        instruction::SETOS, 1, 0, 0, 100, 0, 0, // output size = genome size
        // copy genome
        instruction::CPY, 1, 0, 0, 102, -1, 0, 
        instruction::INC, 1, 0, 0, 102, 0, 0,
        instruction::GR, 1, 2, 0, 103, 102, 0,
        instruction::CPYOUT, 2, 1, 0, 102, 103, 0,
        instruction::JRE, 0, 1, 1, 2, 100, 102,
        instruction::JRS, 0, 0, 0, 4, 0, 0,
 
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        instruction::MARKER, -1, 0, 0, 0, 0, 0  // ENDING OF GENOME (for quine)
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

    // set genome and execute
    algo->set_genes(genome);

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
            is_valid =x86_comp_output(out_res, genome); 
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
                int diff_index = first_diff_index(genome, out_res);

                if(diff_index == -1)
                {
                    std::cout << "\tOutput size = " << out_res.size()
                        << " (expected : " << genome.size() << ")" << std::endl;
                }
                else
                {
                    std::cout << "\tFirst diff is at " << diff_index
                        << "(genome = " << genome[i] << ", out = " << out_res[i]
                        << ")" << std::endl;
                }
            }
        }
        std::cout << std::endl;
   }

    std::cout << std::endl << "Simple quine experiment done"
        << std::endl << std::endl;
}
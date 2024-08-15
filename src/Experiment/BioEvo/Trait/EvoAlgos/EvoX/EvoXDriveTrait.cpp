#include "EvoXDriveTrait.hpp"

#include "../../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../../Utils/Functions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

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
    test_setup();
}

sp_evox EvoXDriveTrait::get_algo(std::string name)
{
    sp_evox algo = std::make_shared<EvoX>(name);
    algo->init();

    //---------- MOLECULAR BODY

    // molecular body for an ranom gene mutation
    // 
    // code template comes from FunctionExecutionEvoX
    std::vector<int> molecular_body { 
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

    //----- replication func : output = molecular body
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        // mutate molecular body
        instruction::INC, 1, 0, 0, 99, 0, 0,      //----- l.69
        instruction::CPY, 2, 0, 0, 99, 8, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        // find end of molecular body
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
        instruction::ADD, 1, 1, 0, 100, 100, 7, // end of molecular body
        instruction::SETOS, 1, 0, 0, 100, 0, 0, // output size = molecular body size
        // copy molecular body
        instruction::CPY, 1, 0, 0, 102, -1, 0, 
        instruction::INC, 1, 0, 0, 102, 0, 0,
        instruction::GR, 1, 2, 0, 103, 102, 0,
        instruction::CPYOUT, 2, 1, 0, 102, 103, 0,
        instruction::JRE, 0, 1, 1, 2, 100, 102,
        instruction::JRS, 0, 0, 0, 4, 0, 0,
 
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

    //----- train phase evaluation func
        instruction::MARKER, 0, 4, 0, 0, 0, 0,

        // check error flag
        instruction::CPYIN, 1, 1, 0, 100, 1, 0,      //----- l.96
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

        // if error flag is 1, update molecular body
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

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 4, 0, 0, 0, 0,

    //----- test phase evaluation func
        instruction::MARKER, 0, 5, 0, 0, 0, 0,

        // call evaluation function
        instruction::INC, 1, 0, 0, 99, 0, 0,      //----- l.119
        instruction::CPY, 2, 0, 0, 99, 5, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 5, 0, 0, 0, 0,

    //----- evaluation func
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

        // for the moment : just output a constant from molecular body
        instruction::CPY, 1, 0, 0, 100, 6, 0,      //----- l.128
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 1, 0, 0, 100, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

    //----- update after error func
        instruction::MARKER, 0, 7, 0, 0, 0, 0,

        // for the moment : randomly change molecular body
        instruction::CPY, 1, 0, 0, 101, 1000, 0,      //----- l.134
        instruction::CPYIN, 1, 1, 0, 101, 2, 0,
        instruction::GR, 1, 1, 0, 102, 128*7+5, 0,
        instruction::ADD, 1, 1, 1, 103, 102, 101,
        instruction::SUB, 1, 1, 1, 102, 102, 101, 
        instruction::RUI, 1, 1, 1, 101, 102, 103,
        instruction::GSET, 1, 1, 0, 128*7+5, 101, 0,    // randomly change the output numbert is set there
        instruction::REGEN, 0, 0, 0, 0, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 7, 0, 0, 0, 0,

    //----- mutate before replciating func
        instruction::MARKER, 0, 8, 0, 0, 0, 0,

        // for the moment : randomly change molecular body
        instruction::RUI, 1, 0, 0, 101, -1000, 1000,      //----- l.145
        instruction::GSET, 1, 1, 0, 128*7+5, 101, 0,    // randomly change the output number

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 8, 0, 0, 0, 0,

    //----- end of molecular body
        instruction::MARKER, -1, 0, 0, 0, 0, 0
    };

    algo->set_molecular_body(molecular_body);

    return algo;
}

void EvoXDriveTrait::test_setup()
{
    sp_evox algo = get_algo("algo 1");

    std::vector<std::vector<int>> inputs {
        { 0, 0 },
        { 0, 1, 0 },
        { 0, 0 },
        { 0, 1, 0 },
        { 2, 0 }
    };
    int nb_phases = 10;

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
            
            std::vector<int>::const_iterator beg = algo->get_molecular_body().begin()+129*7;
            std::vector<int>::const_iterator end = algo->get_molecular_body().begin()+130*7;

            std::vector<int> molecular_body(beg, end);

            std::cout << "Old molecular body : " << to_str(molecular_body) << std::endl;
            algo->set_input({0,1,error});
            algo->exec(std::vector<sp_entity>(0));

            beg = algo->get_molecular_body().begin()+128*7;
            end = algo->get_molecular_body().begin()+129*7;

            std::vector<int> new_molecular_body(beg, end);

            std::cout << "New molecular body : " << to_str(new_molecular_body) << std::endl; 
        }
    }

    // triggering quine
    std::cout << "Triggering quine..." << std::endl;
    algo->set_input({2,0});
    algo->exec(std::vector<sp_entity>(0));

    std::vector<int> copied_out = algo->get_output();
    if(x86_comp_output(copied_out, algo->get_molecular_body()))
    {
        std::cout << "Genes copied successfully" << std::endl;
    }
    else
    {
        std::cout << "Genes" << redcol << " not " << defcol
            << "copied successfully" << std::endl;
    }

}
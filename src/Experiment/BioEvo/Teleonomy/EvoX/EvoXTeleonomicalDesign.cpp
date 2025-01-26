#include "EvoXTeleonomicalDesign.hpp"

#include "../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../Utils/Functions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

EvoXTeleonomicalDesign::EvoXTeleonomicalDesign()
    :Experiment::Experiment(name_exp_bioevo_teleonomy_design_evox)
{
    init();
}

void EvoXTeleonomicalDesign::init()
{

}

void EvoXTeleonomicalDesign::launch()
{
    test_setup();
}

sp_evox EvoXTeleonomicalDesign::get_algo(std::string name)
{
    sp_evox algo = std::make_shared<EvoX>(name);
    algo->init();

    //---------- PHENOTYPIC BODY

    // phenotypic body for an ranom gene mutation
    // 
    // code template comes from FunctionExecutionEvoX
    std::vector<int> phenotypic_body { 
    //----- metadata
        // "-1" = not set

        //--- genetic metadata
        // position of meta-exec func
        // phenotypic body size
        // instr pos of main func (entry point)
        instruction::XXX, 4, -1, -1, 0, 0, 0,

        //--- teleonomical metadata
        // metateleonomical field (teleonomical type)
        // past teleonomical ID list pos
        // teleonomical ID list pos
        instruction::XXX, 1, -1, -1, 0, 0, 0,

        // go to main
        instruction::JMP, 0, 0, 0, 27, 0, 0,    // skip meta-exec func

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

        // autopoiesis
        instruction::GR, 1, 1, 0, 100, 2, 0,      //----- l.27
        instruction::JRE, 0, 1, 0, 2, 100, -1,  // check if morphogenesis already done
        instruction::JRA, 0, 0, 0, 3, 0, 0,
        instruction::CPY, 1, 0, 0, 99, 150, 0,  // data stack begins at 150
        instruction::CALL, 0, 0, 0, 0, 15, 0,   // call autopoiesis func
        // clean output
        instruction::SETOS, 0, 0, 0, 0, 0, 0,
        // call muti-level exec func
        instruction::CALL, 0, 0, 0, 0, 2, 0,
        // end
        instruction::HALT, 0, 0, 0, 0, 0, 0,

        instruction::MARKER, 0, 1, 0, 0, 0, 0,

    //----- function 'main' calls
        instruction::MARKER, 0, 2, 0, 0, 0, 0,

        instruction::INC, 1, 0, 0, 99, 0, 0,        //----- l.37
        instruction::CPYIS, 2, 0, 0, 99, 0, 0,  // store input size at top of of stack
        instruction::JRG, 0, 2, 0, 3, 99, 1,    // HALT if input size < 2
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::CPYIN, 2, 1, 0, 99, 0, 0,  // store phase flag at top of stack

        // replicate if phase flag==2
        instruction::JRE, 0, 2, 0, 2, 99, 2,
        instruction::JRA, 0, 0, 0, 4, 0, 0,     // skip if phase is not replication (phase==2)

        // call replication function
        instruction::CALL, 0, 0, 0, 0, 3, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // check if train (phase flag = 0)
        instruction::JRE, 0, 2, 0, 2, 99, 0,        //----- l.48
        instruction::JRA, 0, 0, 0, 4, 0, 0,     // skip if phase is not train (phase==0)
        instruction::CALL, 0, 0, 0, 0, 4, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        
        // check if test (phase flag = 1)
        instruction::JRE, 0, 2, 0, 2, 99, 1,        //----- l.53
        instruction::JRA, 0, 0, 0, 4, 0, 0,     // skip if phase is not test (phase==1)
        instruction::CALL, 0, 0, 0, 0, 5, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // check if acquire func (phase flag = 3)
        instruction::JRE, 0, 2, 0, 2, 99, 3,        //----- l.58
        instruction::JRA, 0, 0, 0, 4, 0, 0,
        instruction::CALL, 0, 0, 0, 0, 12, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // check if write func (phase flag = 4)
        instruction::JRE, 0, 2, 0, 2, 99, 4,        //----- l.58
        instruction::JRA, 0, 0, 0, 5, 0, 0,

        // call gene copy function
        instruction::CPY, 2, 0, 0, 99, 6, 0,    // put func id at top of stack as arg
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 1, 0,    // put teleonomical ID at top of stack as arg
        instruction::CALL, 0, 0, 0, 0, 14, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 2, 0, 0, 0, 0,

    //----- replication func : output = phenotypic body
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        // mutate phenotypic body
        instruction::CALL, 0, 0, 0, 0, 8, 0,    //----- l.66
        // get end of phenotypic body
        instruction::CALL, 0, 0, 0, 0, 17, 0,
        instruction::GR, 1, 1, 0, 100, 2, 0,    // end of phenotypic body
        instruction::SETOS, 1, 0, 0, 100, 0, 0, // output size = phenotypic body size
        // copy phenotypic body
        instruction::CPY, 1, 0, 0, 102, -1, 0,      //----- l.70
        instruction::INC, 1, 0, 0, 102, 0, 0,
        instruction::GR, 1, 2, 0, 103, 102, 0,
        instruction::CPYOUT, 2, 1, 0, 102, 103, 0,
        instruction::JRE, 0, 1, 1, 2, 100, 102,
        instruction::JRS, 0, 0, 0, 4, 0, 0,
        // find a vacant place
        instruction::CALL, 0, 0, 0, 0, 9, 0,
        instruction::CPY, 1, 2, 0, 100, 99, 0,  // get return arg
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 1, 0, 2, 100, -1,
        instruction::WRITE, 1, 1, 0, 101, 100, 0, 
  
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

    //----- train phase evaluation func
        instruction::MARKER, 0, 4, 0, 0, 0, 0,

        // check error flag
        instruction::CPYIN, 1, 1, 0, 100, 1, 0,      //----- l.84
        instruction::JRE, 0, 1, 0, 2, 100, 0,
        instruction::JRA, 0, 0, 0, 8, 0, 0,     // does not evaluate if error flag is 1

        // call evaluation function
        instruction::CALL, 0, 0, 0, 0, 6, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // if error flag is 1, update phenotypic body
        instruction::CPYIN, 1, 1, 0, 100, 1, 0,
        instruction::JRE, 0, 1, 0, 2, 100, 1,
        instruction::JRA, 0, 0, 0, 8, 0, 0,     // does not evaluate if error flag is 1
        instruction::CALL, 0, 0, 0, 0, 7, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 4, 0, 0, 0, 0,

    //----- test phase evaluation func
        instruction::MARKER, 0, 5, 0, 0, 0, 0,

        // call evaluation function
        instruction::CALL, 0, 0, 0, 0, 6, 0,    //----- l.96

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 5, 0, 0, 0, 0,

    //----- evaluation func
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

        // for the moment : just output a constant from phenotypic body
        instruction::CPY, 1, 0, 0, 100, 6, 0,      //----- l.100
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 1, 0, 0, 100, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

    //----- update after error func
        instruction::MARKER, 0, 7, 0, 0, 0, 0,

        // for the moment : randomly change phenotypic body
        instruction::CPY, 1, 0, 0, 101, 1000, 0,      //----- l.106
        instruction::CPYIN, 1, 1, 0, 101, 2, 0,
        instruction::GR, 1, 1, 0, 102, 136*7+5, 0,
        instruction::ADD, 1, 1, 1, 103, 102, 101,
        instruction::SUB, 1, 1, 1, 102, 102, 101, 
        instruction::RUI, 1, 1, 1, 101, 102, 103,
        instruction::GSET, 1, 1, 0, 136*7+5, 101, 0,    // randomly change the output numbert is set there
        instruction::REGEN, 0, 0, 0, 0, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 7, 0, 0, 0, 0,

    //----- mutate before replicating func
        instruction::MARKER, 0, 8, 0, 0, 0, 0,

        // for the moment : randomly change phenotypic body
        instruction::RUI, 1, 0, 0, 101, -1000, 1000,      //----- l.117
        instruction::GSET, 1, 1, 0, 136*7+5, 101, 0,    // randomly change the output number

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 8, 0, 0, 0, 0,

    //----- find an empty place
        instruction::MARKER, 0, 9, 0, 0, 0, 0,

        instruction::CPYUS, 1, 0, 0, 100, 0, 0,         //----- l.122
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

    //----- get free molecules satisfying specs
        instruction::MARKER, 0, 10, 0, 0, 0, 0,

        instruction::CPYUS, 1, 0, 0, 100, 0, 0,         //----- l.134
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, -1, 0,
        instruction::INC, 2, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 2, 1, 2, 99, 100,  // end loop if at end of universe
        instruction::JRA, 0, 0, 0, 4, 0, 0,     // continue otherwise
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, -1, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        // read place at i
        instruction::READ, 2, 0, 0, 99, 0, 0,
        instruction::CPYIS, 1, 0, 0, 101, 0, 0,
        instruction::JRL, 0, 1, 0, -8, 101, 2,
        instruction::CPYIN, 1, 1, 0, 102, 0, 0, 
        instruction::CPYIN, 1, 1, 0, 103, 1, 0, 
        // check meta params
        instruction::JRE, 0, 1, 0, 2, 102, 3,   // check if input is free molecules
        instruction::JRS, 0, 0, 0, 12, 0, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 2, 0, 4, 99, -1,   // if func arg is -1 we get free molecules
        instruction::JRE, 0, 2, 1, 3, 99, 103,  // otherwise check if we want these free molecules
        instruction::INC, 1, 0, 0, 99, 0, 0, 
        instruction::JRS, 0, 0, 0, 5, 0, 0,
        // appropriate free molecules found
        instruction::DEC, 1, 0, 0, 99, 0, 0,    // remove loop index from stack
        instruction::CPY, 2, 0, 0, 99, 1, 0,    // return arg : true (1, i.e. we copy phenotypic body)

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 10, 0, 0, 0, 0,

    //----- copy input (free molecules) into code as new func
        instruction::MARKER, 0, 11, 0, 0, 0, 0,

        // find end of phenotypic body
        instruction::CPY, 1, 0, 0, 100, -7, 0,      //----- l.160
        instruction::ADD, 1, 1, 0, 100, 100, 7,
        instruction::GR, 1, 2, 0, 101, 100, 0,
        instruction::JRE, 0, 0, 1, 2, instruction::MARKER, 101, // check if we are on a marker
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::GR, 1, 2, 0, 101, 100, 0,
        instruction::DEC, 1, 0, 0, 100, 0, 0,
        instruction::JRE, 0, 0, 1, 2, -1, 101,  // check that marker ID is -1
        instruction::JRS, 0, 0, 0, 8, 0, 0,
        // get id of marker before end
        instruction::SUB, 1, 1, 0, 100, 100, 5,
        instruction::GR, 1, 2, 0, 101, 100, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // new func id
        instruction::ADD, 1, 1, 0, 100, 100, 4, // reajust pos for last func
        // copy input into data
        instruction::CPY, 1, 0, 0, 102, 1, 0,       // beginning of phenotypic body to copy in input
        instruction::CPY, 1, 0, 0, 103, 1000, 0,    // pos of copying in data
        instruction::CPY, 1, 1, 0, 104, 103, 0,     // index to iterate through data phenotypic body
        instruction::CPYIS, 1, 0, 0, 105, 0, 0,
            // marker (begin)
            instruction::CPY, 2, 0, 0, 104, instruction::MARKER, 0, //----- l.178
            instruction::ADD, 1, 1, 0, 104, 104, 2,
            instruction::CPY, 2, 1, 0, 104, 101, 0,
            instruction::ADD, 1, 1, 0, 104, 104, 4,
            // internal of func
            instruction::INC, 1, 0, 0, 102, 0, 0,
            instruction::INC, 1, 0, 0, 104, 0, 0,   // inc loop indices
            instruction::JRE, 0, 1, 1, 3, 102, 105,
            instruction::CPYIN, 2, 2, 0, 104, 102, 0,
            instruction::JRS, 0, 0, 0, 4, 0, 0,
            // marker (end)
            instruction::CPY, 2, 0, 0, 104, instruction::MARKER, 0,
            instruction::ADD, 1, 1, 0, 104, 104, 2,
            instruction::CPY, 2, 1, 0, 104, 101, 0,
            instruction::ADD, 1, 1, 0, 104, 104, 4,
        // copy data into phenotypic body before ending marker
        instruction::GCPY, 2, 2, 2, 100, 103, 104,
        // REGEN ?
        // instruction::REGEN, 0, 0, 0, 0, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 11, 0, 0, 0, 0,

    //----- search and pick free molecules
        instruction::MARKER, 0, 12, 0, 0, 0, 0,

        // find free molecules with teleonomical ID = 1
        instruction::INC, 1, 0, 0, 99, 0, 0,            //----- l.195
        instruction::CPY, 2, 0, 0, 99, 1, 0,
        instruction::CALL, 0, 0, 0, 0, 10, 0,

        // copy if phenotypic body found
        instruction::JRE, 0, 2, 0, 3, 99, 1,    // if free molecules not found, skip
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        // exec the func
        instruction::CALL, 0, 0, 0, 1, 11, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 12, 0, 0, 0, 0,

    //----- get function begining and end in phenotypic body
        // arg1 : func ID
        instruction::MARKER, 0, 13, 0, 0, 0, 0,

        instruction::CPY, 1, 2, 0, 100, 99, 0,          //----- l.205
        instruction::CPY, 1, 0, 0, 101, -1, 0,      // beg
        instruction::CPY, 1, 0, 0, 102, -1, 0,      // end
        // look for function
        instruction::CPY, 1, 0, 0, 110, -7, 0,
        instruction::ADD, 1, 1, 0, 110, 110, 7,
        instruction::GR, 1, 2, 0, 104, 110, 0,
        instruction::JRE, 0, 1, 0, 2, 104, instruction::MARKER, // marker found
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        // check func id
        instruction::ADD, 1, 1, 0, 110, 110, 2,
        instruction::GR, 1, 2, 0, 104, 110, 0,
        instruction::SUB, 1, 1, 0, 110, 110, 2,
        instruction::JRE, 0, 1, 1, 2, 104, 100,
        instruction::JRS, 0, 0, 0, 8, 0, 0,
        // put beginning on the stack
        instruction::CPY, 2, 1, 0, 99, 110, 0,
        // look for end of function
        instruction::ADD, 1, 1, 0, 110, 110, 7,
        instruction::GR, 1, 2, 0, 104, 110, 0,
        instruction::JRE, 0, 1, 0, 2, 104, instruction::MARKER, // marker found
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        // check func id
        instruction::ADD, 1, 1, 0, 110, 110, 2,
        instruction::GR, 1, 2, 0, 104, 110, 0,
        instruction::SUB, 1, 1, 0, 110, 110, 2,
        instruction::JRE, 0, 1, 1, 2, 104, 100,
        instruction::JRS, 0, 0, 0, 8, 0, 0,
        // write end of func on the stack
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 1, 0, 99, 110, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 13, 0, 0, 0, 0,

    //----- write function as free molecules
        instruction::MARKER, 0, 14, 0, 0, 0, 0,

        instruction::CPY, 1, 2, 0, 100, 99, 0,          //----- l.233
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,      // get args (teol ID in 100 and ID in 101)
        // get begin and end of func
        instruction::CALL, 0, 0, 0, 0, 13, 0,

        // get begining and end
        instruction::CPY, 1, 2, 0, 103, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 102, 99, 0,  // begin is at 102 and end at 103
        // reajust (to remove markers)
        instruction::ADD, 1, 1, 0, 102, 102, 7, 
        instruction::DEC, 1, 0, 0, 103, 0, 0,
        // stop if func not found or invalid (beg = end)
        instruction::JRG, 0, 1, 1, 2, 103, 102, 
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        // copy phenotypic body
        instruction::SUB, 1, 1, 0, 102, 102, 3,     // let 2 phenotypic body left for metadata
        instruction::SUB, 1, 1, 1, 104, 103, 102,
        instruction::SETOS, 1, 0, 0, 104, 0, 0,
        instruction::CPY, 1, 1, 0, 110, 102, 0,     // cpy beg-2 (-3 actually) in index var 
        instruction::INC, 1, 0, 0, 102, 0, 0, 
        instruction::INC, 1, 0, 0, 110, 0, 0,  
        instruction::SUB, 1, 1, 1, 105, 110, 102,
        instruction::GR, 1, 2, 0, 104, 110, 0,
        instruction::CPYOUT, 2, 1, 0, 105, 104, 0,
        instruction::JRE, 0, 1, 1, 2, 110, 103,
        instruction::JRS, 0, 0, 0, 5, 0, 0,
        // end of copy - do metadata
        instruction::CPYOUT, 1, 0, 0, 0, 3, 0,      // free molecules
        instruction::CPYOUT, 1, 1, 0, 1, 100, 0,    // teolonomical ID
        // find a vacant place
        instruction::CALL, 0, 0, 0, 0, 9, 0,

        // write on vacant place
        instruction::CPY, 1, 2, 0, 100, 99, 0,  // get return arg
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 1, 0, 2, 100, -1,
        instruction::WRITE, 1, 1, 0, 101, 100, 0, 
 
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 14, 0, 0, 0, 0,

    //----- autopoiesis
        instruction::MARKER, 0, 15, 0, 0, 0, 0,
 
        // compute phenotypic body size
        instruction::CALL, 0, 0, 0, 0, 17, 0,       //----- l.266
        // call func that maps func ID and teleo IDs
        instruction::CALL, 0, 0, 0, 0, 16, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 15, 0, 0, 0, 0,

    //----- func ID list building
        // create the list of current teleonomical IDs
        instruction::MARKER, 0, 16, 0, 0, 0, 0,

        // create a local stack ptr
        instruction::CPY, 1, 1, 0, 100, 99, 0,      //----- l.271
 
        // get func IDs and teleo IDs
        instruction::CPY, 1, 0, 0, 101, -7, 0,
        instruction::ADD, 1, 1, 0, 101, 101, 7,
        instruction::GR, 1, 2, 0, 102, 101, 0,
        instruction::JRE, 0, 0, 1, 2, instruction::MARKER, 102, // check if we are on a marker
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,
        instruction::GR, 1, 2, 0, 102, 101, 0,
        instruction::DEC, 1, 0, 0, 101, 0, 0,
        instruction::JRE, 0, 0, 1, 3, 0, 102,  // check that marker ID is 0
        instruction::JRE, 0, 0, 1, 8, -1, 102,  // check that marker ID is -1
        instruction::JRS, 0, 0, 0, 9, 0, 0,
        // save func ID (funcs are saved twice)
        instruction::ADD, 1, 1, 0, 101, 101, 2,
        instruction::GR, 1, 2, 0, 102, 101, 0,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 1, 0, 100, 102, 0,
        instruction::SUB, 1, 1, 0, 101, 101, 2,
        // go back to loop
        instruction::JRS, 0, 0, 0, 15, 0, 0,

        // remove duplicates
        instruction::ADD, 1, 1, 0, 101, 99, 1,  // p = first func ID    ----- l.289
        instruction::CPY, 1, 0, 0, 102, -1, 0,  // i
        instruction::INC, 1, 0, 0, 102, 0, 0,
        instruction::ADD, 1, 1, 1, 103, 101, 102,   // p + i
        instruction::ADD, 1, 1, 1, 104, 103, 102,   // p + 2i
        instruction::JRG, 0, 1, 1, 3, 104, 100,
        instruction::CPY, 2, 2, 0, 103, 104, 0,
        instruction::JRS, 0, 0, 0, 5, 0, 0, 
        instruction::DEC, 1, 0, 0, 103, 0, 0,
        instruction::CPY, 1, 1, 0, 100, 103, 0, // reset top of local data stack

        // save at end of phenotypic body (i is the nb of funcs)
        instruction::GR, 1, 1, 0, 103, 2, 0,
        instruction::GCPY, 2, 2, 2, 103, 101, 100,    //----- l.300
        instruction::GSET, 1, 1, 0, 10, 103, 0,   // set teleo list pos
        instruction::ADD, 1, 1, 1, 103, 103, 102,   // recalc phenotypic body size
        instruction::GSET, 1, 1, 0, 2, 103, 0, 


        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 16, 0, 0, 0, 0,

    //----- calc phenotypic body size (in nb of phenotypic body)
        instruction::MARKER, 0, 17, 0, 0, 0, 0,
    
        instruction::CPY, 1, 0, 0, 100, -7, 0,  //----- 307
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

        instruction::GSET, 1, 1, 0, 2, 100, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 17, 0, 0, 0, 0,


    //----- end of phenotypic body
        instruction::MARKER, -1, 0, 0, 0, 0, 0          //----- l.340 
    };

    algo->set_phenotypic_body(phenotypic_body);

    return algo;
}

void EvoXTeleonomicalDesign::test_setup()
{
    sp_evox algo = get_algo("algo 1");

    std::vector<int> input_1 { };

    std::vector<std::vector<int>> inputs {
        input_1
    };


    // set phenotypic body and execute
    algo->set_output_size(1);
    algo->reset_data();

    for(int i=0;i<inputs.size();i++)
    {
        std::vector<int>::const_iterator beg = algo->get_phenotypic_body().end()-30;
        std::vector<int>::const_iterator end = algo->get_phenotypic_body().end()-1;

        std::vector<int> phenotypic_body(beg, end);

        std::cout << "Old phenotypic body : " << to_str(phenotypic_body) << std::endl;
        algo->set_input(inputs[i]);
        algo->exec(std::vector<sp_entity>(0));

        beg = algo->get_phenotypic_body().end()-30;
        end = algo->get_phenotypic_body().end()-1;

        std::vector<int> new_phenotypic_body(beg, end);

        std::cout << "New phenotypic body : " << to_str(new_phenotypic_body) << std::endl; 
    }

}
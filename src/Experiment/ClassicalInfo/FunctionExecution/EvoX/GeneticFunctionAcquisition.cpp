#include "GeneticFunctionAcquisition.hpp"

#include "../../../../Entities/EntityVoid.hpp"
#include "../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../Utils/Functions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/FreeGenes.hpp"

GeneticFunctionAcquisition::GeneticFunctionAcquisition()
    :Experiment::Experiment(name_exp_classical_info_func_acqu_evox)
{
    init();
}

void GeneticFunctionAcquisition::init()
{

}

void GeneticFunctionAcquisition::launch()
{
    //FreeGenesFunctionRead();
    FreeGenesFunctionWrite();
}

//-------------------- READ experiment

sp_evox GeneticFunctionAcquisition::get_algo_read()
{
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();


    // genome for an ranom gene mutation
    // 
    // code template comes from FunctionExecutionEvoX
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

        // check if acquire func (phase flag = 3)
        instruction::JRE, 0, 2, 0, 2, 99, 3,      //----- l.67
        instruction::JRA, 0, 0, 0, 7, 0, 0,

        // call gene copy function
        instruction::CPY, 2, 0, 0, 99, 12, 0,   // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 2, 0, 0, 0, 0,

    //----- replication func : output = genes
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        // mutate genome
        instruction::INC, 1, 0, 0, 99, 0, 0,      //----- l.77
        instruction::CPY, 2, 0, 0, 99, 8, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        // find end of genome
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
        instruction::CPY, 1, 0, 0, 102, -1, 0,      //----- l.95
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
        instruction::CPYIN, 1, 1, 0, 100, 1, 0,      //----- l.114
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

        // if error flag is 1, update genes
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
        instruction::INC, 1, 0, 0, 99, 0, 0,      //----- l.136
        instruction::CPY, 2, 0, 0, 99, 5, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 5, 0, 0, 0, 0,

    //----- evaluation func
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

        // for the moment : just output a constant from genome
        instruction::CPY, 1, 0, 0, 100, 6, 0,      //----- l.145
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 1, 0, 0, 100, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

    //----- update after error func
        instruction::MARKER, 0, 7, 0, 0, 0, 0,

        // for the moment : randomly change genome
        instruction::CPY, 1, 0, 0, 101, 1000, 0,      //----- l.151
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

        // for the moment : randomly change genome
        instruction::RUI, 1, 0, 0, 101, -1000, 1000,      //----- l.162
        instruction::GSET, 1, 1, 0, 136*7+5, 101, 0,    // randomly change the output number

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 8, 0, 0, 0, 0,

    //----- find an empty place
        instruction::MARKER, 0, 9, 0, 0, 0, 0,

        instruction::CPYUS, 1, 0, 0, 100, 0, 0,         //----- l.167
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

    //----- get free genes satisfying specs
        instruction::MARKER, 0, 10, 0, 0, 0, 0,

        instruction::CPYUS, 1, 0, 0, 100, 0, 0,         //----- l.179
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
        instruction::JRE, 0, 1, 0, 2, 102, 3,   // check if input is free genes
        instruction::JRS, 0, 0, 0, 12, 0, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 2, 0, 4, 99, -1,   // if func arg is -1 we get free genes
        instruction::JRE, 0, 2, 1, 3, 99, 103,  // otherwise check if we want these free genes
        instruction::INC, 1, 0, 0, 99, 0, 0, 
        instruction::JRS, 0, 0, 0, 5, 0, 0,
        // appropriate free genes found
        instruction::DEC, 1, 0, 0, 99, 0, 0,    // remove loop index from stack
        instruction::CPY, 2, 0, 0, 99, 1, 0,    // return arg : true (1, i.e. we copy genes)

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 10, 0, 0, 0, 0,

    //----- copy input (free genes) into code as new func
        instruction::MARKER, 0, 11, 0, 0, 0, 0,

        // find end of genome
        instruction::CPY, 1, 0, 0, 100, -7, 0,      //----- l.205
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
        instruction::CPY, 1, 0, 0, 102, 1, 0,       // beginning of genes to copy in input
        instruction::CPY, 1, 0, 0, 103, 1000, 0,    // pos of copying in data
        instruction::CPY, 1, 1, 0, 104, 103, 0,     // index to iterate through data genes
        instruction::CPYIS, 1, 0, 0, 105, 0, 0,
            // marker (begin)
            instruction::CPY, 2, 0, 0, 104, instruction::MARKER, 0, //----- l.223
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
        // copy data into genes before ending marker
        instruction::GCPY, 2, 2, 2, 100, 103, 104,
        // REGEN ?
        // instruction::REGEN, 0, 0, 0, 0, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 11, 0, 0, 0, 0,

    //----- search and pick free genes
        instruction::MARKER, 0, 12, 0, 0, 0, 0,

        // find free genes with teleonomical ID = 1
        instruction::INC, 1, 0, 0, 99, 0, 0,            //----- l.240
        instruction::CPY, 2, 0, 0, 99, 1, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 10, 0,
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        // copy if genes found
        instruction::JRE, 0, 2, 0, 3, 99, 1,    // if free genes not found, skip
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        // exec the func
        instruction::CPY, 2, 0, 0, 99, 11, 0,
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 12, 0, 0, 0, 0,

    //----- end of genome
        instruction::MARKER, -1, 0, 0, 0, 0, 0          //----- l.258
    };

    algo->set_genes(genome);

    return algo;
}

std::vector<int> GeneticFunctionAcquisition::get_genes_function_write()
{
    return {
        // phase flag = 3, func teleonomical ID = 1 (ID in genes can be != teleonomical ID)
        3, 1,
        // (for the moment, only increment arg on stack)
        instruction::INC, 2, 0, 0, 99, 0, 0,
    };
}

void GeneticFunctionAcquisition::FreeGenesFunctionRead()
{
    std::cout << "Acquire free genes as function (begin)" << std::endl << std::endl;

    sp_evox algo = get_algo_read();

    //---------- FREE GENES

    sp_freegenes freegenes = std::make_shared<FreeGenes>("free genes");
    freegenes->init();

    // get the genes for the free genes 
    std::vector<int> genes = get_genes_function_write();
    freegenes->set_genes(genes);

    std::vector<sp_place> places {
        std::make_shared<Place>(algo, 0),
        std::make_shared<Place>(freegenes, 1)
    };

    //---------- UNIVERSE

    sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);
    universe->link_universe_functions_to_individuals();


    //---------- EXEC

    std::vector<int>::const_iterator beg = algo->get_genes().begin()+256*7;
    std::vector<int>::const_iterator end = algo->get_genes().end()-1;

    std::vector<int> end_of_genome_before(beg, end);

    std::cout << "End of genome before execution : " << std::endl
        << to_str(end_of_genome_before) << std::endl << std::endl;


    algo->set_input({3,1});
    algo->exec(std::vector<sp_entity>(0));

    beg = algo->get_genes().begin()+256*7;
    end = algo->get_genes().end()-1;

    std::vector<int> end_of_genome_after(beg, end);

    std::cout << "End of genome after execution : " << std::endl
        << to_str(end_of_genome_after) << std::endl << std::endl;

    std::cout << "Acquire free genes as function (end)" << std::endl << std::endl;
}

//-------------------- WRITE experiment


sp_evox GeneticFunctionAcquisition::get_algo_write()
{
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();


    // genome for an ranom gene mutation
    // 
    // code template comes from FunctionExecutionEvoX
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

        // check if acquire func (phase flag = 3)
        instruction::JRE, 0, 2, 0, 2, 99, 3,      //----- l.67
        instruction::JRA, 0, 0, 0, 7, 0, 0,

        // call gene copy function
        instruction::CPY, 2, 0, 0, 99, 12, 0,   // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // check if write func (phase flag = 4)
        instruction::JRE, 0, 2, 0, 2, 99, 4,      //----- l.75
        instruction::JRA, 0, 0, 0, 10, 0, 0,

        // call gene copy function
        instruction::CPY, 2, 0, 0, 99, 6, 0,    // put func id at top of stack as arg
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 1, 0,    // put teleonomical ID at top of stack as arg
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 14, 0,   // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 2, 0, 0, 0, 0,

    //----- replication func : output = genes
        instruction::MARKER, 0, 3, 0, 0, 0, 0,

        // mutate genome
        instruction::INC, 1, 0, 0, 99, 0, 0,      //----- l.89
        instruction::CPY, 2, 0, 0, 99, 8, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        // find end of genome
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
        instruction::CPY, 1, 0, 0, 102, -1, 0,      //----- l.107
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
        instruction::CPYIN, 1, 1, 0, 100, 1, 0,      //----- l.126
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

        // if error flag is 1, update genes
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
        instruction::INC, 1, 0, 0, 99, 0, 0,      //----- l.148
        instruction::CPY, 2, 0, 0, 99, 6, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 5, 0, 0, 0, 0,

    //----- evaluation func
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

        // for the moment : just output a constant from genome
        instruction::CPY, 1, 0, 0, 100, 6, 0,      //----- l.157
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 1, 0, 0, 100, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 6, 0, 0, 0, 0,

    //----- update after error func
        instruction::MARKER, 0, 7, 0, 0, 0, 0,

        // for the moment : randomly change genome
        instruction::CPY, 1, 0, 0, 101, 1000, 0,      //----- l.163
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

        // for the moment : randomly change genome
        instruction::RUI, 1, 0, 0, 101, -1000, 1000,      //----- l.174
        instruction::GSET, 1, 1, 0, 136*7+5, 101, 0,    // randomly change the output number

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 8, 0, 0, 0, 0,

    //----- find an empty place
        instruction::MARKER, 0, 9, 0, 0, 0, 0,

        instruction::CPYUS, 1, 0, 0, 100, 0, 0,         //----- l.179
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

    //----- get free genes satisfying specs
        instruction::MARKER, 0, 10, 0, 0, 0, 0,

        instruction::CPYUS, 1, 0, 0, 100, 0, 0,         //----- l.191
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
        instruction::JRE, 0, 1, 0, 2, 102, 3,   // check if input is free genes
        instruction::JRS, 0, 0, 0, 12, 0, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 2, 0, 4, 99, -1,   // if func arg is -1 we get free genes
        instruction::JRE, 0, 2, 1, 3, 99, 103,  // otherwise check if we want these free genes
        instruction::INC, 1, 0, 0, 99, 0, 0, 
        instruction::JRS, 0, 0, 0, 5, 0, 0,
        // appropriate free genes found
        instruction::DEC, 1, 0, 0, 99, 0, 0,    // remove loop index from stack
        instruction::CPY, 2, 0, 0, 99, 1, 0,    // return arg : true (1, i.e. we copy genes)

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 10, 0, 0, 0, 0,

    //----- copy input (free genes) into code as new func
        instruction::MARKER, 0, 11, 0, 0, 0, 0,

        // find end of genome
        instruction::CPY, 1, 0, 0, 100, -7, 0,      //----- l.217
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
        instruction::CPY, 1, 0, 0, 102, 1, 0,       // beginning of genes to copy in input
        instruction::CPY, 1, 0, 0, 103, 1000, 0,    // pos of copying in data
        instruction::CPY, 1, 1, 0, 104, 103, 0,     // index to iterate through data genes
        instruction::CPYIS, 1, 0, 0, 105, 0, 0,
            // marker (begin)
            instruction::CPY, 2, 0, 0, 104, instruction::MARKER, 0, //----- l.235
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
        // copy data into genes before ending marker
        instruction::GCPY, 2, 2, 2, 100, 103, 104,
        // REGEN ?
        // instruction::REGEN, 0, 0, 0, 0, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 11, 0, 0, 0, 0,

    //----- search and pick free genes
        instruction::MARKER, 0, 12, 0, 0, 0, 0,

        // find free genes with teleonomical ID = 1
        instruction::INC, 1, 0, 0, 99, 0, 0,            //----- l.252
        instruction::CPY, 2, 0, 0, 99, 1, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 10, 0,
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        // copy if genes found
        instruction::JRE, 0, 2, 0, 3, 99, 1,    // if free genes not found, skip
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        // exec the func
        instruction::CPY, 2, 0, 0, 99, 11, 0,
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 12, 0, 0, 0, 0,

    //----- get function begining and end in genes
        // arg1 : func ID
        instruction::MARKER, 0, 13, 0, 0, 0, 0,

        instruction::CPY, 1, 2, 0, 100, 99, 0,          //----- l.270
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

    //----- write function as free genes
        instruction::MARKER, 0, 14, 0, 0, 0, 0,

        instruction::CPY, 1, 2, 0, 100, 99, 0,          //----- l.299
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,      // get args (teol ID in 100 and ID in 101)
        // get begin and end of func
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 13, 0,   // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
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
        // copy genes
        instruction::SUB, 1, 1, 0, 102, 102, 3,     // let 2 genes left for metadata
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
        instruction::CPYOUT, 1, 0, 0, 0, 3, 0,      // free genes
        instruction::CPYOUT, 1, 1, 0, 1, 100, 0,    // teolonomical ID
        // find a vacant place
        instruction::INC, 1, 0, 0, 99, 0, 0,        //----- l.328
        instruction::CPY, 2, 0, 0, 99, 9, 0,    // store the func to exec at top of data stack
        instruction::INC, 1, 0, 0, 0, 0, 0,     // prepare exec of func
        instruction::GPTR, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 0, 0, 3,
        instruction::JMP, 0, 0, 0, 1, 0, 0,     // exec func
        // write on vacant place
        instruction::CPY, 1, 2, 0, 100, 99, 0,  // get return arg
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 1, 0, 2, 100, -1,
        instruction::WRITE, 1, 1, 0, 101, 100, 0, 
 
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 14, 0, 0, 0, 0,

    //----- end of genome
        instruction::MARKER, -1, 0, 0, 0, 0, 0          //----- l.340
    };

    algo->set_genes(genome);

    return algo;
}

void GeneticFunctionAcquisition::FreeGenesFunctionWrite()
{
    std::cout << "Write function as free genes (begin)" << std::endl << std::endl;

    sp_evox algo = get_algo_write();

    //---------- FREE GENES

    sp_entity_void entity_void = std::make_shared<EntityVoid>("entity void");
    entity_void->init();

    std::vector<sp_place> places {
        std::make_shared<Place>(algo, 0),
        std::make_shared<Place>(entity_void, 1)
    };

    //---------- UNIVERSE

    sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);
    universe->link_universe_functions_to_individuals();


    //---------- EXPECTED OUT

    std::vector<int> expected_free_genes {
        3, 6,
        instruction::CPY, 1, 0, 0, 100, 6, 0,
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 1, 0, 0, 100, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    //---------- EXEC

    algo->set_input({4,1});
    algo->exec(std::vector<sp_entity>(0));

    sp_entity entity = universe->get_places()[1]->get_entity();
    if(entity->is_type(FREEGENES))
    {
        sp_freegenes free_genes = std::dynamic_pointer_cast<FreeGenes>(entity);
        std::vector<int> genes = free_genes->get_genes();

        bool is_valid = x86_comp_output(expected_free_genes, genes);

        if(is_valid)
        {
            std::cout << "Function successfully copied as free genes"
                << std::endl << std::endl;
        }
        else
        {
            int diff_index = first_diff_index(genes, expected_free_genes);

            if(diff_index==-1)
            {
                std::cout << "Expected free genes don't have expected size"
                    << std::endl << std::endl;
            }
              
            std::cout << "Expected free genes : " << std::endl
                << to_str(expected_free_genes) << std::endl
                << "Actual free genes : " << std::endl
                << to_str(genes) << std::endl << std::endl;
        }
    }
    else
    {
        std::cout << "No free genes at place" << std::endl << std::endl;
    }

    std::cout << "Write function as free genes (end)" << std::endl << std::endl;
}

#include "GenerateBaseEvoX1.hpp"

#include "../../../../Utils/Functions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/FreeGenes.hpp"

#include "../../../../Entities/EntityVoid.hpp"
#include "../../../../Entities/EntityInt.hpp"

GenerateBaseEvoX1::GenerateBaseEvoX1()
    :Experiment::Experiment(name_exp_bioevo_genesis_1)
{
    init();
}

void GenerateBaseEvoX1::init()
{

}

void GenerateBaseEvoX1::launch()
{
    sp_evox algo = this->get_base_evox();
    auto genome_parts = this->get_genome_parts();
    auto universe = this->get_evox_universe(algo);

    trigger_synthesis(algo, universe);
}

/**
 * @brief get the base algo
 */
sp_evox GenerateBaseEvoX1::get_base_evox()
{
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();

    //---------- GENOME

    // base genome for an autonomical genesis
    // teleonomical IDs:
    //      - -100- : genetic data
    //      - -1 : genome end
    //      - 0-99 : core functions (meta-exec func, main, core switcher, teleonomical list builder,...)
    //      - 100-199 : general genesis funcs (autopoiesis, find free genes, quine, genetic decompression,...) 
    //      - 200-299 : internal utility funcs (genome size, copy input as func, func pos,...)
    //      - 300-399 : external utility funcs (pick free genes, find empty place, write func as free genes,...)
    //      - 400-499 : machine learning funcs (learning switcher, train, test, error correction,...)
    //      - 1000+ : evaluation functions and other
    std::vector<int> genome { 
    //----- metadata
        // "-1" = not set

        //--- genetic metadata
        // position of meta-exec func
        // genome size
        // position of data stack
        instruction::XXX, 3, -1, 150, -1, 0, 0,

        // go to main
        instruction::JMP, 0, 0, 0, 26, 0, 0,    // skip meta-exec func

    //----- exec fct with given id
        // args :
        //      1 - func id
        instruction::MARKER, 0, 0, 0, 0, 0, 0,
        
        // find marker with given id
        instruction::CPY, 1, 2, 1, 100, 99, 0,      // get arg from stack
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

        // clean output
        instruction::SETOS, 0, 0, 0, 0, 0, 0,   //----- l.26
        // autopoiesis
        instruction::CPY, 1, 0, 0, 99, 150, 0,  // temporary set stack
        instruction::CALL, 0, 0, 0, 0, 100, 0,  // call autopoiesis func
        // end
        instruction::HALT, 0, 0, 0, 0, 0, 0,

        instruction::MARKER, 0, 1, 0, 0, 0, 0,

    //----- autopoiesis
        instruction::MARKER, 0, 100, 0, 0, 0, 0,

        // execute func corresponding to the current phase
        instruction::JRE, 0, 1, 0, 2, 98, 1,    // skip phase 1 if first phase was done before
        instruction::CALL, 0, 0, 0, 0, 101, 0,
        instruction::CALL, 0, 0, 0, 0, 102, 0,
        // compute genome size
        instruction::CALL, 0, 0, 0, 0, 200, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 100, 0, 0, 0, 0,

    //----- first autopoiesis phase
        // this phase consists in initializing the individual
        instruction::MARKER, 0, 101, 0, 0, 0, 0,

        // temporary use an autopoeisis phase at 98
        // data stack stuff
        instruction::GR, 1, 1, 0, 100, 3, 0,    // stack pos is at 3rd pos in genome
        instruction::CPY, 1, 1, 0, 99, 100, 0,  // set data stack pos
        instruction::GDELW, 0, 0, 0, 27*SIZE_INSTR, 0, 0,
        // build list of funcs to add at top of data stack
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 404, 0,    // update after error
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 403, 0,    // eval func
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 402, 0,    // test phase
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 401, 0,    // train phase
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 400, 0,    // learning switcher
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 302, 0,    // write func as free genes
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 301, 0,    // find empty place
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 202, 0,    // get func pos
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 105, 0,    // mutate before replication
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 104, 0,    // quine func
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, 2, 0,      // core switcher
        // update autopoiesis phase
        instruction::CPY, 1, 0, 0, 98, 1, 0,
        // recalc genome size
        instruction::CALL, 0, 0, 0, 0, 200, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 101, 0, 0, 0, 0,

    //----- second autopoiesis phase
        // this phase consists in finding the needed parts
        instruction::MARKER, 0, 102, 0, 0, 0, 0,

        // find genes for top of list
        instruction::GR, 1, 1, 0, 100, 3, 0,
        instruction::JRE, 0, 1, 1, 3, 99, 100,
        instruction::CALL, 0, 0, 0, 0, 103, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::GSET, 1, 0, 0, 27*7+5, 2, 0,
        instruction::REGEN, 0, 0, 0, 0, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 102, 0, 0, 0, 0,

    //----- search and pick free genes
        instruction::MARKER, 0, 103, 0, 0, 0, 0,

        // find free genes with given teleonomical ID (in param at pos 1)
        instruction::CALL, 0, 0, 0, 0, 300, 0,

        // copy if genes found
        instruction::JRE, 0, 2, 0, 3, 99, 1,    // if free genes not found, skip
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CALL, 0, 0, 0, 0, 201, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 103, 0, 0, 0, 0,

    //----- calc genome size (in nb of genes)
        instruction::MARKER, 0, 200, 0, 0, 0, 0,
    
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

        instruction::GSET, 1, 1, 0, 2, 100, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 200, 0, 0, 0, 0,

    //----- copy input (free genes) into code as new func
        instruction::MARKER, 0, 201, 0, 0, 0, 0,

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
        // get id in input
        instruction::CPYIN, 1, 1, 0, 101, 1, 0,
        // copy input into data
        instruction::CPY, 1, 0, 0, 102, 1, 0,       // beginning of genes to copy in input
        instruction::CPY, 1, 0, 0, 103, 1000, 0,    // pos of copying in data
        instruction::CPY, 1, 1, 0, 104, 103, 0,     // index to iterate through data genes
        instruction::CPYIS, 1, 0, 0, 105, 0, 0,
            // marker (begin)
            instruction::CPY, 2, 0, 0, 104, instruction::MARKER, 0,
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

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 201, 0, 0, 0, 0,

    //----- get free genes in input
        instruction::MARKER, 0, 300, 0, 0, 0, 0,

        instruction::CPYUS, 1, 0, 0, 100, 0, 0,
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
        instruction::CPY, 2, 0, 0, 99, 1, 0,    // return arg : true (1, i.e. we copy genes)

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::MARKER, 0, 300, 0, 0, 0, 0,


    //----- end of genome
        instruction::MARKER, -1, 0, 0, 0, 0, 0
    };

    algo->set_genes(genome);

    return algo;
}

std::map<std::string, std::vector<int>> GenerateBaseEvoX1::get_genome_parts()
{

    std::vector<int> genome_core_switcher {
    //----- core switcher
        //instruction::MARKER, 0, 2, 0, 0, 0, 0,
        3, 2,

        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPYIS, 2, 0, 0, 99, 0, 0,  // store input size at top of of stack
        instruction::JRG, 0, 2, 0, 3, 99, 1,    // HALT if input size < 2
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::CPYIN, 2, 1, 0, 99, 0, 0,  // store phase flag at top of stack

        // replicate if phase flag==2
        instruction::JRE, 0, 2, 0, 2, 99, 2,
        instruction::JRA, 0, 0, 0, 4, 0, 0,     // skip if phase is not replication (phase==2)

        // call replication function
        instruction::CALL, 0, 0, 0, 0, 104, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // check if train (phase flag = 0)
        instruction::JRE, 0, 2, 0, 2, 99, 0,
        instruction::JRA, 0, 0, 0, 4, 0, 0,     // skip if phase is not train (phase==0)
        instruction::CALL, 0, 0, 0, 0, 401, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        
        // check if test (phase flag = 1)
        instruction::JRE, 0, 2, 0, 2, 99, 1,
        instruction::JRA, 0, 0, 0, 4, 0, 0,     // skip if phase is not test (phase==1)
        instruction::CALL, 0, 0, 0, 0, 402, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // check if acquire func (phase flag = 3)
        instruction::JRE, 0, 2, 0, 2, 99, 3,
        instruction::JRA, 0, 0, 0, 6, 0, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPYIN, 2, 1, 0, 99, 1, 0,
        instruction::CALL, 0, 0, 0, 0, 103, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // check if write func (phase flag = 4)
        instruction::JRE, 0, 2, 0, 2, 99, 4,
        instruction::JRA, 0, 0, 0, 5, 0, 0,

        // call gene copy function
        instruction::CPYIN, 2, 1, 0, 99, 1, 0,    // put func id at top of stack as arg
        instruction::CALL, 0, 0, 0, 0, 302, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // otherwise, call function given in input
        instruction::CPYIN, 2, 1, 0, 99, 1, 0, 
        instruction::CALL, 0, 2, 0, 0, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 2, 0, 0, 0, 0
    };

    std::vector<int> genome_ID_list {
    //----- func ID list building
        // create the list of current teleonomical IDs
        //instruction::MARKER, 0, 4, 0, 0, 0, 0,
        3, 4,

        // create a local stack ptr
        instruction::CPY, 1, 1, 0, 100, 99, 0,

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
        instruction::ADD, 1, 1, 0, 101, 99, 1,  // p = first func ID
        instruction::CPY, 1, 0, 0, 102, -1, 0,  // i
        instruction::INC, 1, 0, 0, 102, 0, 0,
        instruction::ADD, 1, 1, 1, 103, 101, 102,   // p + i
        instruction::ADD, 1, 1, 1, 104, 103, 102,   // p + 2i
        instruction::JRG, 0, 1, 1, 3, 104, 100,
        instruction::CPY, 2, 2, 0, 103, 104, 0,
        instruction::JRS, 0, 0, 0, 5, 0, 0, 
        instruction::DEC, 1, 0, 0, 103, 0, 0,
        instruction::CPY, 1, 1, 0, 100, 103, 0, // reset top of local data stack

        // save at end of genome (i is the nb of funcs)
        instruction::GR, 1, 1, 0, 103, 2, 0,
        instruction::GCPY, 2, 2, 2, 103, 101, 100,
        instruction::GSET, 1, 1, 0, 10, 103, 0,   // set teleo list pos
        instruction::ADD, 1, 1, 1, 103, 103, 102,   // recalc genome size
        instruction::GSET, 1, 1, 0, 2, 103, 0, 


        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 4, 0, 0, 0, 0
    };

    std::vector<int> genome_quine_function {
    //----- quine replication func : output = genes
        //instruction::MARKER, 0, 104, 0, 0, 0, 0,
        3, 104,

        // mutate genome
        instruction::CALL, 0, 0, 0, 0, 105, 0,
        // get end of genome
        instruction::CALL, 0, 0, 0, 0, 200, 0,
        instruction::GR, 1, 1, 0, 100, 2, 0,    // end of genome
        instruction::SETOS, 1, 0, 0, 100, 0, 0, // output size = genome size
        // copy genome
        instruction::CPY, 1, 0, 0, 102, -1, 0,
        instruction::INC, 1, 0, 0, 102, 0, 0,
        instruction::JRE, 0, 1, 1, 4, 102, 100,
        instruction::GR, 1, 2, 0, 103, 102, 0,
        instruction::CPYOUT, 2, 1, 0, 102, 103, 0,
        instruction::JRS, 0, 0, 0, 4, 0, 0,
        // find a vacant place
        instruction::CALL, 0, 0, 0, 0, 301, 0,
        instruction::CPY, 1, 2, 0, 100, 99, 0,  // get return arg
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 1, 0, 2, 100, -1,
        instruction::WRITE, 1, 1, 0, 101, 100, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 104, 0, 0, 0, 0
    };

    std::vector<int> genome_mutate_before_replication {
    //----- mutate before replicating func
        //instruction::MARKER, 0, 105, 0, 0, 0, 0,
        3, 105,

        // for the moment : randomly change genome
        instruction::RUI, 1, 0, 0, 101, -1000, 1000,
        instruction::GSET, 1, 1, 0, 5, 101, 0,    // randomly change a number

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 105, 0, 0, 0, 0
    };

    std::vector<int> genome_func_pos {
    //----- get function begining and end in genes
        // arg1 : func ID
        //instruction::MARKER, 0, 202, 0, 0, 0, 0,
        3, 202,

        instruction::CPY, 1, 2, 0, 100, 99, 0,
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
        //instruction::MARKER, 0, 202, 0, 0, 0, 0
    };

    std::vector<int> genome_find_empty_place {
    //----- find an empty place
        //instruction::MARKER, 0, 301, 0, 0, 0, 0,
        3, 301,

        instruction::CPYUS, 1, 0, 0, 100, 0, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 2, 0, 0, 99, -1, 0,
        instruction::INC, 2, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 2, 1, 4, 99, 100,
        instruction::EMPTY, 1, 2, 0, 101, 99, 0,
        instruction::JRE, 0, 2, 1, 3, 101, 1, 
        instruction::JRS, 0, 0, 0, 4, 0, 0,
        instruction::CPY, 2, 0, 0, 99, -1, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 301, 0, 0, 0, 0
    };

    std::vector<int> genome_export_func {
    //----- write function as free genes
        //instruction::MARKER, 0, 302, 0, 0, 0, 0,
        3, 302,

        // copy metadata first - do metadata
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,      // free genes
        instruction::CPY, 2, 1, 0, 99, 100, 0,    // teolonomical ID


        // get begin and end of func
        instruction::CALL, 0, 0, 0, 0, 202, 0,

        // get begining and end
        instruction::CPY, 1, 2, 0, 103, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 102, 99, 0,  // begin is at 102 and end at 103
        // reajust (to remove markers and return (final JMP))
        instruction::ADD, 1, 1, 0, 102, 102, 7, 
        instruction::SUB, 1, 1, 0, 103, 103, 1,
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
        // end of copy - metadata
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPYOUT, 1, 0, 0, 0, 3, 0,      // free genes
        instruction::CPYOUT, 1, 2, 0, 1, 99, 0,    // teolonomical ID
        instruction::INC, 1, 0, 0, 99, 0, 0,


        // find a vacant place
        instruction::CALL, 0, 0, 0, 0, 301, 0,

        // write on vacant place
        instruction::CPY, 1, 2, 0, 100, 99, 0,  // get return arg
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRE, 0, 1, 0, 2, 100, -1,
        instruction::WRITE, 1, 1, 0, 101, 100, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 302, 0, 0, 0, 0
    };

    std::vector<int> genome_learning_switcher {
    //----- learning switcher
        //instruction::MARKER, 0, 400, 0, 0, 0, 0,
        3, 400,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 400, 0, 0, 0, 0
    };

    std::vector<int> genome_train_phase {
    //----- train phase evaluation func
        // exec func with given teleonomical ID
        //instruction::MARKER, 0, 401, 0, 0, 0, 0,
        3, 401,

        // check error flag
        instruction::CPYIN, 1, 1, 0, 100, 1, 0,
        instruction::JRE, 0, 1, 0, 2, 100, 0,
        instruction::JRA, 0, 0, 0, 4, 0, 0,     // does not evaluate if error flag is 1

        // call evaluation function
        instruction::CPYIN, 1, 1, 0, 100, 2, 0,
        instruction::CALL, 0, 1, 0, 0, 100, 0,
        instruction::JMP, 2, 0, 0, 0, 0, 0,

        // if error flag is 1, update genes
        instruction::CPYIN, 1, 1, 0, 100, 1, 0,
        instruction::JRE, 0, 1, 0, 2, 100, 1,
        instruction::JRA, 0, 0, 0, 2, 0, 0,     // does not evaluate if error flag is 1
        instruction::CALL, 0, 0, 0, 0, 404, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 401, 0, 0, 0, 0
    };

    std::vector<int> genome_test_phase {
    //----- test phase evaluation func
        //instruction::MARKER, 0, 402, 0, 0, 0, 0,
        3, 402,

        // call evaluation function
        instruction::CALL, 0, 0, 0, 0, 403, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 402, 0, 0, 0, 0
    };

    std::vector<int> genome_evalution_function {
    //----- evaluation func
        //instruction::MARKER, 0, 403, 0, 0, 0, 0,
        3, 403,

        // for the moment : just output a constant from genome
        instruction::CPY, 1, 0, 0, 100, -1, 0,
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 1, 0, 0, 100, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 403, 0, 0, 0, 0
    };

    std::vector<int> genome_update_on_error {
    //----- update after error func
        //instruction::MARKER, 0, 404, 0, 0, 0, 0,
        3, 404,

        // for the moment : randomly change genome
        instruction::CPY, 1, 0, 0, 101, 1000, 0,
        instruction::CPYIN, 1, 1, 0, 101, 2, 0,
        instruction::GR, 1, 1, 0, 102, 315*SIZE_INSTR+5, 0,
        instruction::ADD, 1, 1, 1, 103, 102, 101,
        instruction::SUB, 1, 1, 1, 102, 102, 101, 
        instruction::RUI, 1, 1, 1, 101, 102, 103,
        instruction::MUL, 1, 1, 0, 101, 101, 2, 
        instruction::GSET, 1, 1, 0, 315*SIZE_INSTR+5, 101, 0,    // randomly change the output number is set there
        instruction::REGEN, 0, 0, 0, 0, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
        //instruction::MARKER, 0, 404, 0, 0, 0, 0
    };

    std::map<std::string, std::vector<int>> all_parts {
        { "core switcher", genome_core_switcher },
        //{ "teleonomical list", genome_ID_list },
        { "quine function", genome_quine_function },
        { "mutate before replication", genome_mutate_before_replication },
        { "function position", genome_func_pos },
        { "find empty place", genome_find_empty_place },
        { "export func", genome_export_func },
        { "learning switcher", genome_learning_switcher },
        { "train phase", genome_train_phase },
        { "test phase", genome_test_phase },
        { "evaluation", genome_evalution_function },
        { "update on error", genome_update_on_error }
    };

    return all_parts;
}

/**
 * @brief get the universe for the synthesis
 */
sp_univ_evo_algos GenerateBaseEvoX1::get_evox_universe(sp_evox algo) 
{
    int nb_entity_void = 2;

    std::vector<sp_place> places(nb_entity_void+1); 

    places[0] = std::make_shared<Place>(algo, 0);

    for(int i=0;i<nb_entity_void;i++)
    {
        sp_entity_void entity_void = std::make_shared<EntityVoid>("entity void " + std::to_string(i+1));
        entity_void->init();

        places[i+1] = std::make_shared<Place>(entity_void, i+1);
    }

    //---------- UNIVERSE

    sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);
    universe->link_universe_functions_to_individuals();

    return universe;
}

void GenerateBaseEvoX1::trigger_synthesis(sp_evox algo, sp_univ_evo_algos universe)
{
    // get functions for autopoiesis
    auto genome_parts = this->get_genome_parts();

    //----- trigger autopoiesis

    std::vector<std::string> iteration_order {
        "core switcher",
        "quine function",
        "mutate before replication",
        "function position",
        "find empty place",
        "export func",
        "learning switcher",
        "train phase",
        "test phase",
        "evaluation",
        "update on error"             
    };

    for(int i=0;i<iteration_order.size();i++)
    {
        std::string step_name = iteration_order[i];
        std::vector<int> genome_part = genome_parts[step_name];

        sp_freegenes freegenes = std::make_shared<FreeGenes>("free genes");
        freegenes->init();
        freegenes->set_genes(genome_part);

        universe->get_places()[2]->set_entity(freegenes);

        universe->exec();
    }

    universe->exec();

    write_genes_to_csv(algo->get_genes(), "genes_base_algo_1.csv");
}
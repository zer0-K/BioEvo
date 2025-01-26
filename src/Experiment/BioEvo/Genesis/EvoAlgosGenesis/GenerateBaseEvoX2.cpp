#include "GenerateBaseEvoX2.hpp"

#include <fstream>

#include "../../../../Utils/Functions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/FreeMolecules.hpp"


GenerateBaseEvoX2::GenerateBaseEvoX2()
    :Experiment::Experiment(name_exp_bioevo_genesis_2)
{
    init();
}

void GenerateBaseEvoX2::init()
{

}

void GenerateBaseEvoX2::launch()
{
    sp_evox algo = this->get_base_evox();
    auto phenotypic_body_parts = this->get_phenotypic_body_parts();
    auto universe = this->get_evox_universe(algo);

    trigger_synthesis(algo, universe);
}

sp_evox GenerateBaseEvoX2::get_base_evox()
{
    // create algo
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();

    // get phenotypic body from csv
    std::vector<int> phenotypic_body = get_phenotypic_body_from_csv("phenotypic_body_base_algo_1.csv");
    algo->set_phenotypic_body(phenotypic_body);

    // set data stack at 150
    algo->set_data_at(99, 150);

    return algo;
}

std::map<std::string, std::vector<int>> GenerateBaseEvoX2::get_utility_generators()
{
    // copy input args to stack in reverse order
    std::vector<int> copy_in_to_stack {
        3, 203,

        instruction::CPYIS, 1, 0, 0, 100, 0, 0,
        // beginning of loop
        instruction::DEC, 1, 0, 0, 100, 0, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,    // will copy input on stack
        instruction::CPYIN, 2, 2, 0, 99, 100, 0,    // reverse order
        instruction::JRE, 0, 1, 0, 2, 100, 2,    // ignore first 2 args
        instruction::JRS, 0, 0, 0, 4, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // given input, generate free molecules of order 0
    std::vector<int> generate_free_molecules_order_0 {
        3, 204,

        instruction::CALL, 0, 0, 0, 0, 203, 0,
        // remove generator ID from stack
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        // call the generator
        instruction::CALL, 0, 1, 0, 0, 100, 0,
        // copy the generator out to out
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 2, 0, 0, 99, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // given input, generate free molecules of order 1
    std::vector<int> generate_free_molecules_order_1 {
        3, 205,

        instruction::CALL, 0, 0, 0, 0, 203, 0,
        // remove generator ID from stack
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        // call the generator
        instruction::CALL, 0, 1, 0, 0, 100, 0,
        // copy the generator out to out
        instruction::SETOS, 0, 0, 0, 7, 0, 0,
        instruction::CPYOUT, 1, 2, 0, 6, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPYOUT, 1, 2, 0, 5, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPYOUT, 1, 2, 0, 4, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPYOUT, 1, 2, 0, 3, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPYOUT, 1, 2, 0, 2, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPYOUT, 1, 2, 0, 1, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPYOUT, 1, 2, 0, 0, 99, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    std::map<std::string, std::vector<int>> all_parts {
        { "copy input to stack", copy_in_to_stack },
        { "generate free molecules order 0", generate_free_molecules_order_0 },
        { "generate free molecules order 1", generate_free_molecules_order_1 }
    };

    return all_parts;
}

std::map<std::string, std::vector<int>> GenerateBaseEvoX2::get_generators_order_0()
{
    //---------- abstractions
    
    // 1st instruction argument : instruction (hardcoded)
    std::vector<int> generator_order_0_arg0_hard {
        3, 1000000,

        // called a specialized version of the instruction
        instruction::CALL, 0, 0, 0, 0, 1000014, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };
    // 1st instruction argument : instruction (dynamic)
    std::vector<int> generator_order_0_arg0_soft {
        3, 1000001,

        // called a specialized version of the instruction
        instruction::CALL, 0, 2, 0, 1, 99, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // 2nd instruction argument : 1st arg deepness (hardcoded)
    std::vector<int> generator_order_0_arg1_hard {
        3, 1000002,

        // called a specialized version of the instruction
        instruction::CALL, 0, 0, 0, 0, 1000015, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };
    // 2nd instruction argument : 1st arg deepness (dynamic)
    std::vector<int> generator_order_0_arg1_soft {
        3, 1000003,

        // called a specialized version of the instruction
        instruction::CALL, 0, 2, 0, 1, 99, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // 3rd instruction argument : 2nd arg deepness (hardcoded)
    std::vector<int> generator_order_0_arg2_hard {
        3, 1000004,

        // called a specialized version of the instruction
        instruction::CALL, 0, 0, 0, 0, 1000015, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };
    // 3rd instruction argument : 2nd arg deepness (dynamic)
    std::vector<int> generator_order_0_arg2_soft {
        3, 1000005,

        // called a specialized version of the instruction
        instruction::CALL, 0, 2, 0, 1, 99, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // 4th instruction argument : 3rd arg deepness (hardcoded)
    std::vector<int> generator_order_0_arg3_hard {
        3, 1000006,

        // called a specialized version of the instruction
        instruction::CALL, 0, 0, 0, 0, 1000015, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };
    // 4th instruction argument : 3rd arg deepness (dynamic)
    std::vector<int> generator_order_0_arg3_soft {
        3, 1000007,

        // called a specialized version of the instruction
        instruction::CALL, 0, 2, 0, 1, 99, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // 5th instruction argument : 1st arg value (hardcoded)
    std::vector<int> generator_order_0_arg4_hard {
        3, 1000008,

        // called a specialized version of the instruction
        instruction::CALL, 0, 0, 0, 0, 1000016, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };
    // 5th instruction argument : 1st arg value (dynamic)
    std::vector<int> generator_order_0_arg4_soft {
        3, 1000009,

        // called a specialized version of the instruction
        instruction::CALL, 0, 2, 0, 1, 99, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // 6th instruction argument : 2nd arg value (hardcoded)
    std::vector<int> generator_order_0_arg5_hard {
        3, 1000010,

        // called a specialized version of the instruction
        instruction::CALL, 0, 0, 0, 0, 1000016, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };
    // 6th instruction argument : 2nd arg value (dynamic)
    std::vector<int> generator_order_0_arg5_soft {
        3, 1000011,

        // called a specialized version of the instruction
        instruction::CALL, 0, 2, 0, 1, 99, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // 7th instruction argument : 3rd arg value (hardcoded)
    std::vector<int> generator_order_0_arg6_hard {
        3, 1000012,

        // called a specialized version of the instruction
        instruction::CALL, 0, 0, 0, 0, 1000016, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };
    // 7th instruction argument : 3rd arg value (dynamic)
    std::vector<int> generator_order_0_arg6_soft {
        3, 1000013,

        // called a specialized version of the instruction
        instruction::CALL, 0, 2, 0, 1, 99, 0, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    //---------- specialisations

    // when provided a number, interprete it as the id of an instruction
    std::vector<int> generator_order_0_instruction {
        3, 1000014,

        // compute arg modulo nb of instructions
        instruction::DIV, 1, 2, 0, 100, 99, instruction::size,
        instruction::JRE, 0, 1, 0, 3, 100, 0,
        // if |arg|>= size ( => scale in ]-size;size[ )
        instruction::MUL, 1, 1, 0, 100, 100, instruction::size,
        instruction::SUB, 2, 2, 1, 99, 99, 100,
        // if -size < arg < size
        instruction::JRL, 0, 2, 0, 2, 99, 0,    // if  -size < arg < 0
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 99, 99, instruction::size, 

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // generate the deepness of args with a random geometric distrib
    std::vector<int> generator_order_0_arg_deepness {
        3, 1000015,

        // parameters : a, b, for geom distrib with param p=a/b
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::ADD, 1, 1, 0, 99, 99, 2,
        instruction::RG, 2, 1, 1, 99, 100, 101,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // generate the args values with a random geometric distrib
    std::vector<int> generator_order_0_arg_vals {
        3, 1000016,

        // parameters : a, b for geom distrib with param p=a/b and v the base value
        // final nb = v + random geometric
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 102, 99, 0,
        instruction::ADD, 1, 1, 0, 99, 99, 2,
        instruction::RG, 2, 1, 1, 99, 101, 102,
        instruction::ADD, 2, 2, 1, 99, 99, 100,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    std::map<std::string, std::vector<int>> all_parts {
        // abstractions
        { "order 0 : arg0 abstr hard", generator_order_0_arg0_hard },
        { "order 0 : arg0 abstr dynamic", generator_order_0_arg0_soft },
        { "order 0 : arg1 abstr hard", generator_order_0_arg1_hard },
        { "order 0 : arg1 abstr dynamic", generator_order_0_arg1_soft },
        { "order 0 : arg2 abstr hard", generator_order_0_arg2_hard },
        { "order 0 : arg2 abstr dynamic", generator_order_0_arg2_soft },
        { "order 0 : arg3 abstr hard", generator_order_0_arg3_hard },
        { "order 0 : arg3 abstr dynamic", generator_order_0_arg3_soft },
        { "order 0 : arg4 abstr hard", generator_order_0_arg4_hard },
        { "order 0 : arg4 abstr dynamic", generator_order_0_arg4_soft },
        { "order 0 : arg5 abstr hard", generator_order_0_arg5_hard },
        { "order 0 : arg5 abstr dynamic", generator_order_0_arg5_soft },
        { "order 0 : arg6 abstr hard", generator_order_0_arg6_hard },
        { "order 0 : arg6 abstr dynamic", generator_order_0_arg6_soft },
        // specialisations
        { "order 0 : instruction", generator_order_0_instruction },
        { "order 0 : arg deepness", generator_order_0_arg_deepness },
        { "order 0 : arg values", generator_order_0_arg_vals }
    };

    return all_parts;
}

std::map<std::string, std::vector<int>> GenerateBaseEvoX2::get_generators_order_1()
{
    //---------- abstractions and generalisations

    // a random instruction
    std::vector<int> generator_order_1_rand_1 {
        3, 1001000,

        // parameters : a, b for geom distrib
        // make place for new instruction on the stack (i.e. shift the a&b 7 times)
        instruction::CPY, 1, 1, 0, 100, 99, 0,          // pos of b
        instruction::ADD, 1, 1, 0, 99, 99, SIZE_INSTR,  // shift stack
        instruction::MOV, 2, 2, 0, 99, 100, 0,          // put b on top of stack
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::DEC, 1, 0, 0, 100, 0, 0,
        instruction::MOV, 2, 2, 0, 99, 100, 0,          // put a on top of stack
        instruction::INC, 1, 0, 0, 99, 0, 0,

        // generate arg 0
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::RUI, 2, 0, 0, 99, 0, instruction::size,
        instruction::CALL, 0, 0, 0, 0, 1000000, 0, 
        // put arg 0 on stack where we left place for instr
        instruction::SUB, 1, 1, 0, 100, 99, 9,
        instruction::MOV, 2, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,

        // generate arg 1
        instruction::CALL, 0, 0, 0, 0, 1000002, 0, 
        // put arg 1 on stack where we left place for instr
        instruction::SUB, 1, 1, 0, 100, 99, 8,
        instruction::MOV, 2, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,

        // generate arg 2
        instruction::CALL, 0, 0, 0, 0, 1000004, 0, 
        // put arg 2 on stack where we left place for instr
        instruction::SUB, 1, 1, 0, 100, 99, 7,
        instruction::MOV, 2, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,

        // generate arg 3
        instruction::CALL, 0, 0, 0, 0, 1000006, 0, 
        // put arg 3 on stack where we left place for instr
        instruction::SUB, 1, 1, 0, 100, 99, 6,
        instruction::MOV, 2, 2, 0, 100, 99, 0,
 
        // generate arg 4
        // chooses between 0 and 99 randomly
        instruction::RUI, 2, 0, 0, 99, 0, 1,
        instruction::MUL, 2, 2, 0, 99, 99, 99,
        instruction::CALL, 0, 0, 0, 0, 1000008, 0, 
        // put arg 4 on stack where we left place for instr
        instruction::SUB, 1, 1, 0, 100, 99, 5,
        instruction::MOV, 2, 2, 0, 100, 99, 0,

        // generate arg 5
        // chooses between 0 and 99 randomly
        instruction::RUI, 2, 0, 0, 99, 0, 1,
        instruction::MUL, 2, 2, 0, 99, 99, 99,
        instruction::CALL, 0, 0, 0, 0, 1000010, 0, 
        // put arg 5 on stack where we left place for instr
        instruction::SUB, 1, 1, 0, 100, 99, 4,
        instruction::MOV, 2, 2, 0, 100, 99, 0,

        // generate arg 6
        // chooses between 0 and 99 randomly
        instruction::RUI, 2, 0, 0, 99, 0, 1,
        instruction::MUL, 2, 2, 0, 99, 99, 99,
        instruction::CALL, 0, 0, 0, 0, 1000012, 0, 
        // put arg 6 on stack where we left place for instr
        instruction::SUB, 1, 1, 0, 100, 99, 3,
        instruction::MOV, 2, 2, 0, 100, 99, 0,
        instruction::SUB, 1, 1, 0, 99, 99, 3,

        // return stack :
        // top-6 top-5 top-4 top-3 top-2 top-1 top
        // INSTR DEEP1 DEEP2 DEEP3 ARG1  ARG2  ARG3

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    std::map<std::string, std::vector<int>> all_parts {
        // abstractions
        { "order 1 : random instruction", generator_order_1_rand_1 },

    };

    return all_parts;
}

std::map<std::string, std::vector<int>> GenerateBaseEvoX2::get_phenotypic_body_parts()
{
    std::vector<std::map<std::string, std::vector<int>>> generators {
        get_utility_generators(),
        get_generators_order_0(),
        get_generators_order_1()
    };

    std::map<std::string, std::vector<int>> all_parts {};

    for(int i=0;i<generators.size();i++)
    {
        for(auto const& [generator_name, generator_code] : generators[i])
        {
            all_parts[generator_name] = generator_code;
        }
    }

    return all_parts;
}

/**
 * @brief get the universe for the synthesis
 */
sp_univ_evo_algos GenerateBaseEvoX2::get_evox_universe(sp_evox algo) 
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


void GenerateBaseEvoX2::trigger_synthesis(sp_evox algo, sp_univ_evo_algos universe)
{
    // get functions for autopoiesis
    auto phenotypic_body_parts = this->get_phenotypic_body_parts();

    for(auto const& [generator_name, generator_code] : phenotypic_body_parts)
    {
        // create free molecules with the generator's code
        sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules " + generator_name);
        free_molecules->init();
        free_molecules->set_phenotypic_body(generator_code);

        universe->get_places()[2]->set_entity(free_molecules);

        // tell the algo to get the code
        std::vector<int> input{ 3, generator_code[1] };
        algo->set_input(input);

        // execute
        universe->exec();
    }

    universe->exec();

    write_phenotypic_body_to_csv(algo->get_phenotypic_body(), "phenotypic_body_base_algo_2.csv");
}


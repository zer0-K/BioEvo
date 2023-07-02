#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"

/**
 * @brief Test universes of void entities
*/
bool launch_test_evo_algos_empty()
{
    sp_univ_evo_algos build_empty_universe_evo_algos(int);    
    bool check_universe(sp_univ_evo_algos, int);

    bool is_passed = true;

    // sizes
    std::vector<int> sizes{
        0, 1, 2, 10, 100
    };

    for(int i=0; i<sizes.size(); i++)
    {
        int size_universe = sizes[i];

        // build evo algos universe of wanted size
        sp_univ_evo_algos universe_evo_algos = build_empty_universe_evo_algos(size_universe);

        // check if built universe is correct
        bool res = check_universe(universe_evo_algos, size_universe);

        if(!res)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "\t\tEmpty evo algos universe of size "
                << size_universe << " : ";
            passed_print(res, 2);
        } 
    }

    std::cout << "\tUnit test empty evo algos universe : ";
    passed_print(is_passed, 1);

    return is_passed;
}

/**
 * @brief Create a universe (for evolutionary biology) of given size with void entities
*/
sp_univ_evo_algos build_empty_universe_evo_algos(int size_universe)
{
    sp_univ_evo_algos universe_evo_algos = std::make_shared<UniverseEvoAlgos>(
        size_universe,
        "evo algos universe"
    );

    return universe_evo_algos;
}

/**
 * @brief Test if the built universe is full of void entities
*/
bool check_universe(sp_univ_evo_algos universe, int expected_size)
{
    bool is_passed = true;

    std::vector<sp_place> places = universe->get_places();

    if(verbose_unit_tests && places.size() != expected_size)
    {
        std::cout << "\t\t\tError : wrong universe size" << std::endl;
        std::cout << "\t\t\t\tExpected size : " << expected_size 
            << ", actual size : " << places.size()
            << std::endl;
        is_passed = false;
    }

    for(int i=0; i<expected_size; i++)
    {
        sp_entity entity = places[i]->get_entity();
        
        if(verbose_unit_tests && entity->get_type() != TYPE_VOID)
        {
            std::cout << "\t\t\tError : wrong entity type" << std::endl;
            std::cout << "\t\t\t\tExpected  : " << TYPE_VOID 
                << ", actual : " << entity->get_type()
                << std::endl;
            is_passed = false; 
        }
    }

    return is_passed;
}

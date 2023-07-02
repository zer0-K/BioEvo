// -------------------- OPERATIONS - BOOLEANS - BASIC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"

/**
 * @brief Test simple boolean operations with code eaters
*/
bool launch_test_code_eaters_operations_booleans_basic()
{
    bool test_id(void);     

    bool is_passed = true;

    is_passed &= test_id();

    std::cout << "\t\t\tBasic boolean operations : ";
    passed_print(is_passed, 3);

    return is_passed;
}

/**
 * @brief test identity function
*/
bool test_id()
{
    sp_univ_code_eaters build_universe_code_eaters(int);    
    bool check_universe(sp_univ_code_eaters, int);

    bool is_passed = true;

    // build code eaters universe of wanted size
    sp_univ_code_eaters universe_code_eaters = build_universe_code_eaters(2);

    // TODO
    int size_universe = 1;

    // check if built universe is correct
    bool res = check_universe(universe_code_eaters, size_universe);

    if(verbose_unit_tests)
    {
        std::cout << "\t\t\t\tEmpty code eaters universe of size "
            << size_universe << " : ";
        passed_print(res, 1);
    }

    return is_passed;
}

/**
 * @brief Create a universe (for evolutionary biology) of given size with void entities
*/
sp_univ_code_eaters build_universe_code_eaters(int size_universe)
{
    sp_univ_code_eaters universe_code_eaters = std::make_shared<UniverseCodeEaters>(
        size_universe,
        "code eaters universe"
    );

    return universe_code_eaters;
}

/**
 * @brief Test if the built universe is full of void entities
*/
bool check_universe(sp_univ_code_eaters universe, int expected_size)
{
    bool is_passed = true;

    std::vector<sp_place> places = universe->get_places();

    if(verbose_unit_tests && places.size() != expected_size)
    {
        std::cout << "\t\t\t\tError : wrong universe size" << std::endl;
        std::cout << "\t\t\t\t\tExpected size : " << expected_size 
            << ", actual size : " << places.size()
            << std::endl;
        is_passed = false;
    }

    for(int i=0; i<expected_size; i++)
    {
        sp_entity entity = places[i]->get_entity();
        
        if(verbose_unit_tests && entity->get_type() != TYPE_VOID)
        {
            std::cout << "\t\t\t\tError : wrong entity type" << std::endl;
            std::cout << "\t\t\t\t\tExpected  : " << TYPE_VOID 
                << ", actual : " << entity->get_type()
                << std::endl;
            is_passed = false; 
        }
    }

    return is_passed;
}


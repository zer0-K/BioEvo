#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/ClassicalInfo/Universe/UniverseClassicalInfo.hpp"

/**
 * @brief Test universes of void entities
*/
bool launch_test_classical_info_empty()
{
    sp_univ_info build_empty_universe_info(int);    
    bool check_universe(sp_univ_info, int);

    bool is_passed = true;

    // sizes
    std::vector<int> sizes{
        0, 1, 2, 10, 100
    };

    for(int i=0; i<sizes.size(); i++)
    {
        int size_universe = sizes[i];

        // build info universe of wanted size
        sp_univ_info universe_info = build_empty_universe_info(size_universe);

        // check if built universe is correct
        bool res = check_universe(universe_info, size_universe);

        if(!res)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "\t\tEmpty info universe of size "
                << size_universe << " : ";
            passed_print(res);
        } 
    }

    std::cout << "\tUnit test empty info universe : ";
    passed_print(is_passed);

    return is_passed;
}

/**
 * @brief Create a universe (for classical computer science) of given size with void entities
*/
sp_univ_info build_empty_universe_info(int size_universe)
{
    sp_univ_info universe_info = std::make_shared<UniverseClassicalInfo>(
        size_universe,
        "universe test empty"
    );

    return universe_info;
}

/**
 * @brief Test if the built universe is full of void entities
*/
bool check_universe(sp_univ_info universe, int expected_size)
{
    bool is_passed = true;

    std::vector<sp_place> places = universe->get_places();

    if(verbose_unit_tests && places.size() != expected_size)
    {
        std::cout << "\t\t\tError : wrong universe size" << std::endl;
        std::cout << "\t\tExpected size : " << expected_size 
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
            std::cout << "\t\tExpected  : " << TYPE_VOID 
                << ", actual : " << entity->get_type()
                << std::endl;
            is_passed = false; 
        }
    }

    return is_passed;
}

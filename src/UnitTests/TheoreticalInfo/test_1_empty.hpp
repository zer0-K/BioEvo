#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/TheoreticalInfo/Universe/UniverseTheoreticalInfo.hpp"

/**
 * @brief Test universes of void entities
*/
bool launch_test_th_info_empty()
{
    sp_univ_th_info build_empty_universe_th_info(int);    
    bool check_universe(sp_univ_th_info, int);

    bool is_passed = true;

    std::cout << "Th info - empty : ";

    // sizes
    std::vector<int> sizes{
        0, 1, 2, 10, 100
    };

    for(int i=0; i<sizes.size(); i++)
    {
        int size_universe = sizes[i];

        // build theoretical computer science universe of wanted size
        sp_univ_th_info universe_th_info = build_empty_universe_th_info(size_universe);

        // check if built universe is correct
        bool res = check_universe(universe_th_info, size_universe);

        if(!res)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Th info - empty - size "
                << size_universe << " : ";
            passed_print(res);
        } 
    }

    std::cout << "Th info - empty : ";
    passed_print(is_passed);

    return is_passed;
}

/**
 * @brief Create a universe (for evolutionary biology) of given size with void entities
*/
sp_univ_th_info build_empty_universe_th_info(int size_universe)
{
    sp_univ_th_info universe_th_info = std::make_shared<UniverseTheoreticalInfo>(
        size_universe,
        "theoretical computer science universe"
    );

    return universe_th_info;
}

/**
 * @brief Test if the built universe is full of void entities
*/
bool check_universe(sp_univ_th_info universe, int expected_size)
{
    bool is_passed = true;

    std::vector<sp_place> places = universe->get_places();

    if(verbose_unit_tests && places.size() != expected_size)
    {
        std::cout << "\t\tError : wrong universe size" << std::endl;
        std::cout << "\tExpected size : " << expected_size 
            << ", actual size : " << places.size()
            << std::endl;
        is_passed = false;
    }

    for(int i=0; i<expected_size; i++)
    {
        sp_entity entity = places[i]->get_entity();
        
        if(verbose_unit_tests && entity->get_type() != TYPE_VOID)
        {
            std::cout << "\t\tError : wrong entity type" << std::endl;
            std::cout << "\tExpected  : " << TYPE_VOID 
                << ", actual : " << entity->get_type()
                << std::endl;
            is_passed = false; 
        }
    }

    return is_passed;
}






#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/Economy/Universe/UniverseEconomy.hpp"

/**
 * @brief Test universes of void entities
*/
bool launch_test_economy_empty()
{
    sp_univ_economy build_empty_universe_economy(int);    
    bool check_universe(sp_univ_economy, int);

    bool is_passed = true;

    std::cout << "Economy - empty : ";

    // sizes
    std::vector<int> sizes{
        0, 1, 2, 10, 100
    };

    for(int i=0; i<sizes.size(); i++)
    {
        int size_universe = sizes[i];

        // build economy universe of wanted size
        sp_univ_economy universe_economy = build_empty_universe_economy(size_universe);

        // check if built universe is correct
        bool res = check_universe(universe_economy, size_universe);

        if(!res)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Economy - empty - size "
                << size_universe << " : ";
            passed_print(res);
        } 
    }

    std::cout << "Economy - empty : ";
    passed_print(is_passed);

    return is_passed;
}

/**
 * @brief Create a universe (for evolutionary biology) of given size with void entities
*/
sp_univ_economy build_empty_universe_economy(int size_universe)
{
    sp_univ_economy universe_economy = std::make_shared<UniverseEconomy>(
        size_universe,
        "economy universe"
    );

    return universe_economy;
}

/**
 * @brief Test if the built universe is full of void entities
*/
bool check_universe(sp_univ_economy universe, int expected_size)
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



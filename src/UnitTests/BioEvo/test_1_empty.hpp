#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/BioEvo/Universe/UniverseBioEvo.hpp"

/**
 * @brief Test universes of void entities
*/
bool launch_test_bio_evo_empty()
{
    sp_univ_bio_evo build_empty_universe_bio_evo(int);    
    bool check_universe(sp_univ_bio_evo, int);

    bool is_passed = true;

    std::cout << "Bioevo - empty : ";

    // sizes
    std::vector<int> sizes{
        0, 1, 2, 10, 100
    };

    for(int i=0; i<sizes.size(); i++)
    {
        int size_universe = sizes[i];

        // build bio evo universe of wanted size
        sp_univ_bio_evo universe_bio_evo = build_empty_universe_bio_evo(size_universe);

        // check if built universe is correct
        bool res = check_universe(universe_bio_evo, size_universe);

        if(!res)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Bioevo - empty - size "
                << size_universe << " : ";
            passed_print(res);
        } 
    }

    std::cout << "Bioevo - empty : ";
    passed_print(is_passed);

    return is_passed;
}

/**
 * @brief Create a universe (for evolutionary biology) of given size with void entities
*/
sp_univ_bio_evo build_empty_universe_bio_evo(int size_universe)
{
    sp_univ_bio_evo universe_bio_evo = std::make_shared<UniverseBioEvo>(
        size_universe,
        "bio evo universe"
    );

    return universe_bio_evo;
}

/**
 * @brief Test if the built universe is full of void entities
*/
bool check_universe(sp_univ_bio_evo universe, int expected_size)
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

// -------------------- VOID

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"

namespace ut_ce
{

    /**
     * @brief Test universes of void entities
    */
    bool launch_test_code_eaters_void()
    {
        sp_univ_code_eaters build_universe_code_eaters_void(int);    
        bool check_universe_code_eaters_void(sp_univ_code_eaters, int);

        bool is_passed = true;

        // sizes
        std::vector<int> sizes{
            0, 1, 2, 10, 100
        };

        for(int i=0; i<sizes.size(); i++)
        {
            int size_universe = sizes[i];

            // build code eaters universe of wanted size
            sp_univ_code_eaters universe_code_eaters = build_universe_code_eaters_void(size_universe);

            // check if built universe is correct
            bool res = check_universe_code_eaters_void(universe_code_eaters, size_universe);

            is_passed &= res;

            if(verbose_unit_tests)
            {
                std::cout << "\t\t\tCode eaters universe of void entities of size "
                    << size_universe << " : ";
                passed_print(res, 1);
            } 
        }

        std::cout << "\t\tUnit test code eaters universe of void entities : ";
        passed_print(is_passed, 1);

        return is_passed;
    }

    /**
     * @brief Create a universe (for evolutionary biology) of given size with void entities
    */
    sp_univ_code_eaters build_universe_code_eaters_void(int size_universe)
    {
        sp_univ_code_eaters universe_code_eaters = std::make_shared<UniverseCodeEaters>(
            size_universe,
            "code eaters universe void"
        );

        return universe_code_eaters;
    }

    /**
     * @brief Test if the built universe is full of void entities
    */
    bool check_universe_code_eaters_void(sp_univ_code_eaters universe, int expected_size)
    {
        bool is_passed = true;

        std::vector<sp_place> places = universe->get_places();

        if(places.size() != expected_size)
        {
            is_passed = false;

            if(verbose_unit_tests)
            {
                std::cout << "\t\t\tError : wrong universe size" << std::endl;
                std::cout << "\t\t\t\tExpected size : " << expected_size 
                    << ", actual size : " << places.size()
                    << std::endl;
            }
        }

        for(int i=0; i<expected_size; i++)
        {
            sp_entity entity = places[i]->get_entity();
            
            if(entity->get_type() != TYPE_VOID)
            {
                is_passed = false;

                if(verbose_unit_tests)
                {
                    std::cout << "\t\t\tError : wrong entity type" << std::endl;
                    std::cout << "\t\t\t\tExpected  : " << TYPE_VOID 
                        << ", actual : " << entity->get_type()
                        << std::endl;
                } 
            }
        }

        return is_passed;
    }

}
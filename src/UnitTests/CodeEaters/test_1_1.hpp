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
        bool test_code_eaters_void_single(int);

        bool is_passed = true;

        std::cout << "Code eaters - empty - void : " << std::endl;

        // sizes
        std::vector<int> sizes{
            0, 1, 2, 10, 100
        };

        for(int i=0; i<sizes.size(); i++)
        {
            int size_universe = sizes[i];

            is_passed &= test_code_eaters_void_single(size_universe);
        }

        std::cout << "Code eaters - empty - void : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief run a single unit test for void entitiy universe
    */
    bool test_code_eaters_void_single(int size)
    {
        sp_univ_code_eaters build_universe_code_eaters_void(int);    
        bool check_universe_code_eaters_void(sp_univ_code_eaters, int);

        bool is_passed = true;

        // build code eaters universe of wanted size
        sp_univ_code_eaters universe_code_eaters = build_universe_code_eaters_void(size);

        // check if built universe is correct
        bool res = check_universe_code_eaters_void(universe_code_eaters, size);

        is_passed &= res;

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - empty - void - size "
                << size << " : ";
            passed_print(res);
        }

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
                std::cout << "\tError : wrong universe size" << std::endl;
                std::cout << "\t\tExpected size : " << expected_size 
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
                    std::cout << "\tError : wrong entity type" << std::endl;
                    std::cout << "\t\tExpected  : " << TYPE_VOID 
                        << ", actual : " << entity->get_type()
                        << std::endl;
                } 
            }
        }

        return is_passed;
    }

}
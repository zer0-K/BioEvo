//-------------------- EMPTY

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/ClassicalAlgos/Universe/UniverseClassicalAlgos.hpp"

namespace ut_ca
{

    /**
     * @brief Test universes of void entities
     */
    bool launch_tests_classical_algos_empty()
    {
        bool classical_algos_test_empty_universe(int);

        bool is_passed = true;

        std::cout << "Classical algos - empty :" << std::endl;

        // sizes
        std::vector<int> sizes{
            0, 1, 2, 10, 100
        };

        for(int i=0; i<sizes.size(); i++)
        {
            is_passed &= classical_algos_test_empty_universe(sizes[i]);
        }

        std::cout << "Classical algos - empty : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief test an empty universe of given size
    */
    bool classical_algos_test_empty_universe(int size)
    {
        sp_univ_algos classical_algos_empty_build_universe(int);    
        bool classical_algos_empty_check_universe(sp_univ_algos, int);

        bool is_passed = true;

        // build info universe of wanted size
        sp_univ_algos universe_algos = classical_algos_empty_build_universe(size);

        // check if built universe is correct
        is_passed = classical_algos_empty_check_universe(universe_algos, size);

        if(verbose_unit_tests)
        {
            std::cout << "Classical algos - empty - size "
                << size << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief Create a universe (for classical algorithms) of given size with void entities
     */
    sp_univ_algos classical_algos_empty_build_universe(int size_universe)
    {
        sp_univ_algos universe_algos = std::make_shared<UniverseClassicalAlgos>(
            size_universe,
            "empty classical algos universe"
        );

        return universe_algos;
    }  

    /**
     * @brief Test if the built universe is full of void entities
    */
    bool classical_algos_empty_check_universe(sp_univ_algos universe, int expected_size)
    {
        bool is_passed = true;

        std::vector<sp_place> places = universe->get_places();

        if(verbose_unit_tests && places.size() != expected_size)
        {
            std::cout << "\tError : wrong universe size" << std::endl;
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
                std::cout << "\tError : wrong entity type" << std::endl;
                std::cout << "\t\tExpected  : " << TYPE_VOID 
                    << ", actual : " << entity->get_type()
                    << std::endl;
                is_passed = false; 
            }
        }

        return is_passed;
    }

}

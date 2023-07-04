// -------------------- types entities

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"

namespace ut_ce 
{

    /**
     * @brief Test universes with entities for each type
    */
    bool launch_test_code_eaters_types()
    {
        bool run_single_type(int, std::string);

        bool is_passed = true;
        bool is_passed_bool = true;
        bool is_passed_int = true;

        // sizes
        std::vector<int> sizes{
            1, 2, 10, 100
        };

        for(int i=0; i<sizes.size(); i++)
        {
            int size_universe = sizes[i];

            is_passed_bool &= run_single_type(size_universe, TYPE_BOOL);
            is_passed_int &= run_single_type(size_universe, TYPE_INT);
        }

        if(verbose_unit_tests)
        {
            std::cout << "\t\t\tUnit test code eaters universe of bool entities : ";
            passed_print(is_passed_bool, 1);

            std::cout << "\t\t\tUnit test code eaters universe of int entities : ";
            passed_print(is_passed_int, 1); 
        }

        is_passed = is_passed_bool
            && is_passed_int;

        std::cout << "\t\tUnit test code eaters universe of basic type entities : ";
        passed_print(is_passed, 1);

        return is_passed;
    }

    /**
     * @brief Runs a single unit test for a given type of a given size
    */
    bool run_single_type(int size, std::string type_code_eater)
    {
        sp_univ_code_eaters build_universe_code_eaters_type(std::string, int);
        bool check_universe_code_eaters_type(std::string, int, sp_univ_code_eaters);
        
        bool is_passed = true;
            
        // build universe for code eaters of wanted type
        sp_univ_code_eaters universe_code_eaters = build_universe_code_eaters_type(type_code_eater, size);

        // check if code eaters of the universe are of the correct type 
        bool res = check_universe_code_eaters_type(type_code_eater, size, universe_code_eaters);

        if(verbose_unit_tests)
        {
            std::cout << "\t\t\t\tCode eaters universe of "
                << type_code_eater <<" entities of size "
                << size << " : ";
            passed_print(is_passed, 1);
        } 

        return is_passed;
    }

    /**
     * @brief Create a universe of given size with entities of given types
     * 
     * Set the values of the entities with a certain function
     * For example, can set the bool at place 'i' with value 'i%2==0'
    */
    sp_univ_code_eaters build_universe_code_eaters_type(std::string type_code_eater, int size_universe)
    {
        bool func_1_2_bool(int);
        int func_1_2_int(int);

        // fill the places of the universe with entities
        auto places = std::vector<sp_place>(size_universe);

        for(int i=0;i<size_universe;i++)
        {
            sp_entity entity;

            std::string name = type_code_eater + " entity " + std::to_string(i);

            if(type_code_eater == TYPE_BOOL)
            {
                entity = std::make_shared<EntityBool>(name, func_1_2_bool(i));
            } 
            else if(type_code_eater == TYPE_INT)
            {
                entity = std::make_shared<EntityInt>(name, func_1_2_int(i));
            }
            else
            {
                entity = std::make_shared<EntityVoid>(name);
            }

            entity->init();
                
            // place with freshly created entity
            sp_place place = std::make_shared<Place>(entity, i);
            places[i] = place;
        }

        // create the universe
        sp_univ_code_eaters universe_code_eaters = std::make_shared<UniverseCodeEaters>(
            "code eaters universe " + type_code_eater + " " + std::to_string(size_universe),
            places
        );

        return universe_code_eaters;
    }

    /**
     * @brief Test if the built universe is full of the correct entities
    */
    bool check_universe_code_eaters_type(std::string expected_type, int expected_size, sp_univ_code_eaters universe)
    {
        bool check_code_eaters_type_type(sp_entity, std::string);
        bool check_code_eaters_type_value(sp_entity, std::string, int);

        bool is_passed = true;

        std::vector<sp_place> places = universe->get_places();

        if(places.size() != expected_size)
        {
            is_passed = false;

            if(verbose_unit_tests)
            {
                std::cout << "\t\t\t\tError : wrong universe size" << std::endl;
                std::cout << "\t\t\t\t\tExpected size : " << expected_size 
                    << ", actual size : " << places.size()
                    << std::endl;
            }
        }

        for(int i=0; i<expected_size; i++)
        {
            sp_entity entity = places[i]->get_entity();
            
            bool good_type = check_code_eaters_type_type(entity, expected_type);
            
            is_passed &= good_type;
            if(good_type)
            {
            is_passed &= check_code_eaters_type_value(entity, expected_type, i); 
            }
        }

        return is_passed;
    }

    bool check_code_eaters_type_type(sp_entity entity, std::string expected_type)
    {
        bool is_passed = true;

        if(entity->get_type() != expected_type)
        {
            is_passed = false;

            if(verbose_unit_tests)
            {
                std::cout << "\t\t\t\tError : wrong entity type" << std::endl
                    << "\t\t\t\t\tExpected  : " << expected_type 
                    << ", actual : "            << entity->get_type()
                    << std::endl;
            } 
        }

        return is_passed;
    }

    bool check_code_eaters_type_value(sp_entity entity, std::string entity_type, int i)
    {
        bool func_1_2_bool(int);
        int func_1_2_int(int);

        bool is_passed = true;

        if(entity->get_type() != entity_type)
        {
            is_passed = false;

            if(verbose_unit_tests)
            {
                std::cout << "\t\t\t\tError : wrong entity type" << std::endl
                    << "\t\t\t\t\tExpected  : " << entity_type 
                    << ", actual : "        << entity->get_type()
                    << std::endl;
            }
        }

        if(entity_type == TYPE_BOOL)
        {
            if(!entity->has_value_bool())
            {
                is_passed = false;

                if(verbose_unit_tests)
                {
                    std::cout << "\t\t\t\tError : bool entity has no bool value" << std::endl;
                }
            }

            if(entity->get_value_bool() != func_1_2_bool(i))
            {
                is_passed = false;

                if(verbose_unit_tests)
                {
                    std::cout << "\t\t\t\tError : wrong entity value" << std::endl
                        << "\t\t\t\t\tExpected  : " << func_1_2_bool(i) 
                        << ", actual : "        << entity->get_value_bool()
                        << std::endl;
                }
            }
        }
        else if(entity_type == TYPE_INT)
        {
            if(!entity->has_value_int())
            {
                is_passed = false;

                if(verbose_unit_tests)
                {
                    std::cout << "\t\t\t\tError : int entity has no int value" << std::endl;
                }
            }

            if(entity->get_value_int() != func_1_2_int(i))
            {
                is_passed = false;

                if(verbose_unit_tests)
                {
                    std::cout << "\t\t\t\tError : wrong entity value" << std::endl
                        << "\t\t\t\t\tExpected  : " << func_1_2_int(i) 
                        << ", actual : "        << entity->get_value_int()
                        << std::endl;
                }
            }
        }

        return is_passed;
    }

    bool func_1_2_bool(int i)
    {
        bool func_1_2_bool_0(int);
        bool func_1_2_bool_1(int);

        return func_1_2_bool_1(i);
    }

    bool func_1_2_bool_0(int i)
    {
        return true;
    }

    bool func_1_2_bool_1(int i)
    {
        return i%2==0;
    }

    int func_1_2_int(int i)
    {
        int func_1_2_int_0(int);
        int func_1_2_int_1(int);

        return func_1_2_int_0(i);
    }

    int func_1_2_int_0(int i)
    {
        return i;
    }

    int func_1_2_int_1(int i)
    {
        return i*i;
    }

}
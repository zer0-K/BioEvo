// -------------------- CODE EATERS - OPERATIONS - INT - BASIC - UNARY

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Entities/Base/Int/EntityIncr.hpp"

namespace ut_ce
{
    /**
     * @brief Test simple boolean operations with code eaters
    */
    bool launch_test_code_eaters_operations_ints_basic_unary()
    {
        bool test_code_eaters_operations_int_incr(void);
        
        bool is_passed = true;

        std::cout << "Code eaters - operations - int - basic - unary : " << std::endl;

        is_passed &= test_code_eaters_operations_int_incr();
        
        std::cout << "Code eaters - operations - int - basic - unary : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief test incrementation 
    */
    bool test_code_eaters_operations_int_incr()
    {
        bool is_passed = true;

        sp_entity_incr entity_incr = std::make_shared<EntityIncr>("increment entity");
        entity_incr->init();
        std::vector<sp_entity> res;


        //---------- test with negative and positive values 


        int nb_tests = 12;

        for(int i=-nb_tests/2;i<nb_tests/2;i++)
        {
            sp_entity_int entity_int = std::make_shared<EntityInt>("entity int", i);
            entity_int->init();

            res = entity_incr->exec(std::vector<sp_entity>{entity_int});

            if(res.size() != 1 || !res[0]->has_value_int() || res[0]->get_value_int()!=i+1 )
            {
                is_passed = false;
                std::cout << "\tError : incrementation did not work with " 
                << std::to_string(i) << std::endl;
            }
        }


        //---------- test with list of ints
       
        std::vector<sp_entity> entities = {
            std::make_shared<EntityInt>("entity list 0 - int", -12),
            std::make_shared<EntityBool>("entity list 1 - bool", true),
            std::make_shared<EntityInt>("entity list 2 - int", 0),
            std::make_shared<EntityInt>("entity list 3 - int", 4),
        };
        for(int i=0;i<entities.size();i++)
        {
            entities[i]->init();
        }

        res = entity_incr->exec(entities);

        if(res.size() != 4
            || !res[0]->has_value_int() || res[0]->get_value_int() !=-11 
            || !res[1]->has_value_bool() || res[1]->get_value_bool() != true
            || !res[2]->has_value_int() || res[2]->get_value_int() != 1 
            || !res[3]->has_value_int() || res[3]->get_value_int() != 5 
            )
        {
            is_passed = false;
            std::cout << "\tError : incrementation did not work on list of entities" << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - int - basic - incrementation : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    
}
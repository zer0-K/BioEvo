// -------------------- OPERATIONS - ASSEMBLY - TYPE FREE

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityBoolId.hpp"

namespace ut_ce
{
    /**
     * @brief Test simple boolean operations with code eaters
    */
    bool launch_test_code_eaters_operations_assembly_typefree()
    {
        bool test_code_eaters_operations_assembly_(void);
        
        bool is_passed = true;

        std::cout << "\t\t\tType free operations : " << std::endl;

        is_passed &= test_code_eaters_operations_assembly_();
        
        std::cout << "\t\t\tType free operations : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief test boolean id
    */
    bool test_code_eaters_operations_assembly_()
    {
        bool is_passed = true;

        sp_entity_boolid entity_boolid = std::make_shared<EntityBoolId>("boolean id entity");
        std::vector<sp_entity> res;


        //---------- test on bool entities and other types


        //----- true entity

        sp_entity_bool entity_true = std::make_shared<EntityBool>("entity true", true);
        entity_true->init();

        res = entity_boolid->exec(std::vector<sp_entity>{entity_true});

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\tError : boolean id did not work on true entity" << std::endl;
        }


        //----- false entity

        sp_entity_bool entity_false = std::make_shared<EntityBool>("entity false", false);
        entity_false->init();

        res = entity_boolid->exec(std::vector<sp_entity>{entity_false});

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\tError : boolean id did not work on false entity" << std::endl;
        }


        //----- int entity

        sp_entity_int entity_int = std::make_shared<EntityInt>("entity int", 12);
        entity_int->init();

        res = entity_boolid->exec(std::vector<sp_entity>{entity_int});

        if(res.size() != 1 || res[0]->has_value_bool() || !res[0]->get_value_int() )
        {
            is_passed = false;
            std::cout << "\t\tError : boolean id did not work on int entity" << std::endl;
        }


        //----- list of bool entities

        std::vector<sp_entity> entities_bool = {
            std::make_shared<EntityBool>("entity bool list 0", true),
            std::make_shared<EntityBool>("entity bool list 1", true),
            std::make_shared<EntityBool>("entity bool list 2", false),
            std::make_shared<EntityBool>("entity bool list 3", true),
            std::make_shared<EntityBool>("entity bool list 4", false)
        };
        for(int i=0;i<entities_bool.size();i++)
        {
            entities_bool[i]->init();
        }

        res = entity_boolid->exec(entities_bool);

        if(res.size() != 5 
            || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || !res[1]->has_value_bool() || res[1]->get_value_bool() != true
            || !res[2]->has_value_bool() || res[2]->get_value_bool() != false
            || !res[3]->has_value_bool() || res[3]->get_value_bool() != true
            || !res[4]->has_value_bool() || res[4]->get_value_bool() != false
            )
        {
            is_passed = false;
            std::cout << "\t\tError : boolean id did not work on list entity" << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "\t\tTest code eaters - boolean functions - boolean id : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

}
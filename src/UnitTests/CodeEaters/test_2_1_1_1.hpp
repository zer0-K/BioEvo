// -------------------- OPERATIONS - BOOLEANS - BASIC - ID

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityBoolId.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNot.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityBoolIdIn.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNotIn.hpp"

namespace ut_ce
{
    /**
     * @brief Test id function on boolean code eaters 
    */
    bool launch_test_code_eaters_operations_booleans_basic_id()
    {
        bool test_code_eaters_operations_booleans_boolid(void);
        bool test_code_eaters_operations_booleans_not(void);
        bool test_code_eaters_operations_booleans_boolidin(void);
        bool test_code_eaters_operations_booleans_notin(void);

        bool is_passed = true;

        std::cout << "Code eaters - operations - booleans - basic - id : " << std::endl;

        is_passed &= test_code_eaters_operations_booleans_boolid();
        is_passed &= test_code_eaters_operations_booleans_not();
        is_passed &= test_code_eaters_operations_booleans_boolidin();
        is_passed &= test_code_eaters_operations_booleans_notin();

        std::cout << "Code eaters - operations - booleans - basic - id : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief boolean id
    */
    bool test_code_eaters_operations_booleans_boolid()
    {
        bool is_passed = true;

        sp_entity_boolid entity_boolid = std::make_shared<EntityBoolId>("boolean id entity");
        entity_boolid->init();


        //---------- test on bool entities and other types


        //----- explicitly test all possibilities 

        sp_entity_bool entity_res = std::make_shared<EntityBool>("entity res", false);
        sp_entity_bool entity_rop = std::make_shared<EntityBool>("entity right", true);
        entity_res->init();
        entity_rop->init();

        std::vector<sp_entity> entries = {
            entity_res, 
            entity_rop
        };


        // true 
        entries = entity_boolid->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_bool() || entries[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : boolean id did not work on true entity" << std::endl;
        }


        //false

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        entries = entity_boolid->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_bool() || entries[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : boolean id did not work on false entity" << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - booleans - basic - id - id : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief boolean not 
    */
    bool test_code_eaters_operations_booleans_not()
    {
        bool is_passed = true;

        sp_entity_not entity_not = std::make_shared<EntityNot>("not entity");
        entity_not->init();


        //---------- test on bool entities and other types


        //----- explicitly test all possibilities 

        sp_entity_bool entity_res = std::make_shared<EntityBool>("entity res", true);
        sp_entity_bool entity_rop = std::make_shared<EntityBool>("entity right", true);
        entity_res->init();
        entity_rop->init();

        std::vector<sp_entity> entries = {
            entity_res, 
            entity_rop
        };


        // true 
        entries = entity_not->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_bool() || entries[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NOT did not work on true entity" << std::endl;
        }


        //false

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        entries = entity_not->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_bool() || entries[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NOT did not work on false entity" << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - booleans - basic - id - not : ";
            passed_print(is_passed);
        }

        return is_passed;   
    }    
    
    /**
     * @brief boolean id, in place
    */
    bool test_code_eaters_operations_booleans_boolidin()
    {
        bool is_passed = true;

        sp_entity_boolidin entity_boolidin = std::make_shared<EntityBoolIdIn>("in place boolean id entity");
        entity_boolidin->init();


        //---------- test on bool entities and other types


        //----- explicitly test all possibilities 

        sp_entity_bool entity_res = std::make_shared<EntityBool>("entity res", true);
        entity_res->init();

        std::vector<sp_entity> entries = {
            entity_res
        };


        // true 
        entries = entity_boolidin->exec(entries);

        if(entries.size() != 1 || !entries[0]->has_value_bool() || entries[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place boolean id did not work on true entity" << std::endl;
        }


        //false

        entries[0]->set_value_bool(false);
        entries = entity_boolidin->exec(entries);

        if(entries.size() != 1 || !entries[0]->has_value_bool() || entries[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place boolean id did not work on false entity" << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - booleans - basic - id - id in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief boolean not, in place
    */
    bool test_code_eaters_operations_booleans_notin()
    {
        bool is_passed = true;

        sp_entity_notin entity_notin = std::make_shared<EntityNotIn>("in place not entity");
        entity_notin->init();


        //---------- test on bool entities and other types


        //----- explicitly test all possibilities 

        sp_entity_bool entity_res = std::make_shared<EntityBool>("entity res", true);
        entity_res->init();

        std::vector<sp_entity> entries = {
            entity_res
        };


        // true 
        entries = entity_notin->exec(entries);

        if(entries.size() != 1 || !entries[0]->has_value_bool() || entries[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place NOT did not work on true entity" << std::endl;
        }


        //false

        entries[0]->set_value_bool(false);
        entries = entity_notin->exec(entries);

        if(entries.size() != 1 || !entries[0]->has_value_bool() || entries[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NOT did not work on false entity" << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - booleans - basic - id - in place not : ";
            passed_print(is_passed);
        }

        return is_passed;   
    }
}
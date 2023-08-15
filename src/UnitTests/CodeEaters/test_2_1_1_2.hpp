// -------------------- OPERATIONS - BOOLEANS - BASIC - AND

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityAnd.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNand.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityAndIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNandIn.hpp"

namespace ut_ce
{
    /**
     * @brief Test and gates on boolean code eaters
    */
    bool launch_test_code_eaters_operations_boolean_basic_and()
    {
        bool test_code_eaters_operations_boolean_and(void);
        bool test_code_eaters_operations_boolean_nand(void);
        bool test_code_eaters_operations_boolean_andin(void);
        bool test_code_eaters_operations_boolean_nandin(void);

        bool is_passed = true;

        std::cout << "Code eaters - operations - boolean - basic - and : " << std::endl;

        is_passed &= test_code_eaters_operations_boolean_and();
        is_passed &= test_code_eaters_operations_boolean_nand();
        is_passed &= test_code_eaters_operations_boolean_andin();
        is_passed &= test_code_eaters_operations_boolean_nandin();
  
        std::cout << "Code eaters - operations - boolean - basic - and : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief test AND 
    */
    bool test_code_eaters_operations_boolean_and()
    {
        bool is_passed = true;

        sp_entity_and entity_and = std::make_shared<EntityAnd>("and entity");
        entity_and->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities and other types


        //----- explicitly test all possibilities 

        sp_entity_bool entity_res = std::make_shared<EntityBool>("entity res", false);
        sp_entity_bool entity_lop = std::make_shared<EntityBool>("entity left", true);
        sp_entity_bool entity_rop = std::make_shared<EntityBool>("entity right", true);
        entity_res->init();
        entity_lop->init();
        entity_rop->init();

        std::vector<sp_entity> entries = {
            entity_res, 
            entity_lop,
            entity_rop
        };


        // 1x1

        res = entity_and->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : AND did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(true);
        entries[2]->set_value_bool(false);
        res = entity_and->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : AND did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_and->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : AND did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(false);
        res = entity_and->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : AND did not work on false false" << std::endl;
        }


        //----- oversized and undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_and->exec(entries);

        if(res.size() != 4 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false
            || res[3]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : AND did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_and->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : AND did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - and - and : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test NAND 
    */
    bool test_code_eaters_operations_boolean_nand()
    {
        bool is_passed = true;

        sp_entity_nand entity_nand = std::make_shared<EntityNand>("and entity");
        entity_nand->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities and other types


        //----- explicitly test all possibilities 

        sp_entity_bool entity_res = std::make_shared<EntityBool>("entity res", true);
        sp_entity_bool entity_lop = std::make_shared<EntityBool>("entity left", true);
        sp_entity_bool entity_rop = std::make_shared<EntityBool>("entity right", true);
        entity_res->init();
        entity_lop->init();
        entity_rop->init();

        std::vector<sp_entity> entries = {
            entity_res, 
            entity_lop,
            entity_rop
        };


        // 1x1

        res = entity_nand->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NAND did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(true);
        entries[2]->set_value_bool(false);
        res = entity_nand->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NAND did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_nand->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NAND did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(false);
        res = entity_nand->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NAND did not work on false false" << std::endl;
        }


        //----- oversized and undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_nand->exec(entries);

        if(res.size() != 4 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false
            || res[3]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NAND did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_nand->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NAND did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - and - nand : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test AND, in place
    */
    bool test_code_eaters_operations_boolean_andin()
    {
        bool is_passed = true;

        sp_entity_andin entity_andin = std::make_shared<EntityAndIn>("in place and entity");
        entity_andin->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities and other types


        //----- explicitly test all possibilities 

        sp_entity_bool entity_res = std::make_shared<EntityBool>("entity res", true);
        sp_entity_bool entity_rop = std::make_shared<EntityBool>("entity right", true);
        entity_res->init();
        entity_rop->init();

        std::vector<sp_entity> entries = {
            entity_res, 
            entity_rop,
        };


        // 1x1

        res = entity_andin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place AND did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        res = entity_andin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place AND did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(true);
        res = entity_andin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place AND did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        res = entity_andin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place AND did not work on false false" << std::endl;
        }


        //----- oversized and undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_andin->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place AND did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_andin->exec(entries);

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place AND did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - and - and in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test NAND, in place
    */
    bool test_code_eaters_operations_boolean_nandin()
    {
        bool is_passed = true;

        sp_entity_nandin entity_nandin = std::make_shared<EntityNandIn>("in place nand entity");
        entity_nandin->init();
        std::vector<sp_entity> res;


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


        // 1x1

        res = entity_nandin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NAND did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        res = entity_nandin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place NAND did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(true);
        res = entity_nandin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NAND did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        res = entity_nandin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place NAND did not work on false false" << std::endl;
        }


        //----- oversized and undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_nandin->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NAND did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_nandin->exec(entries);

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NAND did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - and - nand in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

}
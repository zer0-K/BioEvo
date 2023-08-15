// -------------------- OPERATIONS - BOOLEANS - BASIC - OR 

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityOr.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNor.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityOrIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNorIn.hpp"

namespace ut_ce
{
    /**
     * @brief Test or gates on boolean code eaters
    */
    bool launch_test_code_eaters_operations_boolean_basic_or()
    {
        bool test_code_eaters_operations_boolean_or(void);
        bool test_code_eaters_operations_boolean_nor(void);
        bool test_code_eaters_operations_boolean_orin(void);
        bool test_code_eaters_operations_boolean_norin(void);

        bool is_passed = true;

        std::cout << "Code eaters - operations - boolean - basic - or : " << std::endl;

        is_passed &= test_code_eaters_operations_boolean_or();
        is_passed &= test_code_eaters_operations_boolean_nor();
        is_passed &= test_code_eaters_operations_boolean_orin();
        is_passed &= test_code_eaters_operations_boolean_norin();
  
        std::cout << "Code eaters - operations - boolean - basic - or : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief test OR 
    */
    bool test_code_eaters_operations_boolean_or()
    {
        bool is_passed = true;

        sp_entity_or entity_or = std::make_shared<EntityOr>("or entity");
        entity_or->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities or other types


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

        res = entity_or->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : OR did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(true);
        entries[2]->set_value_bool(false);
        res = entity_or->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : OR did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_or->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true 
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : OR did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(false);
        res = entity_or->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : OR did not work on false false" << std::endl;
        }


        //----- oversized or undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_or->exec(entries);

        if(res.size() != 4 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false
            || res[3]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : OR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_or->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : OR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - or - or : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test NOR 
    */
    bool test_code_eaters_operations_boolean_nor()
    {
        bool is_passed = true;

        sp_entity_nor entity_nor = std::make_shared<EntityNor>("or entity");
        entity_nor->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities or other types


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

        res = entity_nor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NOR did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(true);
        entries[2]->set_value_bool(false);
        res = entity_nor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NOR did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_nor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NOR did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(false);
        res = entity_nor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NOR did not work on false false" << std::endl;
        }


        //----- oversized or undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_nor->exec(entries);

        if(res.size() != 4 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false
            || res[3]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NOR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_nor->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NOR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - or - nor : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test OR, in place
    */
    bool test_code_eaters_operations_boolean_orin()
    {
        bool is_passed = true;

        sp_entity_orin entity_orin = std::make_shared<EntityOrIn>("in place or entity");
        entity_orin->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities or other types


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

        res = entity_orin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place OR did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        res = entity_orin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place OR did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(true);
        res = entity_orin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place OR did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        res = entity_orin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place OR did not work on false false" << std::endl;
        }


        //----- oversized or undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_orin->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place OR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_orin->exec(entries);

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place OR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - or - or in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test NOR, in place
    */
    bool test_code_eaters_operations_boolean_norin()
    {
        bool is_passed = true;

        sp_entity_norin entity_norin = std::make_shared<EntityNorIn>("in place nor entity");
        entity_norin->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities or other types


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

        res = entity_norin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NOR did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        res = entity_norin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place NOR did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(true);
        res = entity_norin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NOR did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        res = entity_norin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place NOR did not work on false false" << std::endl;
        }


        //----- oversized or undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_norin->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NOR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_norin->exec(entries);

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NOR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - or - nor in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

}
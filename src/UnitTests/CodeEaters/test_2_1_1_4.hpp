// -------------------- OPERATIONS - BOOLEANS - BASIC - XOR

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityXor.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNxor.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityXorIn.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNxorIn.hpp"

namespace ut_ce
{
    /**
     * @brief Test xor gates on boolean code eaters
    */
    bool launch_test_code_eaters_operations_booleans_basic_xor()
    {
        bool test_code_eaters_operations_booleans_xor(void);
        bool test_code_eaters_operations_booleans_nxor(void);
        bool test_code_eaters_operations_booleans_xorin(void);
        bool test_code_eaters_operations_booleans_nxorin(void);

        bool is_passed = true;

        std::cout << "Code eaters - operations - booleans - basic - xor : " << std::endl;

        is_passed &= test_code_eaters_operations_booleans_xor();
        is_passed &= test_code_eaters_operations_booleans_nxor();
        is_passed &= test_code_eaters_operations_booleans_xorin();
        is_passed &= test_code_eaters_operations_booleans_nxorin();
  
        std::cout << "Code eaters - operations - booleans - basic - xor : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief test XOR 
    */
    bool test_code_eaters_operations_booleans_xor()
    {
        bool is_passed = true;

        sp_entity_xor entity_xor = std::make_shared<EntityXor>("xor entity");
        entity_xor->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities xor other types


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

        res = entity_xor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : XOR did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(true);
        entries[2]->set_value_bool(false);
        res = entity_xor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : XOR did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_xor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : XOR did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(false);
        res = entity_xor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : XOR did not work on false false" << std::endl;
        }


        //----- oversized xor undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_xor->exec(entries);

        if(res.size() != 4 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false
            || res[3]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : XOR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_xor->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : XOR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - booleans - basic - xor - xor : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test NXOR 
    */
    bool test_code_eaters_operations_booleans_nxor()
    {
        bool is_passed = true;

        sp_entity_nxor entity_nxor = std::make_shared<EntityNxor>("xor entity");
        entity_nxor->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities xor other types


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

        res = entity_nxor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NXOR did not work on true true" << std::endl;
        }

        // 1x0

        entries[1]->set_value_bool(true);
        entries[2]->set_value_bool(false);
        res = entity_nxor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NXOR did not work on true false" << std::endl;
        }

        // 0x1

        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_nxor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NXOR did not work on false true" << std::endl;
        }

        // 0x0

        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(false);
        res = entity_nxor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NXOR did not work on false false" << std::endl;
        }


        //----- oversized xor undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_nxor->exec(entries);

        if(res.size() != 4 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false
            || res[3]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : NXOR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_nxor->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : NXOR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - booleans - basic - xor - nxor : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test XOR, in place
    */
    bool test_code_eaters_operations_booleans_xorin()
    {
        bool is_passed = true;

        sp_entity_xorin entity_xorin = std::make_shared<EntityXorIn>("in place xor entity");
        entity_xorin->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities xor other types


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

        res = entity_xorin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place XOR did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        res = entity_xorin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place XOR did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(true);
        res = entity_xorin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place XOR did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        res = entity_xorin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place XOR did not work on false false" << std::endl;
        }


        //----- oversized xor undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_xorin->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place XOR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_xorin->exec(entries);

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place XOR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - xor - xor in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test NXOR, in place
    */
    bool test_code_eaters_operations_booleans_nxorin()
    {
        bool is_passed = true;

        sp_entity_nxorin entity_nxorin = std::make_shared<EntityNxorIn>("in place nxor entity");
        entity_nxorin->init();
        std::vector<sp_entity> res;


        //---------- test on bool entities xor other types


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

        res = entity_nxorin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NXOR did not work on true true" << std::endl;
        }

        // 1x0

        entries[0]->set_value_bool(true);
        entries[1]->set_value_bool(false);
        res = entity_nxorin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place NXOR did not work on true false" << std::endl;
        }

        // 0x1

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(true);
        res = entity_nxorin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NXOR did not work on false true" << std::endl;
        }

        // 0x0

        entries[0]->set_value_bool(false);
        entries[1]->set_value_bool(false);
        res = entity_nxorin->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\tError : in place NXOR did not work on false false" << std::endl;
        }


        //----- oversized xor undersized arrays

        // oversize

        sp_entity_bool entity_over = std::make_shared<EntityBool>("entity over", true);
        entity_over->init();
        entries.push_back(entity_over);

        res = entity_nxorin->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NXOR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_nxorin->exec(entries);

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\tError : in place NXOR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - boolean - basic - xor - nxor in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

}
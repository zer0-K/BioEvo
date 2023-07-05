// -------------------- OPERATIONS - BOOLEANS - BASIC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Entities/EntityUnaryId.hpp"
#include "../../Models/CodeEaters/Entities/EntityUnaryNot.hpp"
#include "../../Models/CodeEaters/Entities/EntityAnd.hpp"
#include "../../Models/CodeEaters/Entities/EntityOr.hpp"
#include "../../Models/CodeEaters/Entities/EntityXor.hpp"
#include "../../Models/CodeEaters/Entities/EntityNand.hpp"
#include "../../Models/CodeEaters/Entities/EntityNor.hpp"
#include "../../Models/CodeEaters/Entities/EntityNxor.hpp"

namespace ut_ce
{
    /**
     * @brief Test simple boolean operations with code eaters
    */
    bool launch_test_code_eaters_operations_booleans_basic()
    {
        bool test_code_eaters_operations_booleans_uid(void);
        bool test_code_eaters_operations_booleans_unot(void);
        bool test_code_eaters_operations_booleans_and(void);
        bool test_code_eaters_operations_booleans_or(void);
        bool test_code_eaters_operations_booleans_xor(void);
        bool test_code_eaters_operations_booleans_nand(void);
        bool test_code_eaters_operations_booleans_nor(void);
        bool test_code_eaters_operations_booleans_nxor(void);

        bool is_passed = true;

        std::cout << "\t\t\tBasic boolean operations : " << std::endl;

        is_passed &= test_code_eaters_operations_booleans_uid();
        is_passed &= test_code_eaters_operations_booleans_unot();
        is_passed &= test_code_eaters_operations_booleans_and();
        is_passed &= test_code_eaters_operations_booleans_or();
        is_passed &= test_code_eaters_operations_booleans_xor();
        is_passed &= test_code_eaters_operations_booleans_nand();
        is_passed &= test_code_eaters_operations_booleans_nor();
        is_passed &= test_code_eaters_operations_booleans_nxor();

        std::cout << "\t\t\tBasic boolean operations : ";
        passed_print(is_passed, 1);

        return is_passed;
    }

    /**
     * @brief test unitary id
    */
    bool test_code_eaters_operations_booleans_uid()
    {
        bool is_passed = true;

        sp_entity_uid entity_uid = std::make_shared<EntityUnaryId>("unitary id entity");
        std::vector<sp_entity> res;


        //---------- test on bool entities and other types


        //----- true entity

        sp_entity_bool entity_true = std::make_shared<EntityBool>("entity true", true);
        entity_true->init();

        res = entity_uid->exec(std::vector<sp_entity>{entity_true});

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : unitary id did not work on true entity" << std::endl;
        }


        //----- false entity

        sp_entity_bool entity_false = std::make_shared<EntityBool>("entity false", false);
        entity_false->init();

        res = entity_uid->exec(std::vector<sp_entity>{entity_false});

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : unitary id did not work on false entity" << std::endl;
        }


        //----- int entity

        sp_entity_int entity_int = std::make_shared<EntityInt>("entity int", 12);
        entity_int->init();

        res = entity_uid->exec(std::vector<sp_entity>{entity_int});

        if(res.size() != 1 || res[0]->has_value_bool() || !res[0]->get_value_int() )
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : unitary id did not work on int entity" << std::endl;
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

        res = entity_uid->exec(entities_bool);

        if(res.size() != 5 
            || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || !res[1]->has_value_bool() || res[1]->get_value_bool() != true
            || !res[2]->has_value_bool() || res[2]->get_value_bool() != false
            || !res[3]->has_value_bool() || res[3]->get_value_bool() != true
            || !res[4]->has_value_bool() || res[4]->get_value_bool() != false
            )
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : unitary id did not work on list entity" << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "\t\t\t\tTest code eaters - boolean functions - unitary id : ";
            passed_print(is_passed, 1);
        }

        return is_passed;
    }

    /**
     * @brief test unitary not 
    */
    bool test_code_eaters_operations_booleans_unot()
    {
        bool is_passed = true;

        sp_entity_unot entity_unot = std::make_shared<EntityUnaryNot>("unitary not entity");
        std::vector<sp_entity> res;


        //---------- test on bool entities and other types


        //----- true entity

        sp_entity_bool entity_true = std::make_shared<EntityBool>("entity true", true);
        entity_true->init();

        res = entity_unot->exec(std::vector<sp_entity>{entity_true});

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : unitary not did not work on true entity" << std::endl;
        }


        //----- false entity

        sp_entity_bool entity_false = std::make_shared<EntityBool>("entity false", false);
        entity_false->init();

        res = entity_unot->exec(std::vector<sp_entity>{entity_false});

        if(res.size() != 1 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : unitary not did not work on false entity" << std::endl;
        }


        //----- int entity

        sp_entity_int entity_int = std::make_shared<EntityInt>("entity int", 12);
        entity_int->init();

        res = entity_unot->exec(std::vector<sp_entity>{entity_int});

        if(res.size() != 1 || res[0]->has_value_bool() || !res[0]->get_value_int() )
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : unitary not did not work on int entity" << std::endl;
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

        res = entity_unot->exec(entities_bool);

        if(res.size() != 5 
            || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || !res[1]->has_value_bool() || res[1]->get_value_bool() != false
            || !res[2]->has_value_bool() || res[2]->get_value_bool() != true
            || !res[3]->has_value_bool() || res[3]->get_value_bool() != false
            || !res[4]->has_value_bool() || res[4]->get_value_bool() != true 
            )
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : unitary not did not work on list entity" << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "\t\t\t\tTest code eaters - boolean functions - unitary not : ";
            passed_print(is_passed, 1);
        }

        return is_passed;
    }

    /**
     * @brief test AND 
    */
    bool test_code_eaters_operations_booleans_and()
    {
        bool is_passed = true;

        sp_entity_and entity_and = std::make_shared<EntityAnd>("and entity");
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

        res = entity_and->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : AND did not work on true true" << std::endl;
        }

        // 1x0

        entries[2]->set_value_bool(false);
        res = entity_and->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : AND did not work on true false" << std::endl;
        }

        // 0x1

        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_and->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : AND did not work on false true" << std::endl;
        }

        // 0x0

        entries[2]->set_value_bool(false);
        res = entity_and->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : AND did not work on false false" << std::endl;
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
            std::cout << "\t\t\t\tError : AND did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_and->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : AND did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "\t\t\t\tTest code eaters - boolean functions - and : ";
            passed_print(is_passed, 1);
        }

        return is_passed;
    }

    /**
     * @brief test OR 
    */
    bool test_code_eaters_operations_booleans_or()
    {
        bool is_passed = true;

        sp_entity_or entity_or = std::make_shared<EntityOr>("or entity");
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

        res = entity_or->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : OR did not work on true true" << std::endl;
        }

        // 1x0

        entries[2]->set_value_bool(false);
        res = entity_or->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : OR did not work on true false" << std::endl;
        }

        // 0x1

        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_or->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : OR did not work on false true" << std::endl;
        }

        // 0x0

        entries[2]->set_value_bool(false);
        res = entity_or->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : OR did not work on false false" << std::endl;
        }


        //----- oversized and undersized arrays

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
            std::cout << "\t\t\t\tError : OR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_or->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : OR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "\t\t\t\tTest code eaters - boolean functions - or : ";
            passed_print(is_passed, 1);
        }

        return is_passed;
    }

    /**
     * @brief test XOR 
    */
    bool test_code_eaters_operations_booleans_xor()
    {
        bool is_passed = true;

        sp_entity_xor entity_xor = std::make_shared<EntityXor>("xor entity");
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

        res = entity_xor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : XOR did not work on true true" << std::endl;
        }

        // 1x0

        entries[2]->set_value_bool(false);
        res = entity_xor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : XOR did not work on true false" << std::endl;
        }

        // 0x1

        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_xor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : XOR did not work on false true" << std::endl;
        }

        // 0x0

        entries[2]->set_value_bool(false);
        res = entity_xor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : XOR did not work on false false" << std::endl;
        }


        //----- oversized and undersized arrays

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
            std::cout << "\t\t\t\tError : XOR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_xor->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : XOR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "\t\t\t\tTest code eaters - boolean functions - xor : ";
            passed_print(is_passed, 1);
        }

        return is_passed;
    }

    /**
     * @brief test NAND 
    */
    bool test_code_eaters_operations_booleans_nand()
    {
        bool is_passed = true;

        sp_entity_nand entity_nand = std::make_shared<EntityNand>("and entity");
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
            std::cout << "\t\t\t\tError : NAND did not work on true true" << std::endl;
        }

        // 1x0

        entries[2]->set_value_bool(false);
        res = entity_nand->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NAND did not work on true false" << std::endl;
        }

        // 0x1

        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_nand->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NAND did not work on false true" << std::endl;
        }

        // 0x0

        entries[2]->set_value_bool(false);
        res = entity_nand->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NAND did not work on false false" << std::endl;
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
            std::cout << "\t\t\t\tError : NAND did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_nand->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NAND did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "\t\t\t\tTest code eaters - boolean functions - nand : ";
            passed_print(is_passed, 1);
        }

        return is_passed;
    }

    /**
     * @brief test NOR 
    */
    bool test_code_eaters_operations_booleans_nor()
    {
        bool is_passed = true;

        sp_entity_nor entity_nor = std::make_shared<EntityNor>("or entity");
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

        res = entity_nor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NOR did not work on true true" << std::endl;
        }

        // 1x0

        entries[2]->set_value_bool(false);
        res = entity_nor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NOR did not work on true false" << std::endl;
        }

        // 0x1

        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_nor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NOR did not work on false true" << std::endl;
        }

        // 0x0

        entries[2]->set_value_bool(false);
        res = entity_nor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NOR did not work on false false" << std::endl;
        }


        //----- oversized and undersized arrays

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
            std::cout << "\t\t\t\tError : NOR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_nor->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NOR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "\t\t\t\tTest code eaters - boolean functions - nor : ";
            passed_print(is_passed, 1);
        }

        return is_passed;
    }

    /**
     * @brief test NXOR 
    */
    bool test_code_eaters_operations_booleans_nxor()
    {
        bool is_passed = true;

        sp_entity_nxor entity_nxor = std::make_shared<EntityNxor>("nxor entity");
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

        res = entity_nxor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NXOR did not work on true true" << std::endl;
        }

        // 1x0

        entries[2]->set_value_bool(false);
        res = entity_nxor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != true || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NXOR did not work on true false" << std::endl;
        }

        // 0x1

        entries[1]->set_value_bool(false);
        entries[2]->set_value_bool(true);
        res = entity_nxor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != false
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != true)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NXOR did not work on false true" << std::endl;
        }

        // 0x0

        entries[2]->set_value_bool(false);
        res = entity_nxor->exec(entries);

        if(res.size() != 3 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false || res[2]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NXOR did not work on false false" << std::endl;
        }


        //----- oversized and undersized arrays

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
            std::cout << "\t\t\t\tError : NXOR did not work on oversized list of entities" << std::endl;
        }

        // undersize

        entries.pop_back();
        entries.pop_back();
        res = entity_nxor->exec(entries);

        if(res.size() != 2 || !res[0]->has_value_bool() || res[0]->get_value_bool() != true
            || res[1]->get_value_bool() != false)
        {
            is_passed = false;
            std::cout << "\t\t\t\tError : NXOR did not work on undersized list of entities" << std::endl;
        }


        if(verbose_unit_tests)
        {
            std::cout << "\t\t\t\tTest code eaters - boolean functions - nxor : ";
            passed_print(is_passed, 1);
        }

        return is_passed;
    }

 
}
// -------------------- META DATA - COUNTER 

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityBoolId.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityBoolIdIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNot.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNotIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityAnd.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNand.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityAndIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNandIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityOr.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNor.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityOrIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNorIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityXor.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNxor.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityXorIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Boolean/EntityNxorIn.hpp"
#include "../../Models/CodeEaters/Entities/Base/Meta/EntityOpCounter.hpp"


namespace ut_ce 
{
    /**
     * @brief Test simple boolean operations with code eaters
    */
    bool launch_test_code_eaters_metadata_counter()
    {
        bool test_code_eaters_metadata_counter_bool(void);     

        bool is_passed = true;

        std::cout << "Code eaters - meta - counters : " << std::endl;

        is_passed &= test_code_eaters_metadata_counter_bool();

        std::cout << "Code eaters - meta - counters : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief tries the counter on all basic bool operations
     * 
     * Does not care about the results of the gates, only the counter
    */
    bool test_code_eaters_metadata_counter_bool()
    {
        bool is_passed = true;

        // operation counter
        sp_entity_opcounter op_counter = std::make_shared<EntityOpCounter>("operation counter");
        op_counter->init();

        // boolean operations

        sp_entity_boolid entity_boolid = std::make_shared<EntityBoolId>("boolean id entity");
        sp_entity_not entity_not = std::make_shared<EntityNot>("not entity");
        sp_entity_boolidin entity_boolidin = std::make_shared<EntityBoolIdIn>("in place boolean id entity");
        sp_entity_notin entity_notin = std::make_shared<EntityNotIn>("in place not entity");

        sp_entity_and entity_and = std::make_shared<EntityAnd>("and entity");
        sp_entity_nand entity_nand = std::make_shared<EntityNand>("nand entity");
        sp_entity_andin entity_andin = std::make_shared<EntityAndIn>("in place and entity");
        sp_entity_nandin entity_nandin = std::make_shared<EntityNandIn>("in place nand entity");

        sp_entity_or entity_or = std::make_shared<EntityOr>("or entity");
        sp_entity_nor entity_nor = std::make_shared<EntityNor>("nor entity");
        sp_entity_orin entity_orin = std::make_shared<EntityOrIn>("in place or entity");
        sp_entity_norin entity_norin = std::make_shared<EntityNorIn>("in place nor entity");

        sp_entity_xor entity_xor = std::make_shared<EntityXor>("xor entity");
        sp_entity_nxor entity_nxor = std::make_shared<EntityNxor>("nxor entity");
        sp_entity_xorin entity_xorin = std::make_shared<EntityXorIn>("in place xor entity");
        sp_entity_nxorin entity_nxorin = std::make_shared<EntityNxorIn>("in place nxor entity");



        entity_boolid->init();
        entity_not->init();
        entity_boolidin->init();
        entity_notin->init();

        entity_and->init();
        entity_nand->init();
        entity_andin->init();
        entity_nandin->init();

        entity_or->init();
        entity_nor->init();
        entity_orin->init();
        entity_norin->init();

        entity_xor->init();
        entity_nxor->init();
        entity_xorin->init();
        entity_nxorin->init();



        entity_boolid->set_op_counter(op_counter);
        entity_not->set_op_counter(op_counter);
        entity_boolidin->set_op_counter(op_counter);
        entity_notin->set_op_counter(op_counter);

        entity_and->set_op_counter(op_counter);
        entity_nand->set_op_counter(op_counter);
        entity_andin->set_op_counter(op_counter);
        entity_nandin->set_op_counter(op_counter);

        entity_or->set_op_counter(op_counter);
        entity_nor->set_op_counter(op_counter);
        entity_orin->set_op_counter(op_counter);
        entity_norin->set_op_counter(op_counter);
        
        entity_xor->set_op_counter(op_counter);
        entity_nxor->set_op_counter(op_counter);
        entity_xorin->set_op_counter(op_counter);
        entity_nxorin->set_op_counter(op_counter);



        sp_entity_bool entity_true = std::make_shared<EntityBool>("entity true", true);
        sp_entity_bool entity_false = std::make_shared<EntityBool>("entity false", false);
        sp_entity_bool entity_res = std::make_shared<EntityBool>("entity result", false);
        entity_true->init();
        entity_false->init();
        entity_res->init();

        std::vector<sp_entity> entities_1 = {
            entity_res
        };

        std::vector<sp_entity> entities_2 = {
            entity_res,
            entity_true
        };

        std::vector<sp_entity> entities_3 = {
            entity_res,
            entity_true,
            entity_false
        };


        //----- execute

        entities_2 = entity_boolid->exec(entities_2);
        entities_2 = entity_not->exec(entities_2);
        entities_1 = entity_boolidin->exec(entities_1);
        entities_1 = entity_notin->exec(entities_1);

        entities_3 = entity_and->exec(entities_3);
        entities_3 = entity_nand->exec(entities_3);
        entities_2 = entity_andin->exec(entities_2);
        entities_2 = entity_nandin->exec(entities_2);

        entities_3 = entity_or->exec(entities_3);
        entities_3 = entity_nor->exec(entities_3);
        entities_2 = entity_orin->exec(entities_2);
        entities_2 = entity_norin->exec(entities_2);

        entities_3 = entity_xor->exec(entities_3);
        entities_3 = entity_nxor->exec(entities_3);
        entities_2 = entity_xorin->exec(entities_2);
        entities_2 = entity_nxorin->exec(entities_2);


        if(entities_1.size() != 1 || entities_2.size() != 2 || entities_3.size() != 3)
        {
            is_passed = false;
            std::cout << "\tError : counters did not work on boolean operations : " << std::endl;
            std::cout << "\t\twrong result size" << std::endl;
        }

        if(op_counter->get_count(TYPE_BOOLID) != 1 || op_counter->get_count(TYPE_NOT) != 1
            || op_counter->get_count(TYPE_BOOLIDIN) != 1 || op_counter->get_count(TYPE_NOTIN) != 1)
        {
            is_passed = false;
            std::cout << "\tError : counters did not work on boolean ids " << std::endl;
        }

        if(op_counter->get_count(TYPE_AND) != 1 || op_counter->get_count(TYPE_NAND) != 1
            || op_counter->get_count(TYPE_ANDIN) != 1 || op_counter->get_count(TYPE_NANDIN) != 1)
        {
            is_passed = false;
            std::cout << "\tError : counters did not work on boolean AND " << std::endl;
        }

        if(op_counter->get_count(TYPE_XOR) != 1 || op_counter->get_count(TYPE_NXOR) != 1
            || op_counter->get_count(TYPE_XORIN) != 1 || op_counter->get_count(TYPE_NXORIN) != 1)
        {
            is_passed = false;
            std::cout << "\tError : counters did not work on boolean XOR " << std::endl;
        }

        if(op_counter->get_count(TYPE_OR) != 1 || op_counter->get_count(TYPE_NOR) != 1
            || op_counter->get_count(TYPE_ORIN) != 1 || op_counter->get_count(TYPE_NORIN) != 1)
        {
            is_passed = false;
            std::cout << "\tError : counters did not work on boolean OR " << std::endl;
        }


        // test id again : on int, double and str, it should not trigger counter

        sp_entity_int entity_int = std::make_shared<EntityInt>("int entity", 12);
        entity_int->init();
        entities_1 = entity_boolidin->exec(std::vector<sp_entity>{entity_int});
        if(op_counter->get_count(TYPE_BOOLIDIN) != 1)
        {
            is_passed = false;
            std::cout << "\tError : counter was triggered on in place bool id with int entity " << std::endl;           
        }


        if(verbose_unit_tests)
        {
            std::cout << "\tTest code eaters - meta - counters - bool : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
}
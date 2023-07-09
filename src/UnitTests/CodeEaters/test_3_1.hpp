// -------------------- META DATA - COUNTER 

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Entities/EntityBool.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityUnaryId.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityUnaryNot.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityAnd.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNand.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityAndIn.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNandIn.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityOr.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNor.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityOrIn.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNorIn.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityXor.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNxor.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityXorIn.hpp"
#include "../../Models/CodeEaters/Entities/Boolean/EntityNxorIn.hpp"
#include "../../Models/CodeEaters/Entities/Meta/EntityOpCounter.hpp"


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

        sp_entity_uid entity_uid = std::make_shared<EntityUnaryId>("unitary id entity");
        sp_entity_unot entity_unot = std::make_shared<EntityUnaryNot>("unitary not entity");

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



        entity_uid->init();
        entity_unot->init();

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



        entity_uid->set_op_counter(op_counter);
        entity_unot->set_op_counter(op_counter);

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

        entities_1 = entity_uid->exec(entities_1);
        entities_1 = entity_unot->exec(entities_1);

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

        if(op_counter->get_count(TYPE_UID) != 1 || op_counter->get_count(TYPE_UNOT) != 1)
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


        // test id again

        entities_3 = entity_uid->exec(entities_3);
        if(op_counter->get_count(TYPE_UID) != 4)
        {
            is_passed = false;
            std::cout << "\tError : counters did not work on boolan multiple id " << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "\tTest code eaters - meta - counters - bool : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
}
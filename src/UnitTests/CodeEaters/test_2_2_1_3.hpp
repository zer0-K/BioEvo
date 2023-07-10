// -------------------- CODE EATERS - OPERATIONS - INT - BASIC - MULT

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Entities/Int/EntityMultInt.hpp"
#include "../../Models/CodeEaters/Entities/Int/EntityMultIntIn.hpp"
#include "../../Models/CodeEaters/Entities/Int/EntityDivInt.hpp"
#include "../../Models/CodeEaters/Entities/Int/EntityDivIntIn.hpp"

namespace ut_ce
{
    /**
     * @brief Test multitive operations on ints
    */
    bool launch_test_code_eaters_operations_ints_basic_mult()
    {
        bool test_code_eaters_operations_int_mult(void);
        bool test_code_eaters_operations_int_multin(void);
        bool test_code_eaters_operations_int_div(void);
        bool test_code_eaters_operations_int_divin(void);
        
        bool is_passed = true;

        std::cout << "Code eaters - operations - int - basic - mult : " << std::endl;

        is_passed &= test_code_eaters_operations_int_mult();
        is_passed &= test_code_eaters_operations_int_multin();
        is_passed &= test_code_eaters_operations_int_div();
        is_passed &= test_code_eaters_operations_int_divin();
        
        std::cout << "Code eaters - operations - int - basic - mult : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief test 3 party multiplication 
    */
    bool test_code_eaters_operations_int_mult()
    {
        bool is_passed = true;

        sp_entity_multint entity_multint = std::make_shared<EntityMultInt>("int mult entity");
        entity_multint->init();
        std::vector<sp_entity> res;


        //---------- test with negative and positive values 

        int rint = 10;
        int lint = 3;

        sp_entity_int entity_res = std::make_shared<EntityInt>("entity res", 0);
        sp_entity_int entity_lop = std::make_shared<EntityInt>("entity left", lint);
        sp_entity_int entity_rop = std::make_shared<EntityInt>("entity right", rint);
        entity_res->init();
        entity_lop->init();
        entity_rop->init();

        std::vector<sp_entity> entries = {
            entity_res, 
            entity_lop,
            entity_rop
        };

        entries = entity_multint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint*rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int multiplication did not work on " << lint
                << " + " << rint << std::endl;
        }


        rint = -10;
        lint = 3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_multint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint*rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int multiplication did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = 10;
        lint = -3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_multint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint*rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int multiplication did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = -10;
        lint = -3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_multint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint*rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int multiplication did not work on " << lint
                << " + " << rint << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - int - basic - mult : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test 2 party multiplication, in place
    */
    bool test_code_eaters_operations_int_multin()
    {
        bool is_passed = true;

        sp_entity_multintin entity_multintin = std::make_shared<EntityMultIntIn>("in place int mult entity");
        entity_multintin->init();
        std::vector<sp_entity> res;


        //---------- test with negative and positive values 

        int rint = 10;
        int lint = 3;

        sp_entity_int entity_res = std::make_shared<EntityInt>("entity res", lint);
        sp_entity_int entity_rop = std::make_shared<EntityInt>("entity right", rint);
        entity_res->init();
        entity_rop->init();

        std::vector<sp_entity> entries = {
            entity_res, 
            entity_rop
        };

        entries = entity_multintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint*rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int multiplication did not work on " << lint
                << " + " << rint << std::endl;
        }


        rint = -10;
        lint = 3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_multintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint*rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int multiplication did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = 10;
        lint = -3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_multintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint*rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int multiplication did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = -10;
        lint = -3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_multintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint*rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int multiplication did not work on " << lint
                << " + " << rint << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - int - basic - mult in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
    
    /**
     * @brief test 3 party division 
    */
    bool test_code_eaters_operations_int_div()
    {
        bool is_passed = true;

        sp_entity_divint entity_divint = std::make_shared<EntityDivInt>("int division entity");
        entity_divint->init();
        std::vector<sp_entity> res;


        //---------- test with negative and positive values 

        int rint = 100;
        int lint = 3;

        sp_entity_int entity_res = std::make_shared<EntityInt>("entity res", 0);
        sp_entity_int entity_lop = std::make_shared<EntityInt>("entity left", lint);
        sp_entity_int entity_rop = std::make_shared<EntityInt>("entity right", rint);
        entity_res->init();
        entity_lop->init();
        entity_rop->init();

        std::vector<sp_entity> entries = {
            entity_res, 
            entity_lop,
            entity_rop
        };

        entries = entity_divint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint/rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int division did not work on " << lint
                << " + " << rint << std::endl;
        }


        rint = -100;
        lint = 3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_divint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint/rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int division did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = 100;
        lint = -3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_divint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint/rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int division did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = -100;
        lint = -3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_divint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint/rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int division did not work on " << lint
                << " + " << rint << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - int - basic - division : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test 2 party division, in place 
    */
    bool test_code_eaters_operations_int_divin()
    {
        bool is_passed = true;

        sp_entity_divintin entity_divintin = std::make_shared<EntityDivIntIn>("in place int division entity");
        entity_divintin->init();
        std::vector<sp_entity> res;


        //---------- test with negative and positive values 

        int rint = 100;
        int lint = 3;

        sp_entity_int entity_res = std::make_shared<EntityInt>("entity res", lint);
        sp_entity_int entity_rop = std::make_shared<EntityInt>("entity right", rint);
        entity_res->init();
        entity_rop->init();

        std::vector<sp_entity> entries = {
            entity_res, 
            entity_rop
        };

        entries = entity_divintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint/rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int division did not work on " << lint
                << " + " << rint << std::endl;
        }


        rint = -100;
        lint = 3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_divintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint/rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int division did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = 100;
        lint = -3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_divintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint/rint
            || entries[1]->get_value_int() != rint || entries[2]->get_value_int() != lint)
        {
            is_passed = false;
            std::cout << "\tError : in place int division did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = -100;
        lint = -3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_divintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint/rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int division did not work on " << lint
                << " + " << rint << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - int - basic - in place division : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
}
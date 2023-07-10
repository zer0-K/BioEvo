// -------------------- CODE EATERS - OPERATIONS - INT - BASIC - ADD

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/CodeEaters/Universe/UniverseCodeEaters.hpp"
#include "../../Entities/EntityInt.hpp"
#include "../../Models/CodeEaters/Entities/Int/EntityAddInt.hpp"
#include "../../Models/CodeEaters/Entities/Int/EntityAddIntIn.hpp"
#include "../../Models/CodeEaters/Entities/Int/EntitySubInt.hpp"
#include "../../Models/CodeEaters/Entities/Int/EntitySubIntIn.hpp"

namespace ut_ce
{
    /**
     * @brief Test additive operations on ints
    */
    bool launch_test_code_eaters_operations_ints_basic_add()
    {
        bool test_code_eaters_operations_int_add(void);
        bool test_code_eaters_operations_int_addin(void);
        bool test_code_eaters_operations_int_sub(void);
        bool test_code_eaters_operations_int_subin(void);
        
        bool is_passed = true;

        std::cout << "Code eaters - operations - int - basic - add : " << std::endl;

        is_passed &= test_code_eaters_operations_int_add();
        is_passed &= test_code_eaters_operations_int_addin();
        is_passed &= test_code_eaters_operations_int_sub();
        is_passed &= test_code_eaters_operations_int_subin();
        
        std::cout << "Code eaters - operations - int - basic - add : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief test 3 party addition 
    */
    bool test_code_eaters_operations_int_add()
    {
        bool is_passed = true;

        sp_entity_addint entity_addint = std::make_shared<EntityAddInt>("int add entity");
        entity_addint->init();
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

        entries = entity_addint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint+rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int addition did not work on " << lint
                << " + " << rint << std::endl;
        }


        rint = -10;
        lint = 3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_addint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint+rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int addition did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = 10;
        lint = -3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_addint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint+rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int addition did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = -10;
        lint = -3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_addint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint+rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int addition did not work on " << lint
                << " + " << rint << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - int - basic - add : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test 2 party addition, in place
    */
    bool test_code_eaters_operations_int_addin()
    {
        bool is_passed = true;

        sp_entity_addintin entity_addintin = std::make_shared<EntityAddIntIn>("in place int add entity");
        entity_addintin->init();
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

        entries = entity_addintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint+rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int addition did not work on " << lint
                << " + " << rint << std::endl;
        }


        rint = -10;
        lint = 3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_addintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint+rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int addition did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = 10;
        lint = -3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_addintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint+rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int addition did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = -10;
        lint = -3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_addintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint+rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int addition did not work on " << lint
                << " + " << rint << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - int - basic - add in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
    
    /**
     * @brief test 3 party substraction 
    */
    bool test_code_eaters_operations_int_sub()
    {
        bool is_passed = true;

        sp_entity_subint entity_subint = std::make_shared<EntitySubInt>("int substraction entity");
        entity_subint->init();
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

        entries = entity_subint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint-rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int substraction did not work on " << lint
                << " + " << rint << std::endl;
        }


        rint = -10;
        lint = 3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_subint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint-rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int substraction did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = 10;
        lint = -3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_subint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint-rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int substraction did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = -10;
        lint = -3;
        entries[0]->set_value_int(0);
        entries[1]->set_value_int(lint);
        entries[2]->set_value_int(rint);
        entries = entity_subint->exec(entries);

        if(entries.size() != 3 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint-rint
            || entries[1]->get_value_int() != lint || entries[2]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : int substraction did not work on " << lint
                << " + " << rint << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - int - basic - substraction : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief test 2 party substraction, in place 
    */
    bool test_code_eaters_operations_int_subin()
    {
        bool is_passed = true;

        sp_entity_subintin entity_subintin = std::make_shared<EntitySubIntIn>("in place int substraction entity");
        entity_subintin->init();
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

        entries = entity_subintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint-rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int substraction did not work on " << lint
                << " + " << rint << std::endl;
        }


        rint = -10;
        lint = 3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_subintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint-rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int substraction did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = 10;
        lint = -3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_subintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint-rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int substraction did not work on " << lint
                << " + " << rint << std::endl;
        }

        rint = -10;
        lint = -3;
        entries[0]->set_value_int(lint);
        entries[1]->set_value_int(rint);
        entries = entity_subintin->exec(entries);

        if(entries.size() != 2 || !entries[0]->has_value_int() || entries[0]->get_value_int() != lint-rint
            || entries[1]->get_value_int() != rint)
        {
            is_passed = false;
            std::cout << "\tError : in place int substraction did not work on " << lint
                << " + " << rint << std::endl;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Code eaters - operations - int - basic - substraction in place : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
}
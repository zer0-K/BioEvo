#pragma once

#include <iostream>
#include <string>

#include "Constants.hpp"

void passed_print(bool is_passed)
{
    if(is_passed)
        std::cout << greencol << "passed" << defcol;
    else
        std::cout << redcol << "not passed" << defcol;
    std::cout << std::endl;
}
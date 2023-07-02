#pragma once

#include <iostream>
#include <string>

#include "Constants.hpp"

void passed_print(bool is_passed, int nb_tabs)
{
    if(nb_tabs<0)
        nb_tabs = 0;

    // init tabs
    std::string tabs = "";
    for(int i=0; i<nb_tabs; i++)
        tabs += "\t";
    

    if(is_passed)
        std::cout << tabs << greencol << "passed" << defcol;
    else
        std::cout << tabs << redcol << "not passed" << defcol;
    std::cout << std::endl;
}
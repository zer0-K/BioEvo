#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Constants.hpp"

inline void passed_print(bool is_passed)
{
    if(is_passed)
        std::cout << greencol << "passed" << defcol;
    else
        std::cout << redcol << "not passed" << defcol;
    std::cout << std::endl;
}

inline std::string to_str(std::vector<int> t)
{
    if(t.size() == 0)
        return "[]";

    std::string s = "[ " + std::to_string(t[0]);
    for(int i=1;i<t.size();i++)
    {
        s += ", " + std::to_string(t[i]);
    }

    return s + " ]";
}

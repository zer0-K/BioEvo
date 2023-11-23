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

inline int first_diff_index(std::vector<int> v1, std::vector<int> v2)
{
    if(v1.size() != v2.size() || v1.size() == 0)
        return -1;

    for(int i=0;i<v1.size();i++)
    {
        if(v1[i] != v2[i])
            return i;
    }
    return v1.size();
}
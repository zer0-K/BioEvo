#pragma once

#include "../Constants.hpp"

/// @brief to compute the rule number corresponding to a number
class RuleNumberComputer
{
public:
    /**
     * @brief Compute the rule number corresponding to the given number
     * 
     * @param number number to get the rule from
     * 
     * @return the rule corresponding to the number
    */
    static Rule computeCorrespondingRule(int number);
};
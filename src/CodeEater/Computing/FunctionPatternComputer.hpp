#pragma once

#include "Utils/FunctionPattern.hpp"
#include "../ConstantsCodeEater.hpp"

/// @brief compute the function pattern
class FunctionPatternComputer
{
public:
    /**
     * @brief Constructor
    */
    FunctionPatternComputer();

    /**
     * @brief Compute the process function pattern from the given tokens
     * 
     * @param[out] function_pattern function pattern to compute
     * @param[in] tokens tokens of the eaten code eaters
    */
    void computeFunctionPattern(FunctionPattern* function_pattern, EaterToken tokens[]);
};
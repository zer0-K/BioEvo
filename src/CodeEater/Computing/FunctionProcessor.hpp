#pragma once

#include "Utils/FunctionPattern.hpp"

class FunctionProcessor
{
public:
    /**
     * @brief Constructor
    */
    FunctionProcessor();

    /**
     * @brief Process some numbers into a number
     * the function pattern tells how to transform the numbers into a single one
     * 
     * @param function_pattern the function pattern
     * @param numbers the numbers on which to apply the function
     * @param number_of_numbers size of the array "numbers"
     * 
     * @return result of the process
    */
    int ComputeFunction(FunctionPattern* function_pattern, int numbers[], int number_of_numbers);
};
#include "FunctionProcessor.hpp"

FunctionProcessor::FunctionProcessor()
{
    // do nothing for the moment
}

int FunctionProcessor::ComputeFunction(FunctionPattern* function_pattern, int numbers[], int number_of_numbers)
{
    // for the moment, we don't use the function pattern, this is a fixed function

    // temporary code
    if(number_of_numbers>0)
    {
        int result = numbers[0];

        for(int i=1; i<number_of_numbers-1; i+=2)
        {
            int op = numbers[i]%3;
            int lvalue = numbers[i+1];

            if(op==0)
            {
                result += lvalue;
            }
            else if(op==1)
            {
                result -= lvalue;
            }
            else
            {
                result *= lvalue;
            }

            if(result<0)
            {
                result = 0;
            }
        }

        return result;
    }
    else
    {
        return 0;
    }
}
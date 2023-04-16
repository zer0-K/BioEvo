#include "Result.hpp"

#include "../Convert/tostring.hpp"
#include <iostream>

void Result::set_solutions(Solution** solutions, int nb_solutions)
{
    this->nb_solutions = nb_solutions;
    this->solutions = solutions;

    this->test_errors = new double[nb_solutions];
    for(int i=0; i<nb_solutions;i++)
    {
        this->test_errors[i] = solutions[i]->get_error();
    }
}

//---------- other

std::string Result::to_string()
{
    std::string res = "";
    
    res += "nb_solutions : " + std::to_string(nb_solutions) + " ; ";
    res += "solutions : ";
    for(int i=0; i<nb_solutions;i++)
    {
        res += "      sol : " + this->solutions[i]->to_string() + "\n";
    }
    res += convert_str(this->test_errors, this->nb_solutions); 

    return res;
}
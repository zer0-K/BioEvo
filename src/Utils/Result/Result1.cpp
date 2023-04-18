#include "Result1.hpp"

#include "../Convert/tostring.hpp"

//---------- other

std::string Result1::to_string()
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
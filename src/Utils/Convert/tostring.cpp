#include "tostring.hpp"
#include <algorithm>

const int MAX_ARRAY_PRINT = 10;

std::string convert_str(int* arr, int size)
{
    std::string str_return = "[";

    if(size>0)
    {
        str_return += std::to_string(arr[0]);
    }
    
    for(int i=1; i<std::min(size, MAX_ARRAY_PRINT); i++)
    {
        str_return += " " + std::to_string(arr[i]);
    }

    str_return += "]";

    return str_return;
}

std::string convert_str(double arr[], int size)
{
    std::string str_return = "[";

    if(size>0)
    {
        str_return += std::to_string(arr[0]);
    }
    
    for(int i=1; i<std::min(size, MAX_ARRAY_PRINT); i++)
    {
        str_return += " " + std::to_string(arr[i]);
    }

    str_return += "]";

    return str_return;
}

std::string convert_str(std::vector<double> vect)
{
    std::string str_return = "[";

    if(vect.size()>0)
    {
        str_return += std::to_string(vect[0]);
    }
    
    for(int i=1; i<std::min((int)vect.size(), MAX_ARRAY_PRINT); i++)
    {
        str_return += " " + std::to_string(vect[i]);
    }

    str_return += "]";

    return str_return;
}

std::string convert_str(Pair<double,double>* pair, int dimension)
{
    return "( " + convert_str(pair->get_x(), dimension) + " ; " + std::to_string(pair->get_f_x()) + " )";
}

std::string convert_str(Pair<double,double>* pairs[], int nb_vals, int dimension)
{
    std::string str_return = "[";

    if(nb_vals>0)
    {
        str_return += convert_str(pairs[0], dimension);
    }
    
    for(int i=1; i<std::min(nb_vals, MAX_ARRAY_PRINT); i++)
    {
        str_return += " " + convert_str(pairs[i], dimension);
    }

    str_return += "]";

    return str_return;
}

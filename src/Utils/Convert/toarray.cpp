#include "toarray.hpp"

double* to_double_array(std::string arr_str)
{
    int len = 0;

    for(int i=0; i<arr_str.length();i++)
    {
        if(arr_str[i] == ',')
            len++;
    }

    return to_double_array(arr_str, len);
}

double* to_double_array(std::string arr_str, size_t len)
{
    if(len == 0)
        return nullptr;

    double* parsed_doubles = new double[len];
   
    size_t pos = 1;
    int i=0;
    while ((pos = arr_str.find(',')) != std::string::npos) {
        parsed_doubles[i] = stod(arr_str.substr(0, pos));
        arr_str = arr_str.erase(0, pos+1);
        i++;
    }
    parsed_doubles[len-1] = stod(arr_str.substr(arr_str.length()-1));

    return parsed_doubles;
}
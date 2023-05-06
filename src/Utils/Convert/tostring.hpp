#pragma once

#include <string>
#include <vector>
#include <map>

#include "../Math/Pair.hpp"

extern const int MAX_ARRAY_PRINT;

extern std::string convert_str(int* arr, int size);
extern std::string convert_str(double arr[], int size);
extern std::string convert_str(std::vector<double> vect);
extern std::string convert_str(std::vector<std::string> vect);
extern std::string convert_str(std::map<const std::string, std::vector<std::string>> map_names);
extern std::string convert_str(Pair<double,double>* pair, int dimension);
extern std::string convert_str(Pair<double,double>* pairs[], int nb_vals, int dimension);
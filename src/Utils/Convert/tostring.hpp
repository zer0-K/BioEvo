#pragma

#include <string>
#include <vector>

#include "../Math/Pair.hpp"
#include "../Result/Result.hpp"

extern const int MAX_ARRAY_PRINT;

extern std::string convert_str(int* arr, int size);
extern std::string convert_str(double arr[], int size);
extern std::string convert_str(std::vector<double> vect);
extern std::string convert_str(Pair<double,double>* pair, int dimension);
extern std::string convert_str(Pair<double,double>* pairs[], int nb_vals, int dimension);
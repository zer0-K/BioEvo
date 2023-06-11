#include "ClassicalInfo/test_1_empty.hpp"

int main(int argc, char* argv[])
{
    bool is_passed = true;

    is_passed = is_passed && launch_test_classical_info_empty();

    std::cout << "Unit test classical info : ";
    if(is_passed)
        std::cout << greencol << "passed" << defcol;
    else
        std::cout << redcol << "not passed" << defcol;
    std::cout << std::endl;


    return 0;
}
#pragma once

class Permutation
{
private:
    int number_of_rules;    ///< size of the permutation, number of rules
    int* permutation;  /// the permutation itself

public:
    /**
     * @brief Constructor, create the identity permutation
    */
    Permutation();

    /**
     * @brief Constructor, create the identity permutation
     * 
     * @param number_of_rules size of the permutation, number of rules
    */
    Permutation(int number_of_rules);

    /**
     * @brief Perform a transposition : inverse indexes i and j
     * 
     * @param i first index to swap
     * @param j second index to swap
    */
    void swap(int i, int j);
};
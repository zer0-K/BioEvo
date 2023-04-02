#include "Permutation.hpp"

#include "../../Constants.hpp"

Permutation::Permutation()
    : Permutation(NUMBER_OF_RULES)
{
    // just call the other constructor
}

Permutation::Permutation(int number_of_rules)
{
    // define the size of the permutation
    this->number_of_rules = number_of_rules;

    // init the permutation
    this->permutation = new int[number_of_rules];
    for(int i=0; i<number_of_rules; i++)
    {
        this->permutation[i] = i;
    }
}

void Permutation::swap(int i, int j)
{
    // temporary variable for transposition
    int temp = permutation[i];

    // transpose
    permutation[i] = permutation[j];
    permutation[j] = temp;
}
#pragma once

#include "AbstractTrait.hpp"

/// @brief Trait, generally built to be driven by some gene(s)
template<class T>
class Trait : AbstractTrait
{
protected:
    T trait_value;      ///< actual trait

public:
    /**
     * @brief Constructor
     * 
     * @param[in] trait_value trait value
    */
    Trait(T value) { trait_value = value; }

    //----- getters
    T get_value() { return trait_value; }

    //----- setters
    void set_value(T trait) { trait_value = trait; }
};
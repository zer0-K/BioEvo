#pragma once

#include "../../Biology/Gene.hpp"
#include "../../Biology/Trait.hpp"
#include <string>

/// @brief Gene for a linear model
class GeneLinear : Gene
{
public:

    /**
     * @brief Constructor
     * @see Gene constructor
    */
    GeneLinear(double mean, double std_dev, Trait<double>* trait);

    /// @see Gene::drive
    void drive() override;

    //----- other
    std::string to_string();
    std::string to_json();
};
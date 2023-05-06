#pragma once

#include "Gene.hpp"
#include "../Trait.hpp"
#include <string>

/// @brief Gene for a linear model
class GeneLinear : public Gene
{
public:

    /**
     * @brief Constructor
     * @see Gene constructor
    */
    GeneLinear(double mean, double std_dev, std::shared_ptr<Trait<double>> trait);

    /// @see Gene::drive
    void drive() override;

    //----- other
    std::string to_string();
    std::string to_json();
};

typedef std::shared_ptr<GeneLinear> sp_genelinear;
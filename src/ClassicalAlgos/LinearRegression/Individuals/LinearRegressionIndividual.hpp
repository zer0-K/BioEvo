#pragma once

#include "../../../Individual.hpp"

class LinearRegressionIndividual : Individual
{
public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the individual
    */
    LinearRegressionIndividual(std::string name);

    /// @see Individual::evolve
    void evolve() override;
};
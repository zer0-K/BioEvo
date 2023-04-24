#pragma once

#include "../../../Buffer.hpp"

/// @brief buffer for linear model
class BufferLinear : Buffer
{
public:
    /// @see Buffer 
    Flow* transform_individuals_out_to_environment_in(Flow** individual_ouput) override;

    /// @see Buffer
    Flow** transform_environment_out_to_individuals_in(Flow* environment_ouput, int nb_individuals) override;

    /// @see Buffer
    double compute_errors(Flow* input, Flow* output);
};
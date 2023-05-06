#pragma once

#include "Buffer.hpp"

/// @brief buffer for linear model
class BufferLinear : public Buffer
{
public:
    /// @see Buffer 
    sp_flow transform_individuals_out_to_environment_in(std::vector<sp_flow> individual_ouput) override;

    /// @see Buffer
    std::vector<sp_flow> transform_environment_out_to_individuals_in(sp_flow environment_ouput, int nb_individuals) override;

    /// @see Buffer
    double compute_errors(sp_flow input, sp_flow output);
};

typedef std::shared_ptr<BufferLinear> sp_bufferlinear;
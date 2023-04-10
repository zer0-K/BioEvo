#pragma once

#include "../../Buffer.hpp"

/// @brief buffer for linear model
class BufferLinear : Buffer
{
public:
    /// @see Buffer 
    Flow* transform_individual_out_to_environment_in(Flow* individual_ouput) override;

    /// @see Buffer
    Flow* transform_environment_out_to_individual_in(Flow* environment_ouput) override;
};
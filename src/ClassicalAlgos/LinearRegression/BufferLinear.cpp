#include "BufferLinear.hpp"

Flow* BufferLinear::transform_individual_out_to_environment_in(Flow* individual_ouput)
{
    return individual_ouput;
}

Flow* BufferLinear::transform_environment_out_to_individual_in(Flow* environment_ouput)
{
    return environment_ouput;
}
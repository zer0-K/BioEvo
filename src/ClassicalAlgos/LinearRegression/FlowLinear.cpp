#include "FlowLinear.hpp"

FlowLinear::FlowLinear(std::vector<Pair<double[],double>> flow_vector)
{
    this->flow_vector = flow_vector;
}

std::vector<Pair<double[],double>> FlowLinear::get_flow_vector()
{
    return this->flow_vector;
}
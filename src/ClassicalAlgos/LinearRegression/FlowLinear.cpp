#include "FlowLinear.hpp"

FlowLinear::FlowLinear(int dimension, double* flow_vector)
{
    this->dimension = dimension;
    this->flow_vector = flow_vector;
}
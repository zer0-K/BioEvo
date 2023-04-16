#pragma once

#include "../../Flow.hpp"
#include "../../Utils/Math/Pair.hpp"
#include <vector>

/// @brief flow for linear models
class FlowLinear : Flow
{
private:
    std::vector<Pair<double[],double>> flow_vector; ///< vector of values 

public:
    /**
     * @brief Constructor
     * 
     * @param[in] flow_vector vector of values
    */
    FlowLinear(std::vector<Pair<double[],double>> flow_vector);

    /**
     * getters
    */

    std::vector<Pair<double[],double>> get_flow_vector();
};
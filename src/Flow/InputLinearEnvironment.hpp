#pragma once

#include "Flow.hpp"
#include "../Utils/Math/Pair.hpp"


/// @brief input of linear environments 
class InputLinearEnvironment : public Flow
{
public:
    /**
     * @brief Constructor
    */
    InputLinearEnvironment();
};

typedef std::shared_ptr<InputLinearEnvironment> sp_input_linear_environment;
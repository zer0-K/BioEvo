#pragma once

#include <string>

/// @brief flow, i.e. type of the inputs and outputs
class Flow
{
public:
    /**
     * @brief Constructor
    */
    Flow();

    //----- other
    std::string to_string();
    std::string to_json();
};
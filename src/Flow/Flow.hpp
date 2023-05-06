#pragma once

#include <string>
#include <memory> 

/// @brief flow, i.e. type of the inputs and outputs
class Flow
{
public:
    /**
     * @brief Constructor
    */
    Flow();

    virtual ~Flow() {};

    //----- other
    std::string to_string();
};

typedef std::shared_ptr<Flow> sp_flow;
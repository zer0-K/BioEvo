#pragma once

#include <vector>

#include "Flow.hpp"

///@brief Flow 'list of flows'
class FlowList: Flow
{
protected:
    std::vector<Flow> flows;//TODO : delete it and redo it

public:
    /**
     * @brief Constructor
    */
    FlowList();

    //----- other
    std::string to_string();
};
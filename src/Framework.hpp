#pragma once

#include "Universe.hpp"

class Framework
{
private:
    Universe** universes;   ///< universes in which

public:
    /**
     * Constructor
     * 
     * @param[in] universes universes
    */
    Framework(Universe** universes);
};
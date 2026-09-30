#pragma once

#include <array>
#include <vector>
#include <functional>

#include "../../../../Utils/Constants.hpp"


class BiologicalDebugger
{
protected:
    bool _stop = false;

public:
    bool activated = false;

    BiologicalDebugger() {}


    void check_line(std::array<int,SIZE_INSTR> line)
    {

    }

    bool stop()
    {
        return activated && _stop;
    }

    void unstop()
    {
        _stop = false;
    }
};

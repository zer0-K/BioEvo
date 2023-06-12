#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseMaths : public Universe
{
protected:

public:
    UniverseMaths(int size_universe, std::string name);
};

typedef std::shared_ptr<UniverseMaths> sp_univ_maths;
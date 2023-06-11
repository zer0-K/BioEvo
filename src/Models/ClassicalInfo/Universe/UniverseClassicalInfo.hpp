#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseClassicalInfo : public Universe
{
protected:

public:
    UniverseClassicalInfo(int size_universe, std::string name);
};

typedef std::shared_ptr<UniverseClassicalInfo> sp_univ_info;
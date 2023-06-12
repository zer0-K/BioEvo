#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseTheoreticalInfo : public Universe
{
protected:

public:
    UniverseTheoreticalInfo(int size_universe, std::string name);
};

typedef std::shared_ptr<UniverseTheoreticalInfo> sp_univ_th_info;
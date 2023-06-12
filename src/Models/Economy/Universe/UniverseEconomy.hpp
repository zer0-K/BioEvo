#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseEconomy : public Universe
{
protected:

public:
    UniverseEconomy(int size_universe, std::string name);
};

typedef std::shared_ptr<UniverseEconomy> sp_univ_economy;
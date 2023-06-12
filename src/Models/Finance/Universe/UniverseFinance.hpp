#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseFinance : public Universe
{
protected:

public:
    UniverseFinance(int size_universe, std::string name);
};

typedef std::shared_ptr<UniverseFinance> sp_univ_finance;
#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseEvoAlgos : public Universe
{
protected:

public:
    UniverseEvoAlgos(int size_universe, std::string name);
};

typedef std::shared_ptr<UniverseEvoAlgos> sp_univ_evo_algos;
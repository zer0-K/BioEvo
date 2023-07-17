#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseClassicalAlgos : public Universe
{
protected:

public:
    UniverseClassicalAlgos(int size_universe, std::string name);

    void exec();
};

typedef std::shared_ptr<UniverseClassicalAlgos> sp_univ_algos;
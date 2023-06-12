#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseBioEvo : public Universe
{
protected:

public:
    UniverseBioEvo(int size_universe, std::string name);
};

typedef std::shared_ptr<UniverseBioEvo> sp_univ_bio_evo;
#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseCodeEaters : public Universe
{
protected:

public:
    UniverseCodeEaters(int size_universe, std::string name);
};

typedef std::shared_ptr<UniverseCodeEaters> sp_univ_code_eaters;
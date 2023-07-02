#pragma once

#include "../../../Universe/Universe.hpp"

class UniverseCodeEaters : public Universe
{
protected:

public:
    /**
     * @brief Constructor
     * 
     * Init with void code eaters
    */
    UniverseCodeEaters(int size_universe, std::string name);

    /**
     * @brief Constructor
     * 
     * Init with code eaters that are in some places
    */
    UniverseCodeEaters(std::string name, std::vector<sp_place> places);
};

typedef std::shared_ptr<UniverseCodeEaters> sp_univ_code_eaters;
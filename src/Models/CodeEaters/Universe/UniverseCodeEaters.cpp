#include "UniverseCodeEaters.hpp"

UniverseCodeEaters::UniverseCodeEaters(int size_universe, std::string name)
    :Universe::Universe(size_universe, name)
{
    
}

UniverseCodeEaters::UniverseCodeEaters(std::string name, std::vector<sp_place> places)
    :Universe::Universe(name, places)
{

}
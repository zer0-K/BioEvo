#pragma once

#include <vector>

#include "../General/Place.hpp"
#include "../Utils/Constants.hpp"
#include "../Entities/EntityVoid.hpp"


class Universe;
typedef std::shared_ptr<Universe> sp_universe;

/// @brief Contains entities that evolves across time
class Universe
{
protected:
    std::string name;

    /**
     * @brief places of the universe
     * 
     * (linear topology)
    */
    std::vector<sp_place> places;

    /**
     * @brief meta places of the universe
     * 
     * For example : a place that builds special env values
     *              a terminal in which the individuals can read/write on
     * Those places are ad hoc, they should be handled by the experimenter
    */
    std::vector<sp_place> meta_places;
 
 public:
    /// @brief Constructor
    Universe(int size_universe, std::string name);

    /// @brief Constructor
    Universe(std::string name, std::vector<sp_place> places);

    /// @brief Constructor
    Universe(std::string name, std::vector<sp_place> places, std::vector<sp_place> meta_places);

    /**
     * @brief Execute the universe
    */
    virtual void exec();

    //----- getters

    std::string get_name();
    std::vector<sp_place> get_places();
    std::vector<sp_place> get_meta_places();
};

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
    Universe(std::string name, std::vector<sp_entity> entities);

    /// @brief Constructor
    Universe(std::string name, std::vector<sp_place> places, std::vector<sp_place> meta_places);
    Universe(std::string name, std::vector<sp_entity> entities, std::vector<sp_entity> meta_entities);

    /**
     * @brief Execute the universe
    */
    virtual void exec();

    /**
     * @brief reconnect the out of entity to other ins
     *
     * @param[in] entity entity to connect out to other ins
     */
    virtual void update_flows(sp_entity entity);

    /**
     * @brief return the graph of connection between the places
     *
     * An entity can have several input source, but each time an entity is executed it will set its output,
     * so only last one will override all the previous outputs set as (unique) input
     */
    std::vector<std::array<int,2>> get_place_graph();

    //----- getters

    std::string get_name();
    std::vector<sp_place> get_places();
    std::vector<sp_place> get_meta_places();
    int get_universe_size();
};

#pragma once

#include "../Framework.hpp"
#include "../Individual/IndividualLinear.hpp"
#include "../Environment/EnvironmentLinear.hpp"

/// @brief create objects from json
class Builder
{
public:
    /**
     * @brief create an entity given params for the constructor
     * 
     * @param[out] framework framework to add the entity to
     * @param[in] universe_name name of the universe to add the entity to
     * @param[in] entity_type entity type (individual linear,...)
     * @param[in] params param to build the entity
    */
    static void create_entity(sp_framework framework, std::string universe_name, std::string entity_type, boost::json::object params)
    {
        if(entity_type == "IndividualLinear")
            framework->add_individual(std::make_shared<IndividualLinear>(params), universe_name);
        if(entity_type == "EnvironmentLinear")
            framework->set_environment(std::make_shared<EnvironmentLinear>(params), universe_name);
    }

    /**
     * @brief get a description of the params to build an entity
     * 
     * @param[in] entity_type type of the entity to get the param description from
     * 
     * @return description of the params
    */
    static boost::json::object get_type_descr(std::string entity_type)
    {
        if(entity_type == "IndividualLinear")
            return IndividualLinear::type_to_json();
        if(entity_type == "EnvironmentLinear")
            return EnvironmentLinear::type_to_json();
    }
};
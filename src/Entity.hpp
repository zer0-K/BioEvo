#pragma once

#include <string>
#include <memory>
#include <boost/json.hpp>

#include "Declaration/Constants.hpp"

class Entity
{
protected:
    std::string name;

public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the entity
    */
    Entity(std::string name);

    /**
     * @brief Constructor from json
     * 
     * @param[in] params params to build the object
    */
    Entity(boost::json::object params);

    /**
     * @brief convert current object to json
    */
    virtual boost::json::object object_to_json() = 0;

    /**
     * @brief convert current class to json
    */
    static boost::json::object type_to_json()
    {
        boost::json::object jentity;

        jentity["name"] = TYPE_STRING;

        return jentity;
    }

    std::string get_name();
};

typedef std::shared_ptr<Entity> sp_entity;
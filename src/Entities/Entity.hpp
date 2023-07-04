#pragma once

#include <vector>
#include <string>
#include <memory>

class Entity;
typedef std::shared_ptr<Entity> sp_entity;

class Entity
{
protected:
    std::string name;
    std::string type;

    bool has_int;
    int value_int;
    
    bool has_double;
    double value_double;

    bool has_str;
    std::string value_str;

    bool has_bool;
    bool value_bool;

    int working_place_index;

public:

    Entity(std::string entity_name);
    Entity(std::string entity_name, int val);
    Entity(std::string entity_name, double val);
    Entity(std::string entity_name, std::string val);
    Entity(std::string entity_name, bool val);

    virtual void init() {};
    /**
     * @brief execute the current entity
    */
    virtual std::vector<sp_entity> exec(std::vector<sp_entity> entries) { return std::vector<sp_entity>(0); };
    std::vector<sp_entity> exec(sp_entity entry);

    /**
     * @brief to apply external instructions on the current object
     * 
     * For example, makes the sum of the vals of two entities
    */
    friend void apply_instr(std::vector<Entity> params);

    std::string get_name();
    std::string get_type();

    bool has_value_int();
    int get_value_int();

    bool has_value_double();
    double get_value_double();
    
    bool has_value_str();
    std::string get_value_str();

    bool has_value_bool();
    bool get_value_bool();
    
    int get_working_place_index();

    //----- setters

    void set_value_int(int val);
    void set_value_double(double val);
    void set_value_str(std::string val);
    void set_value_bool(bool val);
};
#pragma once

#include <vector>
#include <string>
#include <memory>

class Entity;
typedef std::shared_ptr<Entity> sp_entity;

class Entity
{
protected:
     /// @brief name of the entity
    std::string name;

    /**
     * @brief most specific type of the entity
    */
    std::string type;

    /**
     * @brief all the types the entity belongs to (inheritance)
    */
    std::vector<std::string> types;

    bool has_int;
    int value_int;
    
    bool has_double;
    double value_double;

    bool has_str;
    std::string value_str;

    bool has_bool;
    bool value_bool;

    /**
     * @brief another entity can feed the input of another entity
     * For the moment, useless, because we automatically fill with connected_outs (@see exec)
     */
    std::vector<int> connected_in;
    std::vector<sp_entity> input;

    /**
     * @brief this entity can feed other algos outs
     */
    std::vector<int> connected_outs;
    std::vector<sp_entity> output;

    // metadata
    /// @brief number of times the entity has been executed
    int nb_of_uses; 
    /// @brief number of times each type of entity has been executed
    sp_entity op_counter;
public:

    Entity(std::string entity_name);
    Entity(std::string entity_name, int val);
    Entity(std::string entity_name, double val);
    Entity(std::string entity_name, std::string val);
    Entity(std::string entity_name, bool val);

    virtual void init() {};

    /**
     * @brief execute the current entity
     * 
     * By default, the execution does not increase the number of use, and does not 
     * consume energy, nor create energy from the entries
    */
    virtual std::vector<sp_entity> exec(std::vector<sp_entity> entries) { return std::vector<sp_entity>(0); };
    std::vector<sp_entity> exec(sp_entity entry);
    virtual void exec() { output = exec(input); };    // exec with input, and res is set to output, @see exec(std::vector<sp_entity>)

    // TODO remove this function
    /**
     * @brief to apply external instructions on the current object
     * 
     * For example, makes the sum of the vals of two entities
    */
    friend void apply_instr(std::vector<Entity> params);

    /**
     * @brief add the given type to the types of the code eater
     * 
     * if the type is already in, does nothing
    */
    void add_type(std::string given_type);


    //----- getters
    std::string get_name();
    std::string get_type();
    std::string get_type(int i);
    bool is_type(std::string type_to_check);

    bool has_value_int();
    int get_value_int();

    bool has_value_double();
    double get_value_double();
    
    bool has_value_str();
    std::string get_value_str();

    bool has_value_bool();
    bool get_value_bool();
    
    std::vector<int> get_connected_ins();
    std::vector<int> get_connected_outs();
    std::vector<sp_entity> get_input();
    std::vector<sp_entity> get_output();

    //----- setters

    void set_value_int(int val);
    void set_value_double(double val);
    void set_value_str(std::string val);
    void set_value_bool(bool val);
    void set_op_counter(sp_entity counter);

    void set_connected_in(int new_in);
    void add_connected_out(int new_out);
    void remove_connected_out(int new_out);
    void set_input(std::vector<sp_entity> new_input);
    void set_output(std::vector<sp_entity> new_output);
};
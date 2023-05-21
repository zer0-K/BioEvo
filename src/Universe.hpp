#pragma once

#include "Declaration/PreprocessingDefinitions.hpp"
#include <map>
#include <string>

#include "Environment/Environment.hpp"
#include "Individual/Individual.hpp"

/// @brief universe for the experiments
class Universe
{
protected:
    std::string name;   ///< name of the universe
    int width;  /// { temporary, for code eater
    int height; /// { temporary, for code eater

    int number_of_individuals;      ///< current number of individuals in the universe
    int max_number_of_individuals;  ///< maximum number of individuals in the universe
    std::vector<int> epochs_individuals;    ///< number of epochs for the individuals

    std::vector<sp_individual> individuals;   ///< individuals living in the universe
    sp_environment current_environment;   ///< environment with which the individual interacts
    std::vector<sp_environment> environments;   ///< all possible environments
        
    std::map<sp_individual, double> solutions;     ///< solutions of the problem

    int t;  ///< time

    bool state; ///< universe state

public:

    /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
    */
    Universe(std::string name);

    Universe(int width, int height);    /// { temporary, for code eater
    
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
     * @param[in] individuals individuals at beginning of the universe
     * @param[in] environment environment
    */
    Universe(std::string name, std::vector<sp_individual> individuals, sp_environment environment);

     /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
     * @param[in] individuals individuals at beginning of the universe
     * @param[in] nb_max_individuals max number of individuals
     * @param[in] environment environment
    */
    Universe(std::string name, std::vector<sp_individual> individuals, int nb_max_individuals, sp_environment environment);

    /**
     * @brief Proceed to the next step
    */
    void next_step();

    /**
     * @brief Show the universe
    */
    void show();

    //----- getters
    std::string get_name();
    int get_nb_individuals();
    std::vector<sp_individual> get_individuals();
    sp_individual get_individual(int pos);
    sp_environment get_environment();
    std::vector<sp_environment> get_environments();
    int get_time();
    int getWidth();
    int getHeight();

    //----- setters
    void set_environment(std::string env_name);
    void set_environment(sp_environment env);
    void add_environment(sp_environment env);
    void set_individuals(std::vector<sp_individual> individuals);
    void add_individual(sp_individual individual);
    void remove_individual(int pos);

    //----- other
    std::string to_string();
    boost::json::object to_json();
    std::string is_ready();
};

typedef std::shared_ptr<Universe> sp_universe;
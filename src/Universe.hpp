#pragma once

#include "Declaration/PreprocessingDefinitions.hpp"
#include "Flow/Buffer/Buffer.hpp"
#include <map>
#include <string>

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
    sp_environment environment;   ///< environment with which the individual interacts
    sp_buffer buffer;             ///< buffer, to feed individual's input with environment's output and vice-vesra
        
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
     * @param[in] buffer buffer
    */
    Universe(std::string name, std::vector<sp_individual> individuals, sp_environment environment, sp_buffer buffer);

     /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
     * @param[in] individuals individuals at beginning of the universe
     * @param[in] nb_max_individuals max number of individuals
     * @param[in] environment environment
     * @param[in] buffer buffer
    */
    Universe(std::string name, std::vector<sp_individual> individuals, int nb_max_individuals, sp_environment environment, sp_buffer buffer);

    /**
     * @brief Initialize everything so that first step is smooth
    */
    void init();

    /**
     * @brief perform one environment step 
    */
    void next_step_environment();

    /**
     * @brief perform one step for the given individual
     * 
     * @param[in] individual_index index of the individual in the array of individuals
    */
    void next_step_individual(int individual_nb);

    /**
     * @brief perform on step for all the individuals
    */
    void next_step_individuals();

    /**
     * @brief Proceed to the next step
    */
    void next_step();

    /**
     * @brief Prepare some values for the individuals
     * 
     * Make the environment compute values and set them into the individuals inputs
     * 
     * @param[in] nb_values number of values to prepare
     * 
     * @return inputs for the individuals
    */
    std::vector<sp_flow> prepare_values(int nb_vals);

    /**
     * @brief Make the individuals compute and get their outputs
     * 
     * @param[in] vals values to compute
    */
    std::vector<sp_flow> individuals_compute(std::vector<sp_flow> vals);

    /**
     * @brief compute the errors between labels and predictions
     * 
     * @param[in] inputs input given to the individuals
     * @param[in] outputs output (predictions) of the individuals
     * @param[in] nb_flows number of individuals
    */
    std::vector<double> compute_errors(std::vector<sp_flow> inputs, std::vector<sp_flow> outputs, int nb_flows);

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
    int get_time();
    int getWidth();
    int getHeight();

    //----- setters
    void set_environment(sp_environment env);
    void set_individuals(std::vector<sp_individual> individuals);
    void add_individual(sp_individual individual);
    void remove_individual(int pos);

    //----- other
    std::string to_string();
    boost::json::object to_json();
    std::string is_ready();
};

typedef std::shared_ptr<Universe> sp_universe;
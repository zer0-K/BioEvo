#pragma once

#include "PreprocessingDefinitions.hpp"
#include "Buffer.hpp"
#include <map>
#include <string>

/// @brief universe for the experiments
class Universe
{
protected:
    std::string name;   ///< name of the universe

    int width;  ///< width of the universe
    int height; ///< height of the universe

    int number_of_individuals;      ///< current number of individuals in the universe
    int max_number_of_individuals;  ///< maximum number of individuals in the universe

    Individual** individuals;   ///< individuals living in the universe
    Environment* environment;   ///< environment with which the individual interacts
    Buffer* buffer;             ///< buffer, to feed individual's input with environment's output and vice-vesra
        
    std::map<Individual*, float> solutions;     ///< solutions of the problem

    int t;  ///< time

    bool state; ///< universe state

public:

    /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
    */
    Universe(std::string name);
    
    /**
     * @brief Constructor
     * 
     * @param[in] width width of the universe
     * @param[in] height height of the universe
    */
    Universe(const int width, const int height);

    /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
     * @param[in] individuals individuals at beginning of the universe
     * @param[in] nb_individuals number of individuals
     * @param[in] environment environment
     * @param[in] buffer buffer
    */
    Universe(std::string name, Individual** individuals, int nb_individuals, Environment* environment, Buffer* buffer);

     /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
     * @param[in] individuals individuals at beginning of the universe
     * @param[in] nb_individuals number of individuals
     * @param[in] nb_max_individuals max number of individuals
     * @param[in] environment environment
     * @param[in] buffer buffer
    */
    Universe(std::string name, Individual** individuals, int nb_individuals, int nb_max_individuals, Environment* environment, Buffer* buffer);

    /**
     * @brief Destructor
    */
    ~Universe();

    /**
     * @brief Proceed to the next step
    */
    void nextStep();

    /**
     * @brief Show the universe
    */
    void show();

    //----- getters
    std::string get_name();
    int getWidth();
    int getHeight();
};
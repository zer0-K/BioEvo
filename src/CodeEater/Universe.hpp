#pragma once

#include "PreprocessingDefinitions.hpp"
#include "CodeEaters/CodeEater.hpp"
#include "Computing/EatingProcessor.hpp"

/// @brief universe for the experiments
class Universe
{
protected:
    int width;  ///< width of the universe
    int height; ///< height of the universe

    int starting_row;   ///< starting row for the eating process (can change)
    int starting_col;   ///< starting col for the eating process (can change)

    int t;  ///< time

    /**
     * universe state : when a code eater's universe state is the same of this 
     * state, it means it has already changed state
    */
    bool state;

    CodeEater*** code_eaters;   ///< content of the universe : code eaters
    EatingProcessor* eating_processor;  ///< eating process


    /**
     * @brief Init code eaters
     * 
     * @param[out] code_eaters code eaters to init (partially, the rest of the init is in the experiment)
     * @param[in] width width of the universe
     * @param[in] height height of the universe
    */
    void initCodeEAters(CodeEater*** code_eaters, const int width, const int height);

    /**
     * @brief Init the scalars
     * 
     * @param[in] width width of the universe
     * @param[in] height height of the universe
     * @param[in] starting_row starting row of the eating process
     * @param[in] starting_col starting column of the eating process
    */
    void initScalars(const int width, const int height, int starting_row, int starting_col);

    /**
     * @brief Proceed to the next step
    */
    void nextStep();

public:
    
    /**
     * @brief Constructor
     * 
     * @param[in] eating_processor eating processor
     * @param[out] code_eaters code eaters to init (partially, the rest of the init is in the experiment)
     * @param[in] width width of the universe
     * @param[in] height height of the universe
    */
    Universe(EatingProcessor* eating_processor, CodeEater*** code_eaters, const int width, const int height);

    /**
     * @brief Constructor
     * 
     * @param[in] eating_processor eating processor
     * @param[out] code_eaters code eaters to init (partially, the rest of the init is in the experiment)
     * @param[in] width width of the universe
     * @param[in] height height of the universe
     * @param[in] starting_width starting width of the eating process
     * @param[in] starting_height starting height of the eating process
    */
    Universe(EatingProcessor* eating_processor, CodeEater*** code_eaters, const int width, const int height, int starting_width, int starting_height);

    /**
     * @brief Destructor
    */
    ~Universe();

    /**
     * @brief Show the universe
    */
    void show();

    /**
     * @brief Proceed to the next steps
     * 
     * @param nb_steps number of steps
    */
    void nextSteps(int nb_steps);

    //----- getters
    int getWidth();
    int getHeight();
    CodeEater*** getCodeEaters();
};
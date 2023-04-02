#pragma once

#include "../PreprocessingDefinitions.hpp"
#include "../CodeEaters/CodeEater.hpp"
#include "NeighborhoodManager.hpp"
#include "StateChanger.hpp"

/// @brief tell how the eating process works
class EatingProcessor
{
protected:
    //---------- spatial attributes
    int width;      ///< width of the universe
    int height;     ///< height of the universe
    int starting_row;   ///< starting row of the eating process
    int starting_col;   ///< starting column of the eating process

    //---------- computing attributes
    NeighborhoodManager* neighborhood_manager;  ///< neighborhood manager
    StateChanger* state_changer;    ///< change the state of the code eaters

    //---------- other
    NeighborHoodType neighborhood_type;  ///< neighborhood type for eating process

    /**
     * @brief Apply the eating process at row r and column c
     * 
     * @param[out] code_eaters code eaters
     * @param[in] r row number
     * @param[in] c column number
    */
    void apply(CodeEater*** code_eaters, int r, int c);

    /**
     * @brief Replace the case at the given coordinates by a new code eater (only if it has to)
     * @see StateChanger::changeState
     * 
     * @param[out] code_eaters the code eaters
     * @param[in] r row at which occurs the replacement
     * @param[in] c column at which occurs the replacement
    */
    void replace(CodeEater*** code_eaters, int r, int c);

public:
    /**
     * @brief Constructor
     * 
     * @param width width of the universe
     * @param height height of the universe
    */
    EatingProcessor(const int width, const int height);

    /**
     * @brief Constructor
     * 
     * @param width width of the universe
     * @param height height of the universe
     * @param starting_row starting row of the eating process
     * @param starting_col starting column of the eating process
    */
    EatingProcessor(const int width, const int height, int starting_row, int starting_col);

    /**
     * @brief PROCEED THE EATING
     * 
     * @param[out] code_eaters code eaters of the universe (first layer obviously)
    */
    void proceed(CodeEater*** code_eaters);
};
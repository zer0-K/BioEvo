#pragma once

#include "../Declaration/PreprocessingDefinitions.hpp"
#include "../Universe.hpp"
#include "CodeEaters/CodeEater.hpp"
#include "Computing/EatingProcessor.hpp"

/// @brief UniverseCodeEater for the ExperimentOldCodeEaters
class UniverseCodeEater : Universe
{
protected:
    int width;  ///< width of the UniverseCodeEater
    int height; ///< height of the UniverseCodeEater

    int starting_row;   ///< starting row for the eating process (can change)
    int starting_col;   ///< starting col for the eating process (can change)

    int t;  ///< time

    /**
     * UniverseCodeEater state : when a code eater's UniverseCodeEater state is the same of this 
     * state, it means it has already changed state
    */
    bool state;

    CodeEater*** code_eaters;   ///< content of the UniverseCodeEater : code eaters
    EatingProcessor* eating_processor;  ///< eating process


    /**
     * @brief Init code eaters
     * 
     * @param[out] code_eaters code eaters to init (partially, the rest of the init is in the ExperimentOldCodeEater)
     * @param[in] width width of the UniverseCodeEater
     * @param[in] height height of the UniverseCodeEater
    */
    void initCodeEAters(CodeEater*** code_eaters, const int width, const int height);

    /**
     * @brief Init the scalars
     * 
     * @param[in] width width of the UniverseCodeEater
     * @param[in] height height of the UniverseCodeEater
     * @param[in] starting_row starting row of the eating process
     * @param[in] starting_col starting column of the eating process
    */
    void initScalars(const int width, const int height, int starting_row, int starting_col);

    
public:
    
    /**
     * @brief Constructor
     * 
     * @param[in] eating_processor eating processor
     * @param[out] code_eaters code eaters to init (partially, the rest of the init is in the ExperimentOldCodeEater)
     * @param[in] width width of the UniverseCodeEater
     * @param[in] height height of the UniverseCodeEater
    */
    UniverseCodeEater(EatingProcessor* eating_processor, CodeEater*** code_eaters, const int width, const int height);

    /**
     * @brief Constructor
     * 
     * @param[in] eating_processor eating processor
     * @param[out] code_eaters code eaters to init (partially, the rest of the init is in the ExperimentOldCodeEater)
     * @param[in] width width of the UniverseCodeEater
     * @param[in] height height of the UniverseCodeEater
     * @param[in] starting_width starting width of the eating process
     * @param[in] starting_height starting height of the eating process
    */
    UniverseCodeEater(EatingProcessor* eating_processor, CodeEater*** code_eaters, const int width, const int height, int starting_width, int starting_height);

    /**
     * @brief Destructor
    */
    ~UniverseCodeEater();

    /**
     * @see Universe
    */
    void next_step();

    /**
     * @brief Show the UniverseCodeEater
    */
    void show();


    //----- getters
    CodeEater*** getCodeEaters();
};
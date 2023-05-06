#pragma once

#include "../../Declaration/PreprocessingDefinitions.hpp"
#include "../CodeEaters/CodeEater.hpp"
#include "FunctionPatternComputer.hpp"
#include "Utils/FunctionPattern.hpp"
#include "FunctionProcessor.hpp"
#include "RuleApplier.hpp"

/// @brief change the state of a code eater, and modify its neighbors accordingly
class StateChanger
{
private:
    /**
     * There is only one function pattern computer, one function pattern (that we change over time, one
     * function processor and one rule applier in the whole program, because there is only one state changer
     * All these computation elements are unique, the UniverseCodeEater and the code eaters are their objects
     * and not the opposite (in contrary to the set of rules for example) 
    */
    FunctionPatternComputer* function_pattern_computer;  ///< function pattern computer, to compute the function pattern to apply to the numbers
    FunctionPattern* function_pattern;  ///< function pattern to compute the numbers
    FunctionProcessor* function_processor;  ///< function processor
    RuleApplier* rule_applier;

    /**
     * @brief Compute the function pattern
     * 
     * @param[in] code_eater the eater to compute the number of
    */
    void computeFunctionPattern(CodeEater* code_eater);

    /**
     * @brief Compute the numbers beginning by the deepest layers
     * to compute the numbers, we need to compute the function patterns
     * 
     * @param[out] code_eater the eater to compute the number of
     * 
     * @return the computed number
    */
    int computeNumbers(CodeEater* code_eater);

    /**
     * @brief Apply the rule corresponding to the number, on the code eater and its neighbors
     * Apply the rules recursively, beginning by the deepest layers
     * 
     * @param[out] code_eater code eater to proceed eating process on
     * @param[out] neighbors neighbors of the code eaters
     * @param[in] neighborhood_type type of neighborhood (Von Neuman, Moore, line,...)
     * @param[out] rules set of rules of the code eater
     * @param[in] number number of the code eater
     * 
     * @return an index (in the neighborhood, not the UniverseCodeEater) telling the eating processor to create a new code eater there. -1 if none
    */
    int applyRule(CodeEater* code_eater, CodeEater** neighbors, NeighborHoodType neighborhood_type, 
        Permutation* rules, int number);

public:
    /**
     * @brief Constructor
     * 
     * @param neighborhood_manager neighborhood manager to get the index of the eaten code eaters in the neighborhood
    */
    StateChanger(NeighborhoodManager* neighborhood_manager);

    /**
     * @brief Change the state of a code eater and proceed the result on the neighborhood (eat/spit)
     * To change the state :
     *      - compute the rule number with the function pattern
     *      - apply the rule corresponding to that number
     * 
     * @param[out] code_eater code eater to proceed eating process on
     * @param[out] neighbors neighbors of the code eaters
     * @param[in] neighborhood_type type of neighborhood (Von Neuman, Moore, line,...)
     * 
     * @return an index (in the neighborhood, not the UniverseCodeEater) telling the eating processor to create a new code eater there. -1 if none
    */
    int changeState(CodeEater* code_eater, CodeEater** neighbors, NeighborHoodType neighborhood_type);
};
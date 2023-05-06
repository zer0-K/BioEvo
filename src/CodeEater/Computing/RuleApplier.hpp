#pragma once

#include "../../Declaration/PreprocessingDefinitions.hpp"
#include "Utils/Permutation.hpp"
#include "../CodeEaters/CodeEater.hpp"
#include "NeighborhoodManager.hpp"
#include "../ConstantsCodeEater.hpp"

/// @brief to apply a rule to a code eater and its neighbors
class RuleApplier
{
private:
    NeighborhoodManager* neighborhood_manager;  ///< neighborhood manager, to get the index of the eaten code eaters in the neighborhood

public:
    /**
     * @brief Constructor
     * 
     * @param neighborhood_manager neighborhood manager to get the index of the eaten code eaters in the neighborhood
    */
    RuleApplier(NeighborhoodManager* neighborhood_manager);

    /**
     * @brief Apply the rule to the code eater and its neighbors according to its rules and its number
     * 
     * @param[out] code_eater code eater to proceed eating process on
     * @param[out] neighborhood neighborhood
     * @param[in] neighborhood_type type of neighborhood (Von Neuman, Moore, line,...)
     * @param[in] neighborhood_manager neighborhood manager, to get the index of the eaten code eater
     * @param[out] rules_permutation the set of rules of the code eater (a permutation because the order of the rules can change)
     * @param[in] number the number of the code eater
     * 
     * (no getter for the number in CodeEater so that we can apply the rule correctly in the state changer)
     * 
     * @return an index (in the neighborhood, not the UniverseCodeEater) telling the parent that a case is empty
    */
    int applyRule(CodeEater* code_eater,CodeEater** neighborhood, NeighborHoodType neighborhood_type, 
        Permutation* rules_permutation, int number);

private:
    //---------- all the rules (snake case to correspond to the 'Rule' enum)

    /**
     * @brief do nothing
     * 
     * @return -1
    */
    int do_nothing();
   

    /**
     * @brief eat left, don't move and don't spit
     * 
     * @param[out] code_eater code eater to proceed eating process on
     * @param[out] neighborhood neighborhood
     * @param[in] neighborhood_type neighborhood type
     * @param[in] direction direction where to eat
     * 
     * @return index of the eaten code_eater in the neighborhood
    */
    int eat(CodeEater* code_eater,CodeEater** neighborhood, NeighborHoodType neighborhood_type, EatDirection direction);
};
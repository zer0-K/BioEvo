#include "RuleApplier.hpp"
#include "RuleNumberComputer.hpp"

#include <iostream>

RuleApplier::RuleApplier(NeighborhoodManager* neighborhood_manager)
{
    this->neighborhood_manager = neighborhood_manager;
}

int RuleApplier::applyRule(CodeEater* code_eater, CodeEater** neighborhood, NeighborHoodType neighborhood_type, 
    Permutation* rules_permutation, int number)
{
    Rule rule_number = RuleNumberComputer::computeCorrespondingRule(number);

    switch (rule_number)
    {
    case Rule::DO_NOTHING:
        return this->do_nothing();

    case Rule::EAT_UP:
        return this->eat(code_eater, neighborhood, neighborhood_type, UP_DIRECTION);

    case Rule::EAT_RIGHT:
        return this->eat(code_eater, neighborhood, neighborhood_type, RIGHT_DIRECTION);

    case Rule::EAT_DOWN:
        return this->eat(code_eater, neighborhood, neighborhood_type, DOWN_DIRECTION);

    case Rule::EAT_LEFT:
        return this->eat(code_eater, neighborhood, neighborhood_type, LEFT_DIRECTION);
    
    default:
        return this->do_nothing();
    }
}

int RuleApplier::do_nothing()
{
    return -1;
}

int RuleApplier::eat(CodeEater* code_eater, CodeEater** neighborhood, NeighborHoodType neighborhood_type, EatDirection direction)
{
#if DEBUG
    std::cout<<"-------------------- BALISE 1 -------------------- (end)"<<std::endl;
#endif

    // get the index corresponding to the 'up' direction in the neighborhoog for the given neighborhood type
    int eating_index = neighborhood_manager->getNeighborIndexFromDirection(neighborhood_type, UP_DIRECTION);

    // get the code eater to eat
    CodeEater* code_eater_to_eat = neighborhood[eating_index];
    neighborhood[eating_index] = new CodeEater(EATER_TOKEN_EMPTY);

    // PROCEED THE EATING
    code_eater->eat(code_eater_to_eat);
    code_eater_to_eat->setIsEaten(true);

#if DEBUG
    std::cout<<"-------------------- BALISE 2 -------------------- (end)"<<std::endl;
#endif

    // the place is now vacant
    return eating_index;
}
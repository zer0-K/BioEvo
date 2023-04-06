#include "StateChanger.hpp"

#include <iostream>

StateChanger::StateChanger(NeighborhoodManager* neighborhood_manager)
{
    // init computing elements
    this->function_pattern_computer = new FunctionPatternComputer();
    this->function_pattern = new FunctionPattern();
    this->function_processor = new FunctionProcessor();
    this->rule_applier = new RuleApplier(neighborhood_manager);
}

int StateChanger::changeState(CodeEater* code_eater, CodeEater** neighbors, NeighborHoodType neighborhood_type)
{
    // to change state, we need :
    // - to compute the rule number with the function pattern
    // - to apply the rule corresponding to that number
    
    // call sub methods that compute numbers and apply rules recursively

    //---------- (1) compute the rule number
    int number = this->computeNumbers(code_eater);
    code_eater->setNumber(number);

    //---------- (2) apply the rule
    int empty_neighbor_index = this->applyRule(code_eater, neighbors, neighborhood_type, 
        code_eater->getRules(), number);


    //---------- end of process functions

    // increment the lifetime of the code eater
    code_eater->timeIncr();

    // flip the UniverseCodeEater state
    code_eater->flipUniverseCodeEaterState();

    // if a neighbor has been eaten without being replaced, we need to warn the eating processor 
    // so that it can replace a code eater at this place (empty_neighbor_index=-1 if no replacement needed)
    return empty_neighbor_index;
}

void StateChanger::computeFunctionPattern(CodeEater* code_eater)
{
    // get the layer size for sublayer computation
    int layerSize = code_eater->getSubLayerSize();

    // compute the function pattern only if it has a sublayer (it should always be the case normally)
    if(layerSize != 0)
    {
        // get the eaten code eaters for computation
        CodeEater** eaten_code_eaters = code_eater->getEatenCodeEaters();

        // tokens of the sublayer, to compute the function pattern of the current code eater
        EaterToken tokens[layerSize];

        for(int i=0; i<layerSize; i++)
        {
            // get the token
            tokens[i] = eaten_code_eaters[i]->getToken();
        }

        // compute the function pattern
        this->function_pattern_computer->computeFunctionPattern(function_pattern, tokens);
    }
    else
    {
#if DEBUG
        std::cout<<"-------------------- ERROR ! -------------------- (beginning)"<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"In the state changer, while computing a function pattern (method 'computeFunctionPattern(...)'). ";
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"We are in the deepest sublayer (sublayer size = 0 here). No need to compute a function pattern. "<<std::endl;
        std::cout<<"The method StateChanger::computeNumbers should have directly returned the number ";
        std::cout<<"without having to go through the 'else' block (the condition 'layerSize==0'  ";
        std::cout<<"should have been true). "<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"-------------------- ERROR ! -------------------- (end)"<<std::endl;
#endif
    }
}

int StateChanger::computeNumbers(CodeEater* code_eater)
{
    // we need to begin by the deepest layers, so we need to do it recursively
    // We need to :
    // - compute the numbers of the sublayer
    // - compute the function pattern
    // - apply this function pattern to these numbers

    //---------- (1) get the numbers

    // get the layer size for sublayer computation
    int layerSize = code_eater->getSubLayerSize();

    // compute the number of the sublayer only if it has some
    if(layerSize == 0)      // (halting condition for this recursive function)
    {
        // if it doesn't have a sublayer, just return the number
        return code_eater->getNumber();

        // note that we don't use the function pattern here : no need to 
        // compute the function pattern when there is no sublayer
    }
    else
    {
        // get the eaten code eaters for computation
        CodeEater** eaten_code_eaters = code_eater->getEatenCodeEaters();

        // numbers of the sublayer, to compute the number of the current code eater
        int numbers[layerSize];

        for(int i=0; i<layerSize; i++)
        {
            // compute the numbers
            numbers[i] = this->computeNumbers(eaten_code_eaters[i]);
        }

        //---------- (2) get the function pattern (if no sublayer)
        this->computeFunctionPattern(code_eater);

        //---------- (3) apply the function pattern to the numbers (if no sublayer)
        return this->function_processor->ComputeFunction(function_pattern, numbers, layerSize);
    }
}



int StateChanger::applyRule(CodeEater* code_eater, CodeEater** neighbors, NeighborHoodType neighborhood_type, 
    Permutation* rules, int number)
{
    // all numbers have already been computed here, we need to apply the rules recursively beginning by
    // the deepest layers, from left to right
    // a code eater that has just being eaten will thus not see its rule be applied
    // we need to ensure here that all rules are applied correctly !! (this is the hardest function of the whole program)
    
    // get the layer size for sublayer computation
    int layerSize = code_eater->getSubLayerSize();

    // useful for later
    // when a code eater is eaten the place is vacant, we need to get the index in the neighborhood
    int neighborhood_index_empty;

    if(layerSize == 0)      // deepest layer
    {
        // if we are the deepest layer, we can apply the rule directly (skip the other else/else if)
    }
    else if(layerSize == 1)   // layer with only one eaten code eater (useful to treat this case apart for optimisation purposes)
    {
        // get the code eater
        CodeEater* eaten_code_eater = code_eater->getEatenCodeEaters()[0];

        // no neighbor, just apply the rules recursively
        neighborhood_index_empty = this->applyRule(eaten_code_eater, NULL, NO_NEIGHBOR, 
            eaten_code_eater->getRules(), eaten_code_eater->getNumber());

        // layer size = 1 => no neighbor => no eating... :(
        // so we do nothing with 'index_to_eat'
    }
    else
    {
        // here, the layer size is >1

        // otherwise, we need to go through the layer and apply from left to right
        bool loop = true;
        int index = 0;
        CodeEater** eaten_code_eaters_currentLayer = code_eater->getEatenCodeEaters();

        // variables to apply the rule and eating
        CodeEater* eaten_code_eater = eaten_code_eaters_currentLayer[0];    //< code eater of the sublayer
        CodeEater** neighbors = new CodeEater*[MAX_NEIGHBORS];  //< its neighbors
        CodeEater* code_eater_to_eat;                           //< the code eater it will probably eat
        bool isright;                                           //< tells if we eat right or left


        // for optimisation, we treat the first case apart (so that we don't have to perform a check at each loop)
        // the only neighnor is at the right
        neighbors[0] = eaten_code_eaters_currentLayer[index+1];

        // apply the rules recursively
        neighborhood_index_empty = this->applyRule(eaten_code_eater, neighbors, RIGHT, 
            eaten_code_eater->getRules(), eaten_code_eater->getNumber());

        // if the index is not -1 (it must be 0) actualize the layer
        if(neighborhood_index_empty == 0)
        {
            // move everyone to the left
            for(int i=index+1;i<layerSize-1;i++) // layerSize-1 because a code eater has been eaten (the layer size is updated in StateChanger::applyRule)
            {
                // move on left
                eaten_code_eaters_currentLayer[i] = eaten_code_eaters_currentLayer[i+1];
            }

            // update layer size
            layerSize--;

            // increment index
            index++;
        }

        while(loop)
        {
            // get the current code eater
            eaten_code_eater = eaten_code_eaters_currentLayer[index];


            // first, we need to check if we are at the end of the layer (no right neighbor in this case)
            if(index == layerSize-1)
            {
                // get its neighborhood
                neighbors[0] = eaten_code_eaters_currentLayer[index-1];
                // we don't care if neighbors[1] is not NULL since the neighborhood type is 'LEFT' (only the first index is needed)

                neighborhood_index_empty = this->applyRule(eaten_code_eater, neighbors, LEFT, 
                    eaten_code_eater->getRules(), eaten_code_eater->getNumber());
            }
            else
            {
                // get its neighborhood
                neighbors[0] = eaten_code_eaters_currentLayer[index-1];
                neighbors[1] = eaten_code_eaters_currentLayer[index+1];

                neighborhood_index_empty = this->applyRule(eaten_code_eater, neighbors, LEFT_AND_RIGHT, 
                    eaten_code_eater->getRules(), eaten_code_eater->getNumber());
            }

            // if a code eater has been eaten, we need to actualize the layer
            if(neighborhood_index_empty == 0)
            {
                // move everyone to the left
                for(int i=index+1;i<layerSize-1;i++) // layerSize-1 because a code eater has been eaten (the layer size is updated in StateChanger::applyRule)
                {
                    // move on left
                    eaten_code_eaters_currentLayer[i] = eaten_code_eaters_currentLayer[i+1];
                }

                // update layer size
                layerSize--;

                // does not increment the index because we have moved everyone to the left, thus the next code eater is at the current index
            }
            else if(neighborhood_index_empty == 1)
            {
                // move everyone to the left
                for(int i=index+1;i<layerSize-1;i++) // layerSize-1 because a code eater has been eaten (the layer size is updated in StateChanger::applyRule)
                {
                    // move on left
                    eaten_code_eaters_currentLayer[i] = eaten_code_eaters_currentLayer[i+1];
                }

                // update layer size
                layerSize--;

                // increment index
                index++;
            }
            else 
            {
                // just increment the index
                index++;
            }
            
            // stop looping if we are at the end of the loop
            if(index == layerSize)
            {
                loop = false;
            }
        }
    }
    
    // all the sublayer rules has been applied, we now have to apply the rule for the current code eater,
    // so we use the rule applier
    neighborhood_index_empty = this->rule_applier->applyRule(code_eater, neighbors, neighborhood_type, 
        code_eater->getRules(), number);

    // telling the parent that a place is empty since a code eater has been eaten (-1 if not empty/no code eater eaten)
    return neighborhood_index_empty;
}
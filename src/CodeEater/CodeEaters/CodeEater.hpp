#pragma once

#include "../../Declaration/PreprocessingDefinitions.hpp"
#include "../ConstantsCodeEater.hpp"
#include "../Computing/Utils/Permutation.hpp"

/// @brief elementary unit of the ExperimentOldCodeEaters
class CodeEater
{
private:
    //---------- identity
    int identifier; ///< identifier of the code eater
    int lifetime;   ///< lifetime of the code eater
    bool UniverseCodeEater_state;    ///< UniverseCodeEater state @see UniverseCodeEater::state
    bool isEaten;   ///< true if the code eater has been eaten

    //---------- computing identity
    EaterToken token;   ///< eater token
    int number;     ///< number of the code eater (computed from its sublayers if it has some)
    Permutation* rules_permutation;  ///< permutation of the rules

    //---------- inner identity
    bool hasSubLayer;   ///< true if the code eater has eaten some code eaters
    int subLayerSize;   ///< number of eaten code eaters
    CodeEater** eaten_code_eaters;  ///< eaten code eaters

public:
    /**
     * @brief Constructor
    */
    CodeEater();

    /**
     * @brief Constructor
     * 
     * @param token token of the code eater
    */
    CodeEater(EaterToken token);

    /**
     * @brief Constructor
     * 
     * @param token token of the code eater
     * @param identifier identifier of the code eater
    */
    CodeEater(EaterToken token, int identifier);

    /**
     * @brief Constructor
     * 
     * @param identifier identifier of the code eater
     * @param lifetime lifetime of the code eater
    */
    CodeEater(int identifier, int lifetime);

    /**
     * @brief Constructor
     * 
     * @param identifier identifier of the code eater
     * @param lifetime lifetime of the code eater
     * @param token token of the code eater
    */
    CodeEater(int identifier, int lifetime, EaterToken token);

    /**
     * @brief Eat the given code eater
     * 
     * @param code_eater code eater to eat
    */
    void eat(CodeEater* code_eater);

    /**
     * @brief Show the code eater info
    */
    void show();

    //---------- end of process methods

    /**
     * @brief Increment lifetime
    */
    void timeIncr();

    /**
     * @brief flip the UniverseCodeEater state (so that we know if the current code eater has been processed by the eating processor or not)
    */
    void flipUniverseCodeEaterState();

    //---------- getters
    
    bool getUniverseCodeEaterState();
    bool getIsEaten();
    EaterToken getToken();
    int getNumber();
    Permutation* getRules();
    int getSubLayerSize();
    CodeEater** getEatenCodeEaters();

    //---------- setters
    
    void setNumber(int number);
    void setIsEaten(bool isEaten);
    void incrementLayerSize();
    void decrementLayerSize();
};
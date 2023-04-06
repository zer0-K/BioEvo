#include <iostream>

#include "CodeEater.hpp"
#include "../ConstantsCodeEater.hpp"

CodeEater::CodeEater()
    : CodeEater(DEFAULT_IDENTIFIER, DEFAULT_LIFETIME, DEFAULT_EATER_TYPE)
{
    // call the other constructor, that's all
}

CodeEater::CodeEater(EaterToken token)
    : CodeEater(DEFAULT_IDENTIFIER, DEFAULT_LIFETIME, token)
{
    // call the other constructor, that's all
}

CodeEater::CodeEater(EaterToken token, int identifier)
    : CodeEater(identifier, DEFAULT_LIFETIME, token)
{
    // call the other constructor, that's all
}

CodeEater::CodeEater(int identifier, int lifetime)
    : CodeEater(identifier, lifetime, DEFAULT_EATER_TYPE)
{
    // call the other constructor, that's all
}

CodeEater::CodeEater(int identifier, int lifetime, EaterToken token)
{
    //---------- identity
    this->identifier = identifier;
    this->lifetime = lifetime;
    this->UniverseCodeEater_state = INITIAL_UniverseCodeEater_STATE; 

    //---------- computing identity
    this->token = token;
    this->number = token;   // the number of the code eater is initially the token (as an int)
    this->rules_permutation = new Permutation();  ///< permutation of the rules

    //---------- inner identity
    this->hasSubLayer = false;  // no sublayer initially
    this->subLayerSize = 0;     // no sublayer initially
    this->eaten_code_eaters = new CodeEater*[MAX_EATING_CODE_EATER]; // empty
}

void CodeEater::eat(CodeEater* code_eater)
{
#if DEBUG
    std::cout<<"-------------------- code eater eaten (id "<< this->identifier <<") -------------------- (beginning)"<<std::endl;
#endif

    // place the code eater at the last position
    this->eaten_code_eaters[subLayerSize] = code_eater;

    // increment the size of the sublayer
    this->incrementLayerSize();

    this->hasSubLayer = true;
}

void CodeEater::show()
{
    // show the code eater token, ID and lifetime
    std::cout<<"("<<token<<";"<<number<<";"<<identifier<<";"<<lifetime<<")\t";
}

//---------- end of process methods

void CodeEater::timeIncr()
{
    // increment lifetime
    this->lifetime++;
}

void CodeEater::flipUniverseCodeEaterState()
{
    // flip the UniverseCodeEater state
    this->UniverseCodeEater_state = !this->UniverseCodeEater_state;
}


//---------- getters

bool CodeEater::getUniverseCodeEaterState() { return this->UniverseCodeEater_state; }
bool CodeEater::getIsEaten() { return this->isEaten; }
EaterToken CodeEater::getToken() { return this->token; }
int CodeEater::getNumber() { return this->number; }
Permutation* CodeEater::getRules() { return this->rules_permutation; }
int CodeEater::getSubLayerSize() { return this->subLayerSize; }
CodeEater** CodeEater::getEatenCodeEaters() { return this->eaten_code_eaters; }

//---------- setters

void CodeEater::setNumber(int number) { this->number = number; }
void CodeEater::setIsEaten(bool isEaten) { this->isEaten = isEaten; }
void CodeEater::incrementLayerSize() { this->subLayerSize++; }
void CodeEater::decrementLayerSize() { this->subLayerSize--; }
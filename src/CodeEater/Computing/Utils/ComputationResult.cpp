#include "ComputationResult.hpp"

ComputationResult::ComputationResult()
{
    // do nothing for the moment
}

//---------- getters

int ComputationResult::getIndexRuleTranspose1() { return this->index_rule_transpose_1; }
int ComputationResult::getIndexRuleTranspose2() { return this->index_rule_transpose_2; }
bool ComputationResult::getEat() { return this->eat; }
int ComputationResult::getIndexEat() { return this->index_to_eat; }
bool ComputationResult::getSpit() { return this->spit; }
int ComputationResult::getIndexSpit() { return this->index_to_spit; }



//---------- setters
void ComputationResult::setIndexRuleTranspose1(int index_rule_transpose_1) { this->index_rule_transpose_1 = index_rule_transpose_1; }
void ComputationResult::setIndexRuleTranspose2(int index_rule_transpose_2) { this->index_rule_transpose_2 = index_rule_transpose_2; }
void ComputationResult::setEat(bool eat) { this->eat = eat; }
void ComputationResult::setIndexEat(int index_to_eat) { this->index_to_eat = index_to_eat; }
void ComputationResult::setSpit(bool spit) { this->spit = spit; }
void ComputationResult::setIndexSpit(int index_to_spit) { this->index_to_spit = index_to_spit; }
#include "RuleNumberComputer.hpp"

Rule RuleNumberComputer::computeCorrespondingRule(int number)
{
    int rule_number = number%NUMBER_OF_RULES;

    switch (rule_number)
    {
    case 0:
        return Rule::DO_NOTHING;

    case 1:
        return Rule::EAT_UP;

    case 2:
        return Rule::EAT_RIGHT;

    case 3:
        return Rule::EAT_DOWN;

    case 4:
        return Rule::EAT_LEFT;

    default:
        return Rule::DO_NOTHING;
    }
}
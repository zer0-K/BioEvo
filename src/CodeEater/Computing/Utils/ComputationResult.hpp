#pragma once

class ComputationResult
{
private:
    //---------- rule transposition
    int index_rule_transpose_1; ///< first rule index to reposition
    int index_rule_transpose_2; ///< second rule index to reposition

    //---------- eating/ejecting
    bool eat;   ///< true if the result is to eat a code eater
    int index_to_eat;   ///< neighborhood index to eat (there will be a code eater there)

    bool spit;  ///< true if the result is to spit a code eater
    int index_to_spit;  ///< neighborhood index to spit/eject (only if the place is free to welcome a code eater)

public:
    /**
     * @brief Constructor
    */
    ComputationResult();

    //---------- getters
    int getIndexRuleTranspose1();
    int getIndexRuleTranspose2();
    bool getEat();
    int getIndexEat();
    bool getSpit();
    int getIndexSpit();

    //---------- setters
    void setIndexRuleTranspose1(int index_rule_transpose_1);
    void setIndexRuleTranspose2(int index_rule_transpose_2);
    void setEat(bool eat);
    void setIndexEat(int index_to_eat);
    void setSpit(bool spit);
    void setIndexSpit(int index_to_spit);
};
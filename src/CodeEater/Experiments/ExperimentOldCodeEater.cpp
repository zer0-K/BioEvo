#include <iostream>

#include "ExperimentOldCodeEater.hpp"
#include "../ConstantsCodeEater.hpp"

ExperimentOldCodeEater::ExperimentOldCodeEater()
    : ExperimentOldCodeEater::ExperimentOldCodeEater(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
    // does nothing
}

ExperimentOldCodeEater::ExperimentOldCodeEater(const int width, const int height)
    : ExperimentOld(width, height)
{
    this->code_eaters = new CodeEater**[height];

    // create the eating process
    this->eating_processor = new EatingProcessor(width, height);

    // create the UniverseCodeEater
    this->universe = (Universe*) new UniverseCodeEater(this->eating_processor, this->code_eaters, width, height);
}

void ExperimentOldCodeEater::show()
{
    this->universe->show();
}

void ExperimentOldCodeEater::loop()
{
    this->loop();
}
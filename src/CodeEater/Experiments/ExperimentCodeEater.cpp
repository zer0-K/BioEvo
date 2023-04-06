#include <iostream>

#include "ExperimentCodeEater.hpp"
#include "../ConstantsCodeEater.hpp"

ExperimentCodeEater::ExperimentCodeEater()
    : ExperimentCodeEater::ExperimentCodeEater(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
    // does nothing
}

ExperimentCodeEater::ExperimentCodeEater(const int width, const int height)
    : Experiment(width, height)
{
    this->code_eaters = new CodeEater**[height];

    // create the eating process
    this->eating_processor = new EatingProcessor(width, height);

    // create the UniverseCodeEater
    this->universe = (Universe*) new UniverseCodeEater(this->eating_processor, this->code_eaters, width, height);
}

void ExperimentCodeEater::show()
{
    this->universe->show();
}

void ExperimentCodeEater::loop()
{
    this->loop();
}
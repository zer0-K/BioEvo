#pragma once

#include "../../../Experiment/Experiment.hpp"

class ConsoleApp : public Experiment
{
protected:


public:
    ConsoleApp();

    void init() override;

    void launch() override;
};
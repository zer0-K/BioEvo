#pragma once

#include "../../../Experiment/Experiment.hpp"

class SimpleLinearAlgos : public Experiment
{
protected:


public:
    SimpleLinearAlgos();

    void init() override;

    void launch() override;

    void launch_simple_1();
};
#pragma once

#include "../../../Experiment.hpp"

class FunctionExecutionEvoX : public Experiment
{
protected:


public:
    FunctionExecutionEvoX();

    void init() override;

    void launch() override;
};

typedef std::shared_ptr<FunctionExecutionEvoX> sp_experiment_func_exec_evox;
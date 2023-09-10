#pragma once

#include "../../../Experiment.hpp"

class GenerationRecursiveOps : public Experiment
{
protected:


public:
    GenerationRecursiveOps();

    void init() override;

    void launch() override;
};

typedef std::shared_ptr<GenerationRecursiveOps> sp_experiment_gen_recursive_ops;

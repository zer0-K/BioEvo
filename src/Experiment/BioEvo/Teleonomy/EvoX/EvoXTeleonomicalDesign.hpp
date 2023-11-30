#pragma once

#include "../../../Experiment.hpp"

#include "../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

class EvoXTeleonomicalDesign : public Experiment
{
protected:


public:
    EvoXTeleonomicalDesign();

    void init() override;

    void launch() override;

    sp_evox get_algo(std::string name);

    void test_setup();
};

typedef std::shared_ptr<EvoXTeleonomicalDesign> sp_experiment_evox_teleodesign;
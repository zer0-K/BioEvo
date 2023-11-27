#pragma once

#include "../../../../Experiment.hpp"

#include "../../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

class ReplicationEvoXQuine : public Experiment
{
protected:


public:
    ReplicationEvoXQuine();

    void init() override;

    void launch() override;

    void simple_quine(sp_evox algo);

    void quine_function_trigger(sp_evox algo);

    void finding_empty_place(sp_evox algo);
};

typedef std::shared_ptr<ReplicationEvoXQuine> sp_experiment_replication_evox_quine;
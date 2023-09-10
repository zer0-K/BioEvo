#pragma once

#include "../../../../Experiment.hpp"

class ReplicationEvoXQuine : public Experiment
{
protected:


public:
    ReplicationEvoXQuine();

    void init() override;

    void launch() override;
};

typedef std::shared_ptr<ReplicationEvoXQuine> sp_experiment_replication_evox_quine;
#pragma once

#include "../../../../Experiment.hpp"

class ReplicationEvoX : public Experiment
{
protected:


public:
    ReplicationEvoX();

    void init() override;

    void launch() override;
};

typedef std::shared_ptr<ReplicationEvoX> sp_experiment_replication_evox;
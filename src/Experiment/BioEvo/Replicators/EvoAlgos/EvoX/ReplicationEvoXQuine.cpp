#include "ReplicationEvoXQuine.hpp"

#include "../../../../../Utils/Constants.hpp"
#include "../../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"

ReplicationEvoXQuine::ReplicationEvoXQuine()
    :Experiment::Experiment(name_exp_bioevo_replication_evox_quine)
{
    init();
}

void ReplicationEvoXQuine::init()
{
    const int universe_size = 2;

    universe = std::make_shared<UniverseEvoAlgos>(
        universe_size,
        name
    );
}

void ReplicationEvoXQuine::launch()
{
    const int nb_steps = 10;

    for(int i=0; i<nb_steps; i++)
    {
        universe->exec();
    }
}


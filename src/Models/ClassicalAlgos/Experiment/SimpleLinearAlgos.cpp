#include "SimpleLinearAlgos.hpp"

#include "../../../Utils/Constants.hpp"
#include "../Universe/UniverseClassicalAlgos.hpp"

#include "../Data/Generation/DataGeneratorLinear.hpp"

SimpleLinearAlgos::SimpleLinearAlgos()
    :Experiment::Experiment(name_exp_console_app)
{
    init();
}

void SimpleLinearAlgos::init()
{
    const int universe_size = 2;

    universe = std::make_shared<UniverseClassicalAlgos>(
        universe_size,
        name
    );
}

void SimpleLinearAlgos::launch()
{
    launch_simple_1();
}

void SimpleLinearAlgos::launch_simple_1()
{
    // TODO : use universe instead of just feeding data in the algos

    sp_datagen_linear datagen = std::make_shared<DataGeneratorLinear>();

    auto data = datagen->generate_test(100);
}
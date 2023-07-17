#include "LinearAlgos.hpp"

#include <iostream>

#include "../../../Utils/Constants.hpp"

#include "../Universe/UniverseClassicalAlgos.hpp"

#include "SimpleLinearAlgos.hpp"

LinearAlgos::LinearAlgos()
    :Experiment::Experiment(name_exp_console_app)
{
    init();
}

void LinearAlgos::init()
{
    const int universe_size = 2;

    universe = std::make_shared<UniverseClassicalAlgos>(
        universe_size,
        name
    );
}

void LinearAlgos::launch()
{
    // choose experiment

    int experiment_nb = 0;

    std::cout << "Choose an evolutionary linear experiment : " << std::endl;
    std::cout << "\t0 - linear simple" << std::endl;

    std::cin >> experiment_nb;

    // launch experiment

    std::unique_ptr<Experiment> experiment;

    switch (experiment_nb)
    {
    case 0:
        experiment = std::make_unique<SimpleLinearAlgos>(); 
        break;
    
    default:
        std::cout << "Wrong number given, default : linear simple" << std::endl;
        experiment = std::make_unique<SimpleLinearAlgos>();
        break;
    }

    experiment->init();
    experiment->launch();
}

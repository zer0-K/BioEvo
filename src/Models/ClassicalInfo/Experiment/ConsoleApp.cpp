#include "ConsoleApp.hpp"

#include "../../../Utils/Constants.hpp"
#include "../Universe/UniverseClassicalInfo.hpp"

ConsoleApp::ConsoleApp()
    :Experiment::Experiment(name_exp_console_app)
{
    init();
}

void ConsoleApp::init()
{
    const int universe_size = 2;

    universe = std::make_shared<UniverseClassicalInfo>(
        universe_size,
        name
    );
}

void ConsoleApp::launch()
{
    const int nb_steps = 10;

    for(int i=0; i<nb_steps; i++)
    {
        universe->exec();
    }
}

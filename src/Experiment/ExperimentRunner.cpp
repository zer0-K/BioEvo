#include "ExperimentRunner.hpp"

#include <iostream>

void ExperimentRunner::launch()
{
    int answer = 0;

    std::cout << name << " : " << std::endl << std::endl;

    while(answer >= 0 && answer < experiments.size())
    {
        std::cout << "Choose an experiment :" << std::endl;

        for(int i=0;i<experiments.size(); i++)
        {
            std::cout << "\t" << i << " - " << experiments[i]->get_name() << std::endl;
        }

        std::cout << std::endl;
        std::cin >> answer ;

        if(answer < 0 || answer >= experiments.size())
        {
            std::cout << "Exiting..." << std::endl;
        }
        else
        {
            experiments[answer]->launch();
        }
    }
}
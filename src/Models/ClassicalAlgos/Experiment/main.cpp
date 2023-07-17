#include <iostream>
#include<memory>

#include "LinearAlgos.hpp"

int main(int argc, char* argv[])
{
    void exec_experiment(int);

    int experiment_nb = 0;

    std::cout << "Choose a classical algo experiment : " << std::endl;
    std::cout << "\t0 - linear models" << std::endl;

    std::cin >> experiment_nb;

    exec_experiment(experiment_nb);

    return 0;
}

void exec_experiment(int experiment_number)
{
    std::unique_ptr<Experiment> experiment;

    switch (experiment_number)
    {
    case 0:
        experiment = std::make_unique<LinearAlgos>(); 
        break;
    
    default:
        std::cout << "Wrong number given, default : linear models" << std::endl;
        experiment = std::make_unique<LinearAlgos>();
        break;
    }

    experiment->launch();
}
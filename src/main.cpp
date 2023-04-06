#include <iostream>
#include "string.h"

#include "Experiment.hpp"
#include "CodeEater/Experiments/ExperimentCodeEater.hpp"
#include "CodeEater/Experiments/ExperimentCodeEater1.hpp"
#include "CodeEater/Experiments/ExperimentCodeEater2.hpp"
#include "CodeEater/Experiments/ExperimentCodeEater3.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    void launch_experiment_code_eaters();
    int experiment_number = 3;
    
    cout<<"Please choose which model to experiment with : "<<endl;
    cout<<"0 - Self changing code "<<endl;
    cout<<"1 - Evolutionary Turing machines "<<endl;
    cin>>experiment_number;

    // create the according experiment
    switch (experiment_number)
    {
        case 1:
            launch_experiment_code_eaters();
            break;
        
        default:
            launch_experiment_code_eaters();
            break;
    }
    
}

void launch_experiment_code_eaters()
{
    int experimentCodeEater_number = 3;
    ExperimentCodeEater* ExperimentCodeEater;

    cout<<"Please give an int to choose an ExperimentCodeEater (between 1 and 3). Default : 3."<<endl;
    cin>>experimentCodeEater_number;

    // create the according ExperimentCodeEater
    switch (experimentCodeEater_number)
    {
        case 1:
            ExperimentCodeEater = new ExperimentCodeEater1();
            break;

        case 2:
            ExperimentCodeEater = new ExperimentCodeEater2();
            break;
        
        case 3:
            ExperimentCodeEater = new ExperimentCodeEater3();
            break;
        
        default:
            ExperimentCodeEater = new ExperimentCodeEater3();
            break;
    }

    ExperimentCodeEater->launch();
}

#include <iostream>
#include "string.h"

#include "Utils/Log/logpaths.hpp"

#include "ExperimentOld.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater1.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater2.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater3.hpp"

#include "Experiments/ClassicalAlgos/experiment_classical_algo_1.hpp"

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
    ExperimentOldCodeEater* experimentOldCodeEater;

    cout<<"Please give an int to choose an ExperimentCodeEater (between 1 and 3). Default : 3."<<endl;
    cin>>experimentCodeEater_number;

    // create the according ExperimentCodeEater
    switch (experimentCodeEater_number)
    {
        case 1:
            experimentOldCodeEater = new ExperimentOldCodeEater1();
            break;

        case 2:
            experimentOldCodeEater = new ExperimentOldCodeEater2();
            break;
        
        case 3:
            experimentOldCodeEater = new ExperimentOldCodeEater3();
            break;
        
        default:
            experimentOldCodeEater = new ExperimentOldCodeEater3();
            break;
    }

    experimentOldCodeEater->launch();
}

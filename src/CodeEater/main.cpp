#include <iostream>
#include "string.h"

#include "Experiments/Experiment1.hpp"
#include "Experiments/Experiment2.hpp"
#include "Experiments/Experiment3.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    int experiment_number = 3;
    Experiment* experiment;

    
    // check command line args
    if(argc==2)
        experiment_number = atoi(argv[1]);
    else
        cout<<"Please give an int to choose an experiment (between 1 and 3). Default : 3."<<endl;

    // create the according experiment
    switch (experiment_number)
    {
        case 1:
            experiment = new Experiment1();
            break;

        case 2:
            experiment = new Experiment2();
            break;
        
        case 3:
            experiment = new Experiment3();
            break;
        
        default:
            experiment = new Experiment3();
            break;
    }

    experiment->launch();
    
}

#include <iostream>
#include <random>

#include "Constants.hpp"
#include "Server/Server.hpp"
#include "ExperimentOld.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater1.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater2.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater3.hpp"

#include "Experiments/Experiment_1_00/experiment_1_00.hpp"

int main(int argc, char* argv[])
{
    std::default_random_engine generator;

    void launch_server();
    void launch_experiment_code_eaters();
    void launch_experiment_classical_algos();
    int experiment_number = 3;
   
    std::cout<<"Please choose which model to experiment with : "<<std::endl;

    std::cout<<EXPERIMENT_NUMBER_WEB                <<" - Web interface"                <<std::endl;
    std::cout<<EXPERIMENT_NUMBER_CLASSICAL_ALGOS    <<" - Classical algorithms"         <<std::endl;
    //std::cout<<EXPERIMENT_NUMBER_SELF_CHANGING_CODE <<" - Self changing code"           <<std::endl;
    //std::cout<<EXPERIMENT_NUMBER_CODE_EATER         <<" - Evolutionary Turing machines "<<std::endl;

    std::cin>>experiment_number;

    int experiment_result_status = 0;

    // create the according experiment
    // switch case not possible because of constant vals
    if(experiment_number == EXPERIMENT_NUMBER_WEB)
    {
        launch_server();
    }
    else if(experiment_number == EXPERIMENT_NUMBER_CLASSICAL_ALGOS)      //-----     classical algos
    {
        experiment_result_status = experiment_1();
    }
    else if(experiment_number == EXPERIMENT_NUMBER_SELF_CHANGING_CODE)  //-----    self changing code 
    {
        // for the moment, code eaters
        launch_experiment_code_eaters();
    }
    else
    {
        launch_experiment_code_eaters(); 
    }

    if(experiment_result_status == 0)
    {
        std::cout<<"Experiment succeeded"<<std::endl;
    }
    else
    {
        std::cout<<"Experiment failed"<<std::endl;
    }
    
}

void launch_experiment_code_eaters()
{
    int experimentCodeEater_number = 3;
    ExperimentOldCodeEater* experimentOldCodeEater;

    std::cout<<"Please give an int to choose an ExperimentCodeEater (between 1 and 3). Default : 3."<<std::endl;
    std::cin>>experimentCodeEater_number;

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

void launch_server()
{
    try
    {
        const std::string address_str = "127.0.0.1";
        const int port_nb = 4300;
        const std::string target = "/bio-evo-api";
        int version = 11;
 
        auto const address = net::ip::make_address(address_str);
        unsigned short port = static_cast<unsigned short>(port_nb);
        std::cout<<"----------"<<std::endl;

        std::cout<<"Connecting to " + address_str + ":" + std::to_string(port_nb) + target<<std::endl;

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        tcp::socket socket{ioc};
        http_server(acceptor, socket);

        ioc.run();
    }
    catch(std::exception const& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
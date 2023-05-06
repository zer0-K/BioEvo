#include <iostream>
#include <random>

#include "Declaration/Constants.hpp"
#include "Server/Server.hpp"
#include "Utils/Config/config.hpp"
#include "Utils/Config/ConfigRunner.hpp"
#include "Utils/json/interprete_json.hpp"
#include "ExperimentOld.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater1.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater2.hpp"
#include "CodeEater/Experiments/ExperimentOldCodeEater3.hpp"

#include "Experiments/experiment_1.hpp"

int main(int argc, char* argv[])
{
    std::default_random_engine generator;

    void launch_server();
    void launch_config_mode();
    void launch_experiment_code_eaters();
    void launch_experiment_classical_algos();
    int experiment_number = 3;
   
    std::cout<<"Please choose which model to experiment with : "<<std::endl;

    std::cout<<EXPERIMENT_NUMBER_WEB                <<" - Web interface"                <<std::endl;
    std::cout<<EXPERIMENT_NUMBER_CONFIG             <<" - Config mode"                  <<std::endl;
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
    else if(experiment_number == EXPERIMENT_NUMBER_CONFIG)
    {
        launch_config_mode();
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
        std::cout<< "Wrong number given, launching server" << std::endl;
        launch_server(); 
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
        const int port_nb = 4301;
        const std::string target = "/bio-evo-api";
        int version = 11;
 
        auto const address = net::ip::make_address(address_str);
        unsigned short port = static_cast<unsigned short>(port_nb);
        std::cout<<"----------"<<std::endl;

        std::cout<<"Connecting to " + address_str + ":" + std::to_string(port_nb) + target<<std::endl;

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        tcp::socket socket{ioc};
        Framework* framework = new Framework();
        ConfigRunner* cr = new ConfigRunner(framework); 
        http_server(acceptor, socket, framework, cr);

        ioc.run();
    }
    catch(std::exception const& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void launch_config_mode()
{
    std::vector<std::string> configs = get_config_names();
    size_t nb_cfg = configs.size();

    int config_nb = 0;

    std::cout<<"Select the config to launch"<<std::endl;
    for(int i=0;i<nb_cfg;i++)
    {
        std::cout<< i << " - " << configs[i] <<std::endl;
    }

    std::cin>>config_nb;

    if(config_nb>=nb_cfg || config_nb<0)
    {
        std::cout << "Wrong config number given, selecting config 0" << std::endl;
        config_nb = 0;
    }

    std::string cfg_txt = get_config_content(configs[config_nb]);
    std::vector<boost::json::object> instructions = convert_to_objs(cfg_txt);

    Framework* framework = new Framework();
    ConfigRunner* cr = new ConfigRunner(framework); 

    cr->add_instructions(instructions);
    cr->continue_exec();
}
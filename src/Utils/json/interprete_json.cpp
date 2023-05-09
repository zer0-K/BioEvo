#include "interprete_json.hpp"

#include "../../Individual/IndividualLinear.hpp"
#include "../../Environment/EnvironmentLinear.hpp"

std::vector<boost::json::object> convert_to_objs(std::string instr_txt)
{
    std::vector<boost::json::object> instructions = std::vector<boost::json::object>();

    boost::json::value json_val = boost::json::parse(instr_txt);
    
    if( auto p = json_val.if_object())
    {
        int nb_instructions = ((*p)["nb instructions"]).as_int64();

        // iterate through all JSON instructions
        for(int i=0; i<nb_instructions;i++)
        {
            if( auto instr = ( (*p)["instruction "+std::to_string(i+1)] ).if_object())
            {
                instructions.push_back(*instr);   
            }
        } 
    }

    return instructions;
}

std::string exec_instr(sp_framework framework, std::string instr_name, boost::json::object* instr_params)
{ 
    if(instr_name == "ADD_UNIVERSE")
        return add_universe(framework, instr_params);
    if(instr_name == "ADD_ENVIRONMENT")
        return add_environment(framework, instr_params);
    if(instr_name == "SET_INDIVIDUALS")
        return set_individuals(framework, instr_params);
    if(instr_name == "ADD_INDIVIDUAL")
        return add_individual(framework, instr_params);
    if(instr_name == "ADD_INDIVIDUALS")
        return add_individuals(framework, instr_params);
    if(instr_name == "LAUNCH")
        return launch(framework, instr_params);
}

std::string add_universe(sp_framework framework, boost::json::object* params)
{
    boost::json::value* jname = params->if_contains("name");
    boost::json::value* jenvironment = params->if_contains("current environment");
    boost::json::value* jindividuals = params->if_contains("individuals");

    if(jname != nullptr)
    {
        std::string message = "";

        std::string name = boost::json::value_to<std::string>(*jname);

        if(name == "")
            return "Error : can't add universe, please provide a name for the universe";
        else if (framework->get_universe_pos(name) != -1)
            return "Error : can't add " + name + ", already exists";


        framework->add_universe(std::make_shared<Universe>(name));

        if(jenvironment != nullptr)
        {
            boost::json::object* params_jenv = new boost::json::object();
            (*params_jenv)["universe name"] = name;
            (*params_jenv)["current environment"] = *jenvironment;
            message += add_environment(framework, params_jenv);

            if(message.substr(0, 5) == "Error")
                return message;
        }

        if(jindividuals != nullptr)
        {
            boost::json::object* params_jindiv = new boost::json::object();
            (*params_jindiv)["universe name"] = name;
            (*params_jindiv)["nb individuals"] = *(jindividuals->if_object()->if_contains("nb individuals"));
            (*params_jindiv)["individuals"] = *(jindividuals->if_object()->if_contains("individuals"));
            message += set_individuals(framework, params_jindiv);

            if(message.substr(0, 5) == "Error")
                return message;
        }
        
        return "Success";
    }
    else
    {
       return "Error : can't add universe : must provide a name for the universe";
    }
}

std::string add_environment(sp_framework framework, boost::json::object* params)
{
    boost::json::value* jname_universe = params->if_contains("universe name");
    boost::json::object* jenvironment = params->if_contains("current environment")->if_object();

    if(jname_universe != nullptr && jenvironment != nullptr)
    {
        std::string universe_name = boost::json::value_to<std::string>(*jname_universe);

        boost::json::value* jenv_name = jenvironment->if_contains("name");

        if(jenv_name != nullptr)
        {
            std::string env_name = boost::json::value_to<std::string>(*jenv_name);

            if(env_name == "")
                return "Error : can't add universe, please provide a name for the environment";
            else if (framework->get_universe_pos(universe_name) == -1)
                return "Error : can't add " + env_name + " to " + universe_name + " : universe does not exist";


            // set the environment to the universe   
            // TODO : for the moment, linear environment
            int dim = 1;
            std::vector<double> w(dim, 3);
            double b = 4;
            sp_environment env = std::make_shared<EnvironmentLinear>(env_name, dim, w, b);
            framework->set_environment(env, universe_name);

            return "Success";
        }
        else
        {
            return "Error : can't add environment to " + universe_name + " : must provide an environment name";
        }
    }
    else
    {
        if(jname_universe == nullptr)
            return "Error : can't add environment : must provide the name of the universe to link the environment to";

        if(jenvironment == nullptr)
            return "Error : can't add environment : must provide a minimal environment";
    }
}

std::string set_individuals(sp_framework framework, boost::json::object* params)
{
    boost::json::value* jname_universe  = params->if_contains("universe name");
    boost::json::value* jnb_individuals = params->if_contains("nb individuals");
    boost::json::array* jindividuals    = params->if_contains("individuals")->if_array();

    if(jname_universe != nullptr && jnb_individuals !=nullptr && jindividuals != nullptr)
    {
        std::string universe_name = boost::json::value_to<std::string>(*jname_universe);
        int nb_individuals = boost::json::value_to<int>(*jnb_individuals);

        std::vector<sp_individual> individuals = std::vector<sp_individual>(nb_individuals);

        for(int i=0;i<nb_individuals;i++)
        {
            // get the characteristics of the individual
            std::string name_individual =   boost::json::value_to<std::string>( *(jindividuals->at(i).if_object()->if_contains("name"))     );
            int dimension_individual    =   boost::json::value_to<int>(         *(jindividuals->at(i).if_object()->if_contains("dimension")));
            
            // add the individual
            individuals[i] = std::make_shared<IndividualLinear>(name_individual, dimension_individual);
        }

        framework->set_individuals(individuals, universe_name); 

        return "Success";
    }
    else
    {
        if(jname_universe == nullptr)
            return "Error : can't set individuals : must provide the name of the universe to link the individuals to";
        if(jnb_individuals == nullptr)
            return "Error : can't set individuals : must provide the number of individuals to set";
         if(jindividuals == nullptr)
            return "Error : can't set individuals : must provide the individuals"; 
    }
}

std::string add_individual(sp_framework framework, boost::json::object* params)
{
    boost::json::value* jname_universe  = params->if_contains("universe name");
    boost::json::object* jindividual    = params->if_contains("individual")->if_object();

    if(jname_universe != nullptr && jindividual != nullptr)
    {
        // get the characteristics
        std::string universe_name   =   boost::json::value_to<std::string>( *jname_universe                         );
        std::string name_individual =   boost::json::value_to<std::string>( *(jindividual->if_contains("name"))     );
        int dimension_individual    =   boost::json::value_to<int>(         *(jindividual->if_contains("dimension")));

        sp_individual individual = std::make_shared<IndividualLinear>(name_individual, dimension_individual);
        framework->add_individual(individual, universe_name);

        return "Success";
    }
    else
    {
        if(jname_universe == nullptr)
            return "Error : can't add individual : must provide the name of the universe to link the individuals to";
         if(jindividual == nullptr)
            return "Error : can't add individual : must provide the individuals"; 
    }
}

std::string add_individuals(sp_framework framework, boost::json::object* params)
{
    boost::json::value* jname_universe = params->if_contains("universe name");
    boost::json::value* jnb_individuals = params->if_contains("nb individuals");
    boost::json::array* jindividuals = params->if_contains("individuals")->if_array();

    if(jname_universe != nullptr && jnb_individuals !=nullptr && jindividuals != nullptr)
    {
        std::string universe_name = boost::json::value_to<std::string>(*jname_universe);
        int nb_individuals = boost::json::value_to<int>(*jnb_individuals);

        for(int i=0;i<nb_individuals;i++)
        {
            // get the characteristics of the individual
            std::string name_individual = boost::json::value_to<std::string>(*(jindividuals->at(i).if_object()->if_contains("name")));
            int dimension_individual = boost::json::value_to<int>(*(jindividuals->at(i).if_object()->if_contains("dimension")));

            // create the individual
            sp_individual individual = std::make_shared<IndividualLinear>(name_individual, dimension_individual);

            // add the individual
            framework->add_individual(individual, universe_name);
        } 

        return "Success";
    }
    else
    {
        if(jname_universe == nullptr)
            return "Error : can't add individuals : must provide the name of the universe to link the individuals to";
        if(jnb_individuals == nullptr)
            return "Error : can't add individuals : must provide the number of individuals to set";
         if(jindividuals == nullptr)
            return "Error : can't add individuals : must provide the individuals"; 
    }
}

std::string launch(sp_framework framework, boost::json::object* params)
{
    boost::json::value* jname_universe  = params->if_contains("universe name");
    boost::json::value* jnb_steps       = params->if_contains("nbbsteps");

    if(jname_universe != nullptr || jnb_steps == nullptr)
    {
        std::string universe_name = boost::json::value_to<std::string>(*jname_universe);
        int nb_steps = boost::json::value_to<int>(*jnb_steps);

        return framework->launch(universe_name, nb_steps);
    }
    else
    {
        if(jname_universe == nullptr)
            return "Error : can't launch experiment : must provide a universe name";
         if(jnb_steps == nullptr)
            return "Error : can't launch experiment : must provide a number of steps to perform";
   }
}
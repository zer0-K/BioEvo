#include "json_interprete.hpp"

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

std::string exec_instr(Framework* framework, std::string instr_name, boost::json::object* instr_params)
{ 
    if(instr_name == "ADD_UNIVERSE")
        return add_universe(framework, instr_params);
    if(instr_name == "ADD_ENVIRONMENT")
        return add_environment(framework, instr_params);
}

std::string add_universe(Framework* framework, boost::json::object* params)
{
    boost::json::value* jname = params->if_contains("name");
    boost::json::value* jenvironment = params->if_contains("environment");
    boost::json::value* jindividuals = params->if_contains("individuals");

    if(jname != nullptr)
    {
        std::string message = "";

        std::string name = boost::json::value_to<std::string>(*jname);

        framework->add_universe(new Universe(name));

        if(jenvironment != nullptr)
        {
            boost::json::object* params_jenv = new boost::json::object();
            (*params_jenv)["universe name"] = name;
            (*params_jenv)["environment"] = *jenvironment;
            message = add_environment(framework, params_jenv);

            if(message.substr(0, 5) == "Error")
                return message;
        }
    }
    else
    {
        return "Error : can't add universe : must provide a name for the universe";
    }
}

std::string add_environment(Framework* framework, boost::json::object* params)
{
    boost::json::value* jname_universe = params->if_contains("universe name");
    boost::json::object* jenvironment = params->if_contains("environment")->if_object();

    if(jname_universe != nullptr && jenvironment != nullptr)
    {
        std::string universe_name = boost::json::value_to<std::string>(*jname_universe);

        boost::json::value* jenv_name = jenvironment->if_contains("name");

        if(jenv_name != nullptr)
        {
            std::string env_name = boost::json::value_to<std::string>(*jenv_name);
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
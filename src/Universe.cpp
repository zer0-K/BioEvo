#include <iostream>

#include "Universe.hpp"
#include "Declaration/Constants.hpp"
#include "Utils/Log/Logger.hpp"
#include "Utils/Convert/tostring.hpp"

Universe::Universe(const int width, const int height)
{
    this->width = width;
    this->height = height;
}

Universe::Universe(std::string name)
{
    this->name = name;
    this->number_of_individuals = 0;
    this->max_number_of_individuals = DEFAULT_NB_MAX_INDIVIDUALS;
    this->individuals = std::vector<sp_individual>();
    this->current_environment = nullptr;

    this->environments = std::vector<sp_environment>();
}

Universe::Universe(std::string name, std::vector<sp_individual> individuals, sp_environment environment)
    : Universe::Universe(name, individuals, DEFAULT_NB_MAX_INDIVIDUALS, environment)
{
    // do nothing here
}

Universe::Universe(std::string name, std::vector<sp_individual> individuals, int nb_max_individuals, sp_environment environment)
{
    logger_write(1, FLAG_INIT + FLAG_BEGIN + "Creating universe. name : " + name + "...");

    this->name = name;
    number_of_individuals = individuals.size();
    this-> max_number_of_individuals = nb_max_individuals;
    this->individuals = individuals;
    current_environment = environment;

    // init some stuff to before first step
    current_environment->init_values();

    this->environments = std::vector<sp_environment>();
    this->environments.push_back(environment);

    logger_write(1, FLAG_INIT + FLAG_END + this->name + " created");
}

void Universe::next_step()
{
    current_environment->evolve();

    for(int i=0;i<number_of_individuals;i++)
    {
        individuals[i]->evolve();
    }

    t++;
}

void Universe::show()
{
    std::cout<<"Universe name : "<<name<<std::endl;
    std::cout<<"\tEnvironment name : "<<current_environment->get_name()<<std::endl;
    std::cout<<"\tIndividuals : "<<std::endl;
    for(int i=0; i<number_of_individuals; i++)
    {
        std::cout<<"\t\t"<<individuals[i]->get_name()<<std::endl;
    }
}


//-------------------- getters

std::string Universe::get_name()
{
    return name;
}


int Universe::get_nb_individuals()
{
    return number_of_individuals;
}

std::vector<sp_individual> Universe::get_individuals()
{
    return individuals;
}

sp_individual Universe::get_individual(int pos)
{
    return individuals[pos];
}

sp_environment Universe::get_environment()
{
    return current_environment;
}

std::vector<sp_environment> Universe::get_environments()
{
    return environments;
}

int Universe::get_time()
{
    return t;
}

int Universe::getWidth()
{
    return width;
}

int Universe::getHeight()
{
    return height;
}

//---------- setters

void Universe::set_environment(std::string env_name)
{
    for(int i=0; environments.size(); i++)
    {
        if(environments[i]->get_name() == env_name)
        {
            current_environment = environments[i];
        }
    }
}

void Universe::set_environment(sp_environment env)
{
    current_environment = env;
}

void Universe::add_environment(sp_environment env)
{
    bool isin = false;

    for(int i=0; i<environments.size();i++)
    {
        if(environments[i]->get_name() == env->get_name())
        {
            isin = true;
            break;
        }
    }

    if(!isin)
    {
        environments.push_back(env);
    }
}

void Universe::set_individuals(std::vector<sp_individual> individuals)
{
    number_of_individuals = individuals.size();
    this->individuals = individuals;
}

void Universe::add_individual(sp_individual individual)
{
    bool isin = false;
    for(int i=0;i<number_of_individuals;i++)
    {
        if(individuals[i]->get_name() == individual->get_name())
        {
            isin = true;
            break;
        }
    }
    
    if(!isin)
    {
        individuals.push_back(individual);
        number_of_individuals++;
    } 
}

void Universe::remove_individual(int pos)
{
    number_of_individuals--;
    individuals.erase(individuals.begin() + pos);
}

//---------- other

std::string Universe::to_string()
{
    std::string res = "";

    res += name + " : nb_individuals=" + std::to_string(number_of_individuals);
    res += " ; max_nb_individuals=" + std::to_string(max_number_of_individuals);
    res += " individuals :";
    for(int i=0;i<number_of_individuals;i++)
    {
        res += " " + individuals[i]->to_string();
    }
    res += " ; environment : " + current_environment->to_string();

    return res;
}

boost::json::object Universe::to_json()
{
    boost::json::object juniverse;

    juniverse["name"] = name;

    if(current_environment == nullptr)
        juniverse["current environment"] = "null";
    else
        juniverse["current environment"] = current_environment->object_to_json();

    if(environments.empty())
    {
        juniverse["environments"] = "null";
    }
    else
    {
        boost::json::object jenvs;
        for(int i=0;environments.size();i++)
            jenvs[environments[i]->get_name()] = environments[i]->object_to_json();
        juniverse["environments"] = jenvs;
    }

    juniverse["nb individuals"] = number_of_individuals;
    juniverse["max_nb_individuals"] = max_number_of_individuals;
    boost::json::object jindividuals;
    for(int i=0;i<number_of_individuals;i++)
        jindividuals[individuals[i]->get_name()] = individuals[i]->object_to_json();   
    juniverse["individuals"] = jindividuals;

    return juniverse;
}

std::string Universe::is_ready()
{
    bool is_ready = true;
    std::string message = "Universe missing content : ";
    std::string env_message = "";
    std::string individuals_messages = "";

    if(name == "")
    {
        message += "name, ";
        is_ready = false;
    }
    else
    {
        message = "Missing content of " + name + " : ";
    }

        
    if(current_environment == nullptr)
    {
        message += "environment, ";
        is_ready = false;
    }
    else
    {
        env_message = current_environment->is_ready(); 
    }

        
    if(individuals.size() == 0 || number_of_individuals == 0)
    {
        is_ready = false;
        message += "individuals, ";
    }
    else
    {
        bool indiv_ready = true;
        std::string indiv_message;

        for(int i=0;i<number_of_individuals;i++)
        {
            indiv_message = individuals[i]->is_ready();

            if(indiv_message != "ready")
            {
                indiv_ready = false;
                individuals_messages += indiv_message;
            }
        }

        if(indiv_ready)
            individuals_messages = "ready";
    }

    if(env_message != "" && env_message != "ready")
    {
        is_ready = false;
        message += env_message;
    }

    if(individuals_messages != "" && individuals_messages != "ready")
    {
        is_ready = false;
        message += individuals_messages;
    }

    if(is_ready)
        return "ready";

    return message;
}
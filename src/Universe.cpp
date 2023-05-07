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
    this->environment = nullptr;
    this->buffer = nullptr;
}

Universe::Universe(std::string name, std::vector<sp_individual> individuals, sp_environment environment, sp_buffer buffer)
    : Universe::Universe(name, individuals, DEFAULT_NB_MAX_INDIVIDUALS, environment, buffer)
{
    // do nothing here
}

Universe::Universe(std::string name, std::vector<sp_individual> individuals, int nb_max_individuals, sp_environment environment, sp_buffer buffer)
{
    logger_write(1, FLAG_INIT + FLAG_BEGIN + "Creating universe. name : " + name + "...");

    this->name = name;
    this->number_of_individuals = individuals.size();
    this-> max_number_of_individuals = nb_max_individuals;
    this->individuals = individuals;
    this->environment = environment;
    this->buffer = buffer;

    this->epochs_individuals = std::vector<int>(this->number_of_individuals, DEFAULT_NB_EPOCHS_LEARN);

    // init some stuff to before first step
    this->environment->init(epochs_individuals);

    logger_write(1, FLAG_INIT + FLAG_END + this->name + " created");
}

void Universe::init()
{
    std::vector<sp_flow> inputs_for_individuals = this->prepare_values(100); 

    for(int i=0;i<this->number_of_individuals;i++)
    {
        this->individuals[i]->set_input(inputs_for_individuals[i]);
    }
}

void Universe::next_step_environment()
{
    this->environment->evolve(this->epochs_individuals);
}

void Universe::next_step_individual(int individual_index)
{
    this->individuals[individual_index]->evolve();
}

void Universe::next_step_individuals()
{
    for(int i=0; i<this->number_of_individuals; i++)
    {
        this->next_step_individual(i);
    }
}

void Universe::next_step()
{
    // first, feed inputs with the outputs of the other
    this->buffer->feed_ins_and_outs(this->individuals, this->environment);

    // TODO allow the experimenter to act between each of the steps ?

    // then, makes the individuals and the environment evolve
    this->next_step_individuals();
    this->next_step_environment();
}

std::vector<sp_flow> Universe::prepare_values(int nb_vals)
{
    // code is similar to Buffer:feed_ins_and_outs, but here it gets the env out and does nothing with individuals out

    this->environment->compute(this->number_of_individuals, nb_vals);

    sp_flow environment_out = environment->get_output();
    
    // transforms the environment output into input for the individuals 
    std::vector<sp_flow> inputs_for_individuals = this->buffer->transform_environment_out_to_individuals_in(environment_out, this->number_of_individuals);

    // set individuals inputs
    for(int i=0;i<this->number_of_individuals;i++)
    {
        this->individuals[i]->set_input(inputs_for_individuals[i]);
    }

    return inputs_for_individuals; 
}

std::vector<sp_flow> Universe::individuals_compute(std::vector<sp_flow> values)
{
    std::vector<sp_flow> individuals_out;

    // compute individuals' outputs one by one
    for(int i=0; i<this->number_of_individuals;i++)
    {
        sp_flow individual_out = this->individuals[i]->compute(values[i]);
        individuals_out[i] = individual_out;
    }

    return individuals_out;
}

std::vector<double> Universe::compute_errors(std::vector<sp_flow> inputs, std::vector<sp_flow> outputs, int nb_flows)
{
    // compute the errors for each flow
    std::vector<double> errors(nb_flows);
    for(int i=0;i<nb_flows;i++)
    {
        errors[i] += this->buffer->compute_errors(inputs[i], outputs[i]);
    }

    return errors;
}

void Universe::show()
{
    std::cout<<"Universe name : "<<this->name<<std::endl;
    std::cout<<"\tEnvironment name : "<<this->environment->get_name()<<std::endl;
    std::cout<<"\tIndividuals : "<<std::endl;
    for(int i=0; i<this->number_of_individuals; i++)
    {
        std::cout<<"\t\t"<<this->individuals[i]->get_name()<<std::endl;
    }
}


//-------------------- getters

std::string Universe::get_name()
{
    return this->name;
}


int Universe::get_nb_individuals()
{
    return this->number_of_individuals;
}

std::vector<sp_individual> Universe::get_individuals()
{
    return this->individuals;
}

sp_individual Universe::get_individual(int pos)
{
    return this->individuals[pos];
}

sp_environment Universe::get_environment()
{
    return this->environment;
}

int Universe::get_time()
{
    return this->t;
}

int Universe::getWidth()
{
    return this->width;
}

int Universe::getHeight()
{
    return this->height;
}

//---------- setters

void Universe::set_environment(sp_environment env)
{
    this->environment = env;
}

void Universe::set_individuals(std::vector<sp_individual> individuals)
{
    this->number_of_individuals = individuals.size();
    this->individuals = individuals;
}

void Universe::add_individual(sp_individual individual)
{
    bool isin = false;
    for(int i=0;i<this->number_of_individuals;i++)
    {
        if(this->individuals[i]->get_name() == individual->get_name())
        {
            isin = true;
            break;
        }
    }
    
    if(!isin)
    {
        this->individuals.push_back(individual);
        this->number_of_individuals++;
    } 
}

void Universe::remove_individual(int pos)
{
    this->number_of_individuals--;
    this->individuals.erase(this->individuals.begin() + pos);
}

//---------- other

std::string Universe::to_string()
{
    std::string res = "";

    res += this->name + " : nb_individuals=" + std::to_string(this->number_of_individuals);
    res += " ; max_nb_individuals=" + std::to_string(this->max_number_of_individuals);
    res += " individuals :";
    for(int i=0;i<this->number_of_individuals;i++)
    {
        res += " " + this->individuals[i]->to_string();
    }
    res += " ; environment : " + this->environment->to_string();
    res += " ; buffer : " + this->buffer->to_string();

    return res;
}

boost::json::object Universe::to_json()
{
    boost::json::object juniverse;

    juniverse["name"] = this->name;

    if(this->environment == nullptr)
        juniverse["environment"] = "null";
    else
        juniverse["environment"] = this->environment->to_json();

    juniverse["nb individuals"] = this->number_of_individuals;
    juniverse["max_nb_individuals"] = this->max_number_of_individuals;
    boost::json::object jindividuals;
    for(int i=0;i<this->number_of_individuals;i++)
        jindividuals[this->individuals[i]->get_name()] = this->individuals[i]->to_json();   
    juniverse["individuals"] = jindividuals;

    /*
    std::string res = "{";

    res += "name:" + this->name + ",nb_individuals:" + std::to_string(this->number_of_individuals);
    res += ",'max nb individuals':" + std::to_string(this->max_number_of_individuals);
    res += ",'epochs for individuals':" + convert_str(this->epochs_individuals, this->get_nb_individuals());
    res += ",'individuals':[";
    for(int i=0;i<this->number_of_individuals;i++)
    {
        res += this->individuals[i]->to_json() +",";
    }
    res.replace( res.size()-1, 1, "");
    res += "],'environment':" + this->environment->to_json();
    res += ",'buffer':" + this->buffer->to_json();
    res += "}";

    return res;*/
    return juniverse;
}

std::string Universe::is_ready()
{
    bool is_ready = true;
    std::string message = "Universe missing content : ";
    std::string env_message = "";
    std::string individuals_messages = "";

    if(this->name == "")
    {
        message += "name, ";
        is_ready = false;
    }
    else
    {
        message = "Missing content of " + this->name + " : ";
    }

        
    if(this->environment == nullptr)
    {
        message += "environment, ";
        is_ready = false;
    }
    else
    {
        env_message = this->environment->is_ready(); 
    }

        
    if(this->individuals.size() == 0 || this->number_of_individuals == 0)
    {
        is_ready = false;
        message += "individuals, ";
    }
    else
    {
        bool indiv_ready = true;
        std::string indiv_message;

        for(int i=0;i<this->number_of_individuals;i++)
        {
            indiv_message = this->individuals[i]->is_ready();

            if(indiv_message != "ready")
            {
                indiv_ready = false;
                individuals_messages += indiv_message;
            }
        }

        if(indiv_ready)
            individuals_messages = "ready";
    }

    if(this->buffer == nullptr)
        message += "buffer, ";

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
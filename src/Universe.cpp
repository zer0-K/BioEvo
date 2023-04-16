#include <iostream>

#include "Universe.hpp"
#include "Constants.hpp"
#include "Utils/Log/Logger.hpp"
#include "Utils/Convert/tostring.hpp"

Universe::Universe(const int width, const int height)
{
    this->width = width;
    this->height = height;
}

Universe::Universe(std::string name, Individual** individuals, int nb_individuals, Environment* environment, Buffer* buffer)
    : Universe::Universe(name, individuals, nb_individuals, DEFAULT_NB_MAX_INDIVIDUALS, environment, buffer)
{
    // do nothing here
}

Universe::Universe(std::string name, Individual** individuals, int nb_individuals, int nb_max_individuals, Environment* environment, Buffer* buffer)
{
    logger_write(1, FLAG_INIT + FLAG_BEGIN + "Creating universe. name : " + name + "...");

    this->name = name;
    this->number_of_individuals = nb_individuals;
    this-> max_number_of_individuals = nb_max_individuals;
    this->individuals = individuals;
    this->environment = environment;
    this->buffer = buffer;

    int* epochs_individuals = new int[nb_individuals];
    for(int i=0;i<nb_individuals;i++)
    {
        epochs_individuals[i] = DEFAULT_NB_EPOCHS_LEARN;
    }
    this->epochs_individuals = epochs_individuals;

    // init some stuff to before first step
    this->environment->init(nb_individuals, epochs_individuals);

    logger_write(1, FLAG_INIT + FLAG_END + this->name + " created");
}

void Universe::next_step_environment()
{
    logger_write(3, FLAG_INFO + FLAG_BEGIN + "Next step for " + this->environment->get_name() + " from " + this->name + "...");

    this->environment->evolve(this->number_of_individuals, this->epochs_individuals);

    logger_write(3, FLAG_INFO + FLAG_END + "Step of" + this->environment->get_name() + " from " + this->name + " ended");
}

void Universe::next_step_individual(int individual_index)
{
    logger_write(4, FLAG_INFO + FLAG_BEGIN + "Next step for individual " + std::to_string(individual_index) + " from " + this->name + "...");

    this->individuals[individual_index]->evolve();

    logger_write(4, FLAG_INFO + FLAG_END + "Step of individual " + std::to_string(individual_index) + " from " + this->name + " ended");
}

void Universe::next_step_individuals()
{
    logger_write(3, FLAG_INFO + FLAG_BEGIN + "Next step for individuals of " + this->name + "...");

    for(int individual_index  = 0; individual_index<this->number_of_individuals; individual_index++)
    {
        this->next_step_individual(individual_index);
    }

    logger_write(3, FLAG_INFO + FLAG_END + "Step of individuals of " + this->name + " ended");
}

void Universe::next_step()
{
    logger_write(2, FLAG_INFO + FLAG_BEGIN + "Next step of " + this->name + "...");

    // first, feed inputs with the outputs of the other
    this->buffer->feed_ins_and_outs(this->individuals, this->number_of_individuals, this->environment);

    // TODO allow the experimenter to act between each of the steps ?

    // then, makes the individuals and the environment evolve
    this->next_step_individuals();
    this->next_step_environment();

    logger_write(2, FLAG_INFO + FLAG_END + "Step of " + this->name + " ended");
}

Flow** Universe::prepare_values(int nb_vals)
{
    // code is similar to Buffer:feed_ins_and_outs, but here it gets the env out and does nothing with individuals out

    this->environment->compute(this->number_of_individuals, nb_vals);

    Flow* environment_out = environment->get_output();
    
    // transforms the environment output into input for the individuals 
    Flow** inputs_for_individuals = this->buffer->transform_environment_out_to_individuals_in(environment_out, this->number_of_individuals);

    // set individuals inputs
    for(int i=0;i<this->number_of_individuals;i++)
    {
        this->individuals[i]->set_input(inputs_for_individuals[i]);
    }

    return inputs_for_individuals; 
}

Flow** Universe::individuals_compute(Flow** values)
{
    Flow** individuals_out = new Flow*[this->number_of_individuals];

    for(int i=0; i<this->number_of_individuals;i++)
    {
        Flow* individual_out = this->individuals[i]->compute(values[i]);
        individuals_out[i] = individual_out;
    }

    return individuals_out;
}

double* Universe::compute_errors(Flow** inputs, Flow** outputs, int nb_flows)
{
    double* errors = new double[nb_flows];
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

Individual** Universe::get_individuals()
{
    return this->individuals;
}

int Universe::getWidth()
{
    return this->width;
}

int Universe::getHeight()
{
    return this->height;
}

//---------- other

std::string Universe::to_string()
{
    std::string res = "";

    res += this->name + " : nb_individuals=" + std::to_string(this->number_of_individuals);
    res += " ; max_nb_individuals=" + std::to_string(this->max_number_of_individuals);
    res += " ; epochs for individuals : " + convert_str(this->epochs_individuals, this->get_nb_individuals());
    res += " individuals :";
    for(int i=0;i<this->number_of_individuals;i++)
    {
        res += " " + this->individuals[i]->to_string();
    }
    res += " ; environment : " + this->environment->to_string();
    res += " ; buffer : " + this->buffer->to_string();

    return res;
}
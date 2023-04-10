#include <iostream>

#include "Universe.hpp"
#include "Constants.hpp"

Universe::Universe(const int width, const int height)
{
    this->width = width;
    this->height = height;
}

Universe::Universe(std::string name, Individual** individuals, int nb_individuals, Environment* environment, Buffer* buffer)
    : Universe::Universe(name, individuals, nb_individuals, DEFAULT_NB_MAX_INDIVIDUALS, environment, buffer)
{

}

Universe::Universe(std::string name, Individual** individuals, int nb_individuals, int nb_max_individuals, Environment* environment, Buffer* buffer)
{
    this->name = name;
    this->number_of_individuals = nb_individuals;
    this->individuals = individuals;
    this->environment = environment;
    this->buffer = buffer;
}

Universe::~Universe()
{
    // does nothing
}

void Universe::nextStep()
{
    // first, feed inputs with the outputs of the other
    // TODO more complex feeding ?
    for(int individual_i=0; individual_i<this->number_of_individuals; individual_i++)
    {
        this->buffer->feed_ins_and_outs(this->individuals[individual_i], this->environment);
    }

    // TODO allow the experimenter to act between each of the steps ?

    // then, makes the individuals and the environment evolve
    for(int individual_i=0; individual_i<this->number_of_individuals; individual_i++)
    {
        this->individuals[individual_i]->evolve();
    }
    this->environment->evolve();
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

int Universe::getWidth()
{
    return this->width;
}

int Universe::getHeight()
{
    return this->height;
}
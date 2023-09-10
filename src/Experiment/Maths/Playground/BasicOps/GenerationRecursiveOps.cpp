#include "GenerationRecursiveOps.hpp"

#include "../../../../Utils/Constants.hpp"
#include "../../../../Models/Maths/Playground/BasicOps/RecursiveBasicOps.hpp"

GenerationRecursiveOps::GenerationRecursiveOps()
    :Experiment::Experiment(name_exp_maths_gen_recursive_ops)
{
    init();
}

void GenerationRecursiveOps::init()
{

}

void GenerationRecursiveOps::launch()
{
    RecursiveApplier* test = new RecursiveApplier();
}

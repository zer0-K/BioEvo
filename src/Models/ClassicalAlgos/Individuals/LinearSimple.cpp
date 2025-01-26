#include "LinearSimple.hpp"

#include "../../../Utils/Constants.hpp"
#include "../Biology/Gene/GeneGaussian.hpp"
#include "../Data/ClassicalValidationData.hpp"

LinearSimple::LinearSimple(std::string name, int dim)
    :ClassicalIndividual::ClassicalIndividual(name)
{
    coeffs = std::vector<sp_abstracttrait>(dim);    
    phenotypic_body = std::vector<sp_gene>(dim);

    for(int d=0;d<dim;d++)
    {
        std::shared_ptr<Trait<double>> coeff_d = std::make_shared<Trait<double>>(0);
        coeffs[d] = coeff_d;

        sp_gene_gauss gene_d = std::make_shared<GeneGaussian>(0, 1, coeff_d);
    }
}

LinearSimple::LinearSimple(std::string name, std::vector<double> coeffs)
    :ClassicalIndividual::ClassicalIndividual(name)
{
    this->coeffs = std::vector<sp_abstracttrait>(coeffs.size());    
    phenotypic_body = std::vector<sp_gene>(coeffs.size());

    for(int d=0;d<coeffs.size();d++)
    {
        std::shared_ptr<Trait<double>> coeff_d = std::make_shared<Trait<double>>(coeffs[d]);
        this->coeffs[d] = coeff_d;

        sp_gene_gauss gene_d = std::make_shared<GeneGaussian>(0, 1, coeff_d);
    }
}

LinearSimple::LinearSimple(std::string name, std::vector<double> coeffs,
    std::vector<double> means, std::vector<double> std_devs)
    :ClassicalIndividual::ClassicalIndividual(name)
{
    this->coeffs = std::vector<sp_abstracttrait>(coeffs.size());    
    phenotypic_body = std::vector<sp_gene>(coeffs.size());

    for(int d=0;d<coeffs.size();d++)
    {
        std::shared_ptr<Trait<double>> coeff_d = std::make_shared<Trait<double>>(coeffs[d]);
        this->coeffs[d] = coeff_d;

        sp_gene_gauss gene_d = std::make_shared<GeneGaussian>(means[d], std_devs[d], coeff_d);
    }
}


void LinearSimple::init()
{
    ClassicalIndividual::init();

    type = CA_LIN_SIMP;
    add_type(CA_LIN_SIMP);
}

std::vector<sp_entity> LinearSimple::exec(std::vector<sp_entity> entries)
{
    // execute the individual model on each entry
    for(int i=0;i<entries.size(); i++)
    {
        // entries should be classical algo data (test/validation)
        if(entries[i]->is_type(CA_DATA))
        {
            sp_classical_data data = std::dynamic_pointer_cast<ClassicalData>(entries[i]); 
            compute_single(data);
        }
    }

    return entries;
}

void LinearSimple::compute_single(sp_classical_data data)
{
    if(data->get_x().size() == coeffs.size())
    {
        // compute model prediction
        double prediction = 0;
        for(int i=0;i<coeffs.size();i++)
        {
            //< simple linear model :
            //< 
            //< y = sum(ai*xi)
            //< ai = coeffs[i]
            //< xi = data 'x[i]' value
            std::shared_ptr<Trait<double>> coeff = std::dynamic_pointer_cast<Trait<double>>(coeffs[i]);
            prediction += coeff->get_value() * data->get_x()[i];
        }

        // if it's test, update weigths
        if(data->is_type(CA_DATA_TEST))
        {
            // TODO : change weigths
        }

        // if it's validation, try to predict
        if(data->is_type(CA_DATA_VALIDATION))
        {
            sp_classical_data_validation data_validation = std::dynamic_pointer_cast<ClassicalValidationData>(data);
            data_validation->set_f_x_predict(prediction);
        }
    }
}
// -------------------- CLASSICAL ALGOS - GENES - SINGLE

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Constants.hpp"
#include "../../Utils/Functions.hpp"
#include "../../Models/ClassicalAlgos/Biology/Gene/GeneGaussian.hpp"

namespace ut_ca 
{
    /**
     * @brief test all kinds of genes
    */
    bool launch_tests_classical_algos_genes_single()
    {
        bool launch_tests_classical_algos_genes_single_gaussian(void);

        bool is_passed = true;

        std::cout << "Classical algos - genes - single : " << std::endl;

        is_passed &= launch_tests_classical_algos_genes_single_gaussian();

        std::cout << "Classical algos - genes - single : ";
        passed_print(is_passed);

        return is_passed;
    }

    bool launch_tests_classical_algos_genes_single_gaussian()
    {

        bool is_passed = true;

        double mean_test = 100;
        double std_dev_test = 3;

        int nb_loops = 200;
        double result_tolerance = 0.01;

        std::shared_ptr<Trait<double>> trait_test = std::make_shared<Trait<double>>(0);
        sp_gene_gauss gene_test = std::make_shared<GeneGaussian>(mean_test, std_dev_test, trait_test);

        double mean = 0;
        double std_dev = 0;
        double temp;
        for(int i=0;i<nb_loops;i++)
        {
            gene_test->drive();

            temp = trait_test->get_value();
            mean += temp;
            std_dev += temp*temp;
        } 

        mean /= nb_loops;
        std_dev = std_dev*std_dev/nb_loops - mean*mean;

        if(abs(mean-mean_test)/mean_test > result_tolerance
            || abs(std_dev-std_dev_test)/std_dev_test > result_tolerance)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Classical algos - genes - single - gaussian : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
}
#pragma once

#include "../Utils/Log/logpaths.hpp"

#include <iostream>
#include "../Framework.hpp"

//---------- constants

extern const int NB_SUFFIXES_EXPERIMENT_1;
extern std::string LOG_SUFFIXES_EXPERIMENT_1[];

//---------- functions

extern int experiment_1();

/**
 * @brief Linear model dimension 1
 * 
 * @param[out] framework framework of the experience
*/
extern int experiment_1_1(Framework* framework);

/**
 * @brief Linear model dimension n
 * 
 * @param[out] framework framework of the experience
 * @param[in] dim dimension of the linear model
*/
extern int experiment_1_2(Framework* framework, int dim);

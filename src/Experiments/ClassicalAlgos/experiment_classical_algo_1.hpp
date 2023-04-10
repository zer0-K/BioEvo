#pragma once

#include "../../Utils/Log/logpaths.hpp"

#include <iostream>
#include "../../Framework.hpp"

//---------- constants

extern const int NB_SUFFIXES_EXPERIMENT_1;
extern std::string LOG_SUFFIXES_EXPERIMENT_1[];

//---------- functions

extern int experiment_1();

/**
 * @brief affine functions
 * 
 * @param[in] framework framework of the experience
*/
extern int experiment_1_1(Framework* framework);

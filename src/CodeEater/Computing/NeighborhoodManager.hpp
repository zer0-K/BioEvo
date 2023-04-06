#pragma once

#include "../../PreprocessingDefinitions.hpp"
#include "../ConstantsCodeEater.hpp"
#include "../CodeEaters/CodeEater.hpp"

class NeighborhoodManager
{
    int width;  ///< width of the UniverseCodeEater
    int height; ///< height of the UniverseCodeEater

public:
    /**
     * @brief Constructor
     * 
     * @param width width of the UniverseCodeEater
     * @param height height of the UniverseCodeEater
    */
    NeighborhoodManager(int width, int height);

    //-------------------- general methods

    /**
     * @brief general method to get the neighbors
     * will call similar methods, correspoding to particular neighborhood
     * 
     * @param[in] code_eaters code eaters
     * @param[in] r row number to get the neighborhood of
     * @param[in] c column number to get the neighborhood of
     * @param[in] neighborhood_type type of neighborhood (Von Neumann, Moore, line,...)
     * 
     * @return the neighborhood of the code eater at (r;c)
    */
    CodeEater** getNeighborhood(CodeEater*** code_eaters, int r, int c, NeighborHoodType neighborhood_type);

    /**
     * @brief get the absolute coordinates (in the UniverseCodeEater) corresponding to the index for the given neighborhood at the 
     * absolute coordinantes
     * will call similar methods, correspoding to particular neighborhood
     * 
     * @param[in] r row of the code eater from which we have taken the neighborhood of
     * @param[in] c column of the code eater from which we have taken the neighborhood of
     * @param[in] index relative index of the missing code eater; i.e. index in the neighborhood
     * @param[in] neighborhood_type neighborhood type, so that we can deduce the absolute coordinates from the relative index
     * @param[out] r_replacement absolute row (i.e. row in the UniverseCodeEater) where to replace a code eater, corresponding to the relative index
     * @param[out] c_replacement absolute column (i.e. column in the UniverseCodeEater) where to replace a code eater, corresponding to the relative index
    */
    void getAbsoluteReplacementCoordinates(int r, int c, int index, NeighborHoodType neighborhood_type, 
        int& r_replacement, int& c_replacement);

    /**
     * @brief get the index correponding to the given direction in the neighborhood type
     * 
     * @param neighborhood_type type of neighborhood
     * @param direction direction, it corresponds to an index in the neighborhood type
    */
    int getNeighborIndexFromDirection(NeighborHoodType neighborhood_type, EatDirection direction);


    //-------------------- more particular methods

    //---------- Von Neumann

    /**
     * @brief get the Von Neumann neighbors
     * 
     * @param[in] code_eaters code eaters
     * @param[in] r row number to get the neighborhood of
     * @param[in] c column number to get the neighborhood of
     * 
     * @return the Von Neumann neighborhood of the code eater at (r;c)
    */
    CodeEater** getVonNeumannNeighborhood(CodeEater*** code_eaters, int r, int c);

    /**
     * @brief get the absolute coordinates (in the UniverseCodeEater) corresponding to the index for the given Von Neumann neighborhood at the 
     * absolute coordinantes
     * 
     * @param[in] r row of the code eater from which we have taken the neighborhood of
     * @param[in] c column of the code eater from which we have taken the neighborhood of
     * @param[in] index relative index of the missing code eater; i.e. index in the neighborhood
     * @param[out] r_replacement absolute row (i.e. row in the UniverseCodeEater) where to replace a code eater, corresponding to the relative index
     * @param[out] c_replacement absolute column (i.e. column in the UniverseCodeEater) where to replace a code eater, corresponding to the relative index
    */
    void getAbsoluteReplacementCoordinates_VonNeumann(int r, int c, int index, 
        int& r_replacement, int& c_replacement);
};
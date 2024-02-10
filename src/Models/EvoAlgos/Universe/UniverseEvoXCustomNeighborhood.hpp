#pragma once

#include "UniverseEvoAlgos.hpp"

enum neighborhoodType {
    VON_NEUMANN,
    MOORE
};

/**
 * @brief a 2-dimensional space for evoX algos
 */
class UniverseEvoXCustomNeighborhood : public UniverseEvoAlgos
{
protected:
    int neighborhood_size;
    int current_exec_pos;

    int nb_cols;
    int nb_rows;

    /**
     * @brief get absolute pos of a cell in the neighborhood of another cell
     * 
     * @param pos position of cell
     * @param pos_neighborhood position in the neighorhood of the cell
     * @param size of the neighborhood
     * @param nb_rows number of rows of the universe
     * @param nb_cols number of cols of the universe
     *
     * @return absolute position of the cell, -1 if outside of the universe
     */
    std::function<int(int, int, int, int, int)> get_pos_from_neighborhood_coords;

public:
    /// @brief constructor
    UniverseEvoXCustomNeighborhood(int nbrows, int nbcols, std::string name);

    using UniverseEvoAlgos::UniverseEvoAlgos;

    /// @brief constructor
    UniverseEvoXCustomNeighborhood(int nbrows, int nbcols, std::vector<sp_evox> algos, 
        std::vector<std::array<int, 2>> positions, std::string name);

    /// @see Universe::exec
    void exec() override;

    //---------- X86 IO

    /**
     * @brief check in the neighborhood if a place is empty
     *
     * @param[in] pos position to check
     * @return true if given place is empty
     */
    bool is_empty(int pos) override;

    /**
     * @brief get free genes at given pos in the neighborhood
     *
     * @param[in] pos position
     * @return genes (empty if no free genes at given pos)
     */
    std::vector<int> get_freegenes_at(int pos) override;

    /**
     * @brief write free genes at given pos
     *
     * @param[in] pos position to write
     * @param[in] vals int sequence to write
     * @return true if write was successful
     */
    bool write_freegenes_at(int pos, std::vector<int> vals) override;

    /**
     * @brief link universe functions to x86 individuals
     */
    void link_universe_functions_to_individuals(neighborhoodType nt, int params[]);
};

typedef std::shared_ptr<UniverseEvoXCustomNeighborhood> sp_univ_evo_algos_custom;
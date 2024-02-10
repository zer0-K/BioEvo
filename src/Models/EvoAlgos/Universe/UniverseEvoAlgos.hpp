#pragma once

#include "../../../Universe/Universe.hpp"
#include "../X86Algo/X86Algo.hpp"
#include "../X86Algo/EvoX.hpp"

class UniverseEvoAlgos : public Universe
{
protected:


public:
    /// @brief constructor
    UniverseEvoAlgos(int size, std::string name);

    using Universe::Universe;

    /// @brief constructor
    UniverseEvoAlgos(std::vector<sp_x86algo> algos, std::string name);
    /// @brief constructor
    UniverseEvoAlgos(std::vector<sp_evox> algos, std::string name);

    /// @see Universe::exec
    void exec() override;

    //---------- X86 IO

    /**
     * @brief check if a place is empty
     *
     * @param[in] pos position to check
     * @return true if given place is empty
     */
    virtual bool is_empty(int pos);

    /**
     * @brief get free genes at given pos
     *
     * @param[in] pos position
     * @return genes (empty if no free genes at given pos)
     */
    virtual std::vector<int> get_freegenes_at(int pos);

    /**
     * @brief write free genes at given pos
     *
     * @param[in] pos position to write
     * @param[in] vals int sequence to write
     * @return true if write was successful
     */
    virtual bool write_freegenes_at(int pos, std::vector<int> vals);

    /**
     * @brief link universe functions to x86 individuals
     */
    virtual void link_universe_functions_to_individuals();

};

typedef std::shared_ptr<UniverseEvoAlgos> sp_univ_evo_algos;
#pragma once

#include "../../../Universe/Universe.hpp"
#include "../X86Algo/X86Algo.hpp"
#include "../X86Algo/EvoX.hpp"

class UniverseEvoAlgos : public Universe
{
protected:
    /**
     * @brief create flow if entity to connect matches the output_flow requirement
     *
     * @param[in] output_flow output flow, containing the requirements
     * @param[in] entity_to_connect entity to connect
     *
     * @return true if the entity to connect matches the requirements
     */
    bool do_connect_flows(std::vector<std::array<int,2>> output_flow, sp_x86algo entity_to_connect);

public:
    /// @brief constructor
    UniverseEvoAlgos(int size, std::string name);

    /// @brief constructor
    UniverseEvoAlgos(std::vector<sp_x86algo> algos, std::string name);
    UniverseEvoAlgos(std::vector<sp_evox> algos, std::string name);

    /// @see Universe::exec
    void exec() override;

    /// @see Universe::update_flows
    void update_flows(sp_entity entity) override;
};

typedef std::shared_ptr<UniverseEvoAlgos> sp_univ_evo_algos;
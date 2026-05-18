#pragma once

#include "XASMAlgo.hpp"

/**
 * @brief XASM-based evolutionary algorithm with self-modifiable body
*/
class EvoX : public XASMAlgo
{
protected:
    std::vector<int> body;

public:
    using XASMAlgo::XASMAlgo;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
    
    void exec_instruction_molecule(int instr, int arg1_depth, int arg2_depth, int arg3_depth,
        int arg1, int arg2, int arg3);

    /**
     * @brief create the executable code from the body (XASM molecules)
    */
    void create_code_from_body();

    /**
     * @brief modify (or not a phenotypic marker once it's been used)
    */
    void post_process_marker(int marker_pos);

    // setters
    void set_body(std::vector<int> body);

    // getters
    std::vector<int> get_body();

    // utils
    void print_body();
    std::string body_to_evox_string() const;
};

typedef std::shared_ptr<EvoX> sp_evox;

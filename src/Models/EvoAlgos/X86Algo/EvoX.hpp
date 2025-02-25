#pragma once

#include "X86Algo.hpp"

/**
 * @brief x86_like evolutionary algorithm
 * 
 * Small computer close to x86 architecture
*/
class EvoX : public X86Algo
{
protected:
    std::vector<int> phenotypic_body;

public:
    using X86Algo::X86Algo;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
    
    void exec_instruction_molecule(int instr, int is_addr1, int is_addr2, int is_addr3, 
    int addr1, int addr2, int addr3);

    /**
     * @brief create the executable code from the body (XASM molecules)
    */
    void create_code_from_phenotypic_body();

    /**
     * @brief modify (or not a phenotypic marker once it's been used)
    */
    void post_process_marker(int marker_pos);

    // setters
    void set_phenotypic_body(std::vector<int> phenotypic_body);

    // getters
    std::vector<int> get_phenotypic_body();

    // utils
    void print_phenotypic_body();
};

typedef std::shared_ptr<EvoX> sp_evox;

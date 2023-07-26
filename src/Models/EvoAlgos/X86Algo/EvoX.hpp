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
    std::vector<int> genes;

public:
    using X86Algo::X86Algo;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
    
    void exec_instruction_meta(int instr, int addr1, int addr2);

    /**
     * @brief create the code from the genes
    */
    void create_code_from_genes();

    // setters
    void set_genes(std::vector<int> genes);

    // getters
    std::vector<int> get_genes();
};

typedef std::shared_ptr<EvoX> sp_evox;

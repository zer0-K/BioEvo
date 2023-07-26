#pragma once

#include <array>

#include "../../../Entities/Entity.hpp"

/**
 * @brief x86-like base algorithm
 * 
 * Small computer close to x86 architecture
*/
class X86Algo : public Entity
{
protected:
    /**
     * @brief data of the individual
     * 
     * The addresses are integers between 0 and 2^n-1, where n is the size of the data memory
     * Everything is treated as integers here
    */
    std::vector<int> data;

    // inputs and outputs of the program
    std::vector<int> input;
    std::vector<int> output;

    /**
     * @brief code of the individual
     * 
     * This is the evolutionary part.
     * A code instruction is like INSTR ADDR1 ADDR2
    */
    std::vector<std::array<int, 3>> code;


    /**
     * @brief program counter
     * 
     * Initialized at 0, incremented each time a line is executed
    */
    int program_counter;

public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    void exec_instruction(int instr, int addr1, int addr2);
    void exec_instruction_basic(int instr, int addr1, int addr2);
    virtual void exec_instruction_meta(int instr, int addr1, int addr2) {};

    // setters
    void set_data_size(int n);
    void set_input_size(int n);
    void set_output_size(int n);

    void set_code(std::vector<std::array<int, 3>> code, int place_at);
    void set_input(std::vector<int> in);

    // getters
    std::vector<std::array<int, 3>> get_code();
    std::vector<int> get_output();
};

typedef std::shared_ptr<X86Algo> sp_x86algo;

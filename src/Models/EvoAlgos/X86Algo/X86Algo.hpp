#pragma once

#include <array>

#include "../../../Utils/Constants.hpp"

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
    std::vector<std::vector<int>> data_debug;

    // inputs and outputs of the program
    std::vector<int> input;
    std::vector<int> output;

    /**
     * @brief code of the individual
     * 
     * This is the evolutionary part.
     * A code instruction is like INSTR ISADDR1 ISADDR2 arg1 arg2
    */
    std::vector<std::array<int,SIZE_INSTR>> code;


    /**
     * @brief program counter
     * 
     * Initialized at 0, incremented each time a line is executed
    */
    int program_counter;

    //---------- other
    int unif_lower_bound = 0;
    int unif_upper_bound = 1;

public:
    bool debug;
    int data_debug_window;

    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    /**
     * @brief Execute an assembly instruction
     * 
     * @param[in] instr instruction to execute
     * @param[in] is_addr1 true if the value of the first arg of the instruction is to be found at given address
     * @param[in] is_addr2 true if the value of the second arg of the instruction is to be found at given address
     * @param[in] is_addr3 true if the value of the third arg of the instruction is to be found at given address
     * @param[in] arg1 value/address of the first argument of the instruction
     * @param[in] arg2 value/address of the second argument of the instruction
     * @param[in] arg3 value/address of the third argument of the instruction
    */
    void exec_instruction(int instr, bool is_addr1, bool is_addr2, bool is_addr3, 
        int arg1, int arg2, int arg3);

    /// @brief Basic instructions @see exec_instruction
    void exec_instruction_basic(int instr, bool is_addr1, bool is_addr2, bool is_addr3, 
        int arg1, int arg2, int arg3);

    /// @brief Genetic instructions @see exec_instruction
    virtual void exec_instruction_gene(int instr, bool is_addr1, bool is_addr2, bool is_addr3, 
        int arg1, int arg2, int arg3) {};

    /**
     * @brief Get the values at given addresses if they are so
     * 
     * For example, if is_addr1 is true, arg1 will refer to the value at the address arg1
     * and if is_addr1 is false it corresponds to an "absolute" value (i.e. not a value at an address)
     * 
     * @param[out] is_valid true if the given address are valid
     * @param[in] is_addr1 true if the value of the first arg of the instruction is to be found at given address
     * @param[in] is_addr2 true if the value of the second arg of the instruction is to be found at given address
     * @param[in] is_addr3 true if the value of the third arg of the instruction is to be found at given address
     * @param[in] arg1 value/address of the first argument of the instruction
     * @param[in] arg2 value/address of the second argument of the instruction
     * @param[in] arg3 value/address of the third argument of the instruction
    */
    std::array<int,SIZE_INSTR> get_vals(bool &is_valid, bool is_addr1, bool is_addr2, bool is_addr3, 
        int arg1, int arg2, int arg3);

    // setters
    void set_data_size(int n);
    void set_input_size(int n);
    void set_output_size(int n);

    void reset_code_to_size(int code_size);
    void set_code(std::vector<std::array<int,SIZE_INSTR>> code, int place_at);
    void set_input(std::vector<int> in);

    void reset_data();

    // getters
    std::vector<std::array<int,SIZE_INSTR>> get_code();
    std::vector<int> get_output();

    // utils
    void print_data_debug();
};

typedef std::shared_ptr<X86Algo> sp_x86algo;

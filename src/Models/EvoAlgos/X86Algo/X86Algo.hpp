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
     * @brief values for input flow 
     * first value is a key, second is a value (corresponding to an ID)
     */
    std::vector<std::array<int,2>> input_flows;

    /**
     * @brief values for the output flow 
     * first value is a key, second is a value (corresponding to an ID)
     */
    std::vector<std::array<int,2>> output_flows;

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
    int instr_counter;  ///< count the number of instructions executed

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
     * @param[in] addr1_order 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] addr2_order 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] addr3_order 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] arg1 value/address of the first argument of the instruction
     * @param[in] arg2 value/address of the second argument of the instruction
     * @param[in] arg3 value/address of the third argument of the instruction
    */
    void exec_instruction(int instr, int addr1_order, int addr2_order, int addr3_order, 
        int arg1, int arg2, int arg3);

    /// @brief Basic instructions @see exec_instruction
    void exec_instruction_basic(int instr, int addr1_order, int addr2_order, int addr3_order, 
        int arg1, int arg2, int arg3);

    /// @brief Genetic instructions @see exec_instruction
    virtual void exec_instruction_gene(int instr, int addr1_order, int addr2_order, int addr3_order, 
        int arg1, int arg2, int arg3) {};

    /**
     * @brief Get the addresses at given args
     * 
     * For example, if addr1_order is 0, arg1 will refer to its own value, 
     * if addr1_order is 1, arg1 will refer to data at arg1, if addr1_order is
     * 2, arg1 will refer to data at data at arg1,...
     * 
     * @param[out] is_valid true if the given address are valid
     * @param[in] addr1_order 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] addr2_order 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] addr3_order 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] arg1 value/address of the first argument of the instruction
     * @param[in] arg2 value/address of the second argument of the instruction
     * @param[in] arg3 value/address of the third argument of the instruction
    */
    std::array<int,SIZE_INSTR> get_addrs(bool &is_valid, int addr1_order, int addr2_order, int addr3_order, 
        int arg1, int arg2, int arg3);

    // setters
    void set_data_size(int n);
    void set_input_size(int n);
    void set_output_size(int n);

    void reset_code_to_size(int code_size);
    void set_code(std::vector<std::array<int,SIZE_INSTR>> code, int place_at);
    void reset_code(std::vector<std::array<int,SIZE_INSTR>> code);
    void set_input(std::vector<int> in);

    void reset_data();

    // getters
    std::vector<std::array<int,SIZE_INSTR>> get_code();
    std::vector<int> get_output();
    std::vector<std::array<int,2>> get_input_flows();
    std::vector<std::array<int,2>> get_output_flows();

    // utils
    void print_data_debug();
};

typedef std::shared_ptr<X86Algo> sp_x86algo;

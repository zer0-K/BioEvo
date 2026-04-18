#pragma once

#include <array>
#include <functional>

#include "../../../Utils/Constants.hpp"

#include "../../../Entities/Entity.hpp"

/**
 * @brief XASM virtual machine — base individual
 *
 * Integer-addressed memory, custom assembly language (XASM), program counter loop.
*/
class XASMAlgo : public Entity
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
    std::vector<int> input_x86;
    std::vector<int> output_x86;

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
    int max_nb_instr_exec;  ///< max number of instructions to execute


    //---------- external functions

    /**
     * @brief get universe size
     *
     * @return size of the universe
     */
    std::function<int()> get_universe_size;

    /**
     * @brief check if a place is empty
     *
     * @param int position to check
     * @return true if given place is empty
     */
    std::function<bool(int)> is_empty;

    /**
     * @brief get free molecules at given pos
     *
     * @param int position
     * @return phenotypic body (empty if no free molecules at given pos)
     */
    std::function<std::vector<int>(int)> get_free_molecules_at;

    /**
     * @brief get universe size
     *
     * @param int position to write
     * @param vector_int int sequence to write
     * @return true if write was successful
     */
    std::function<bool(int, std::vector<int>)> write_free_molecules_at;

    /**
     * @brief size of the neighborhood of the current individual
     */
    int neighborhood_size;


    //---------- other

    int unif_lower_bound = 0;
    int unif_upper_bound = 1;

public:
    bool debug;
    bool debug_ribosome;
    int data_debug_window;

    using Entity::Entity;

    void init() override;
    /// @brief set the external functions (get universe size, read, write,...)
    void init_external_functions(std::function<int()> get_universe_size,
        std::function<bool(int)> is_empty, std::function<std::vector<int>(int)> get_free_molecules_at,
        std::function<bool(int, std::vector<int>)> write_free_molecules_at);


    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
    void exec() override; // ! this one copies Entity::input and Entity::output

    /**
     * @brief Execute an assembly instruction
     * 
     * @param[in] instr instruction to execute
     * @param[in] arg1_depth 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] arg2_depth 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] arg3_depth 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] arg1 value/address of the first argument of the instruction
     * @param[in] arg2 value/address of the second argument of the instruction
     * @param[in] arg3 value/address of the third argument of the instruction
    */
    void exec_instruction(int instr, int arg1_depth, int arg2_depth, int arg3_depth, 
        int arg1, int arg2, int arg3);

    /// @brief Basic instructions @see exec_instruction
    void exec_instruction_basic(int instr, int arg1_depth, int arg2_depth, int arg3_depth, 
        int arg1, int arg2, int arg3);

    /// @brief Genetic instructions @see exec_instruction
    virtual void exec_instruction_molecule(int instr, int arg1_depth, int arg2_depth, int arg3_depth, 
        int arg1, int arg2, int arg3) {};

    /**
     * @brief Get the addresses at given args
     * 
     * For example, if arg1_depth is 0, arg1 will refer to its own value, 
     * if arg1_depth is 1, arg1 will refer to data at arg1, if arg1_depth is
     * 2, arg1 will refer to data at data at arg1,...
     * 
     * @param[out] is_valid true if the given address are valid
     * @param[in] arg1_depth 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] arg2_depth 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] arg3_depth 0 if absolute arg, 1 if arg is value at addr given in arg,...
     * @param[in] arg1 value/address of the first argument of the instruction
     * @param[in] arg2 value/address of the second argument of the instruction
     * @param[in] arg3 value/address of the third argument of the instruction
    */
    std::array<int,SIZE_INSTR> get_addrs(bool &is_valid, int arg1_depth, int arg2_depth, int arg3_depth, 
        int arg1, int arg2, int arg3);

    // setters
    void set_max_nb_instr_exec(int n);

    void set_data_size(int n);
    void set_input_size(int n);
    void set_output_size(int n);

    void reset_code_to_size(int code_size);
    void set_code(std::vector<std::array<int,SIZE_INSTR>> code, int place_at);
    void reset_code(std::vector<std::array<int,SIZE_INSTR>> code);
    void set_input(std::vector<int> in);

    void set_data_at(int pos, int val);
    void reset_data();

    void set_neighborhood_size(int size);

    // getters
    std::vector<std::array<int,SIZE_INSTR>> get_code();
    std::vector<int> get_output();
    std::vector<int> get_data();
    int get_neighborhood_size();

    // utils
    void print_data_debug();
};

typedef std::shared_ptr<XASMAlgo> sp_xasmalgo;

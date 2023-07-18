#include "X86Algo.hpp"

#include "../../../Utils/Constants.hpp"
#include "InstructionMapping.hpp"

void X86Algo::init()
{
    type = X86_ALGO;
    add_type(X86_ALGO);

    program_counter = 0;

    code = std::vector<std::array<int, 3>>(DEFAULT_X86_CODE_SIZE);
    set_data_size(DEFAULT_X86_DATA_SIZE);
    set_input_size(1);
    set_output_size(1);
}

std::vector<sp_entity> X86Algo::exec(std::vector<sp_entity> entries)
{
    while(program_counter>=0 && program_counter<code.size())
    {
        std::array<int,3> code_line = code.at(program_counter);

        exec_instruction(code_line[0], code_line[1], code_line[2]);

        program_counter++;
    }

    return entries;
}

void X86Algo::exec_instruction(int instr, int addr1, int addr2)
{
    switch(instr)
    {
        case instruction::XXX:
            // does nothing
            break;

        case instruction::MOV:
            // moves the second address into the first one
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr2];
            }
            break;

        case instruction::MOVIN:
            // moves the input data into the first address
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<input.size())
            {
                data[addr1] = input[addr2];
            }
            break;

        case instruction::MOVOUT:
            // moves the input data into the first address
            if(addr1>=0 && addr2>=0
                && addr1<output.size() && addr2<data.size())
            {
                output[addr1] = data[addr2];
            }
            break;

        default:
            // does nothing
            break;
    }
}

void X86Algo::set_data_size(int n)
{
    data = std::vector<int>(n);
}

void X86Algo::set_input_size(int n)
{
    input = std::vector<int>(n);
}

void X86Algo::set_output_size(int n)
{
    output = std::vector<int>(n);
}

void X86Algo::set_code(std::vector<std::array<int, 3>> code, int place_at)
{
    if(place_at>=0 && place_at+code.size()<this->code.size())
    {
        for(int i=0;i<code.size();i++)
        {
            this->code[place_at + i][0] = code[i][0];
            this->code[place_at + i][1] = code[i][1];
            this->code[place_at + i][2] = code[i][2];
        }
    }
}

void X86Algo::set_input(std::vector<int> in)
{
    for(int i=0; i<std::min(in.size(), input.size());i++)
    {
        input[i] = in[i];
    }
}

std::vector<int> X86Algo::get_output()
{
    return output;
}
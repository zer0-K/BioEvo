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

    debug = false;
    data_debug_window = 6;
    data_debug = std::vector<std::vector<int>>(0);
}

std::vector<sp_entity> X86Algo::exec(std::vector<sp_entity> entries)
{
    // execution starts at pos 0
    program_counter = 0;

    // to prevent infinite loops
    int instr_counter = 0;

    if(debug)
    {
        data_debug.push_back(data);
    }

    while(program_counter>=0 && program_counter<code.size()
        && instr_counter < 100000)
    {
        std::array<int,3> code_line = code.at(program_counter);

        exec_instruction(code_line[0], code_line[1], code_line[2]);

        program_counter++;
        instr_counter++;

        if(debug)
        {
            data_debug.push_back(data);
        }
    }

    return entries;
}

void X86Algo::exec_instruction(int instr, int addr1, int addr2)
{
    exec_instruction_basic(instr, addr1, addr2);
    exec_instruction_meta(instr, addr1, addr2);
}

void X86Algo::exec_instruction_basic(int instr, int addr1, int addr2)
{
    switch(instr)
    {
        case instruction::XXX:
            // does nothing
            break;

        case instruction::MOV:
            // moves data at second address into the first one
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr2];
                data[addr2] = 0;
            }
            break;

        case instruction::CPY:
            // copy data at second address into first one
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr2];
            }
            break;

        case instruction::CPYIN:
            // copies the input into memory
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<input.size())
            {
                data[addr1] = input[addr2];
            }
            break;

        case instruction::CPYOUT:
            // copies data to output
            if(addr1>=0 && addr2>=0
                && addr1<output.size() && addr2<data.size())
            {
                output[addr1] = data[addr2];
            }
            break;

        case instruction::INC:
            // increment data at second address into first one
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr2] + 1;
            }
            break;

         case instruction::DEC:
            // decrement data at second address into first one
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr2] - 1;
            }
            break;

        case instruction::ADD:
            // add the data in the two addresses into the first one
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr1] + data[addr2];
            }
            break;

        case instruction::SUB:
            // substract the data in the two addresses into the first one
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr1] - data[addr2];
            }
            break;

        case instruction::MUL:
            // multiply the data in the two addresses into the first one
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr1] * data[addr2];
            }
            break;

        case instruction::DIV:
            // divide the data in the two addresses into the first one
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr1] / data[addr2];
            }
            break;

        case instruction::CMP:
            // compare data 1 if addr1<addr2, -1 if > and 0 if =
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size())
            {
                data[addr1] = data[addr1] == data[addr2] ? 0 :
                                ( data[addr1] < data[addr2] ? 1 : -1 );
            }
            break;


        case instruction::JMP:
            // set prog ptr to given position at index of second address
            // set current prog ptr in first address
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size()
                && data[addr2]>=0 && data[addr2]<code.size())
            {                
                int temp = program_counter;

                // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                program_counter = data[addr2] - 1;

                // ! prog ptr BEFORE being incremented !
                data[addr1] = temp;
            }
            break;


        case instruction::JRA:
            // shift positively the prog ptr according to data at second address
            // set current prog ptr in first address
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size()
                && program_counter + data[addr2] >= 0 
                && program_counter + data[addr2] < code.size())
            {
                int temp = program_counter;
                
                // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                program_counter += data[addr2] - 1;

                // ! prog ptr BEFORE being incremented !
                data[addr1] = temp;
            }
            break;

        case instruction::JRS:
            // shift negatively the prog ptr according to data at second address
            // set current prog ptr in first address
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size()
                && program_counter - data[addr2] >= 0 
                && program_counter - data[addr2] < code.size())
            {
                int temp = program_counter;
                
                // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                program_counter = (program_counter - data[addr2]) - 1;

                // ! prog ptr BEFORE being incremented !
                data[addr1] = temp;
            }
            break;

        case instruction::JRE:
            // add val at addr1 to prog ptr if at addr2 is equal to 0
            // does not set old prog ptr
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size()
                && data[addr1]>=0 && data[addr1]<code.size()
                && program_counter + data[addr1] >= 0 
                && program_counter + data[addr1] < code.size())
            {
                if(data[addr2] == 0)
                {
                    // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                    program_counter += data[addr1] - 1;
                }
            }
            break;

        case instruction::JE:
            // jump at address at addr1 if data at addr2 is equal to 0
            // does not set old prog ptr
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size()
                && data[addr1]>=0 && data[addr1]<code.size())
            {
                if(data[addr2] == 0)
                {
                    // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                    program_counter = data[addr1] - 1;
                }
            }
            break;


        case instruction::JL:
            // jump at address at addr1 if data at addr2 is < 0
            // does not set old prog ptr
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size()
                && data[addr1]>=0 && data[addr1]<code.size())
            {
                if(data[addr2] < 0)
                {
                    // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                    program_counter = data[addr1] - 1;
               }
            }
            break;


        case instruction::JG:
            // jump at address at addr1 if data at addr2 is > 0
            // does not set old prog ptr
            if(addr1>=0 && addr2>=0
                && addr1<data.size() && addr2<data.size()
                && data[addr1]>=0 && data[addr1]<code.size())
            {
                if(data[addr2] > 0)
                {
                    // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                    program_counter = data[addr1] - 1;
               }
            }
            break;

        case instruction::HALT:
            // set prog ptr at end of code ('-1' because prog ptr is incremented at end of instr exec)
            program_counter = code.size() - 1;
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

//----- getters

std::vector<std::array<int, 3>> X86Algo::get_code()
{
    return code;
}

std::vector<int> X86Algo::get_output()
{
    return output;
}

// utils

void X86Algo::print_data_debug()
{
    if(debug)
    {
        std::cout << std::endl << std::endl;
        std::cout << "******************** debug x86 algo ********************";
        std::cout << std::endl << std::endl;

        std::cout << "Input : " << std::endl;

        for(int i=0; i<input.size();i++)
        {
            std::cout << input[i] << "\t";
        }

        std::cout << std::endl << std::endl;

        std::cout << "Data accross execution : " << std::endl;

        for(int i=0; i<data_debug.size();i++)
        {
            std::cout << i << " : \t";

            for(int j=0; j<data_debug_window;j++)
            {
                std::cout << data_debug[i][j] << "\t";
            }

            std::cout << std::endl;
        }

        std::cout << std::endl << std::endl;

        std::cout << "Output : " << std::endl;

        for(int i=0; i<output.size();i++)
        {
            std::cout << output[i] << "\t";
        }

        std::cout << std::endl << std::endl;
    }
}
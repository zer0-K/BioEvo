#include "X86Algo.hpp"

#include "../../../Utils/Maths/RandomGen.hpp"
#include "InstructionMapping.hpp"

void X86Algo::init()
{
    type = X86_ALGO;
    add_type(X86_ALGO);

    program_counter = 0;

    code = std::vector<std::array<int,SIZE_INSTR>>(DEFAULT_X86_CODE_SIZE);
    set_data_size(DEFAULT_X86_DATA_SIZE);
    set_input_size(1);
    set_output_size(1);

    debug = false;
    data_debug_window = 10;
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
        && instr_counter < 20000)
    {
        std::array<int,SIZE_INSTR> code_line = code.at(program_counter);

        exec_instruction(code_line[0], code_line[1], code_line[2], code_line[3], code_line[4], code_line[5], code_line[6]);

        program_counter++;
        instr_counter++;

        if(debug)
        {
            data_debug.push_back(data);
        }
    }

    return entries;
}

void X86Algo::exec_instruction(int instr, int addr1_order, int addr2_order, int addr3_order, 
    int arg1, int arg2, int arg3)
{
    exec_instruction_basic(instr, addr1_order, addr2_order, addr3_order, arg1, arg2, arg3);
    exec_instruction_gene(instr, addr1_order, addr2_order, addr3_order, arg1, arg2, arg3);
}

void X86Algo::exec_instruction_basic(int instr, int addr1_order, int addr2_order, int addr3_order, 
    int arg1, int arg2, int arg3)
{
    bool is_valid = true;

    auto transformed_args = get_addrs(is_valid, addr1_order, addr2_order, addr3_order,
        arg1, arg2, arg3);

    if(!is_valid)
        return;

    int arg1_ = transformed_args[0];
    int arg2_ = transformed_args[1];
    int arg3_ = transformed_args[2];

    int destination = arg1_;
    int destination_order = addr1_order;
    int source = arg2_;
    int source_order = addr2_order;

    switch(instr)
    {
        case instruction::XXX:
            // does nothing
            break;

        case instruction::MOV:
            // move
            // moves data at source into destination

            if(destination_order>0 && destination>=0 && destination<data.size())
            {
                // if source order is 0, 'mov' is actually a 'set'
                if(source_order==0)
                {
                    data[destination] = source;
                }
                else if(source>=0 && source<data.size())
                {
                    data[destination] = data[source];
                    data[source] = 0;
                }
            }

            break;

        case instruction::CPY:
            // copy
            // copy data at second adress into first one

            if(destination_order>0 && destination>=0 && destination<data.size())
            {
                if(source_order==0)
                {
                    data[destination] = source;
                }
                else if(source>=0 && source<data.size())
                {
                    data[destination] = data[source];
                }
            }

            break;

        case instruction::CPYIN:
            // copy input
            // copies the input into memory

            if(destination_order>0 && destination>=0 && destination<data.size())
            {
                // if source order is 0, 'CPYIN' is just a 'set'
                if(source_order==0)
                {
                    data[destination] = source;
                }
                else if(source>=0 && source<input.size())
                {
                    data[destination] = input[source];
                }
            }

           break;

        case instruction::CPYOUT:
            // copy output
            // copies data to output

            if(destination_order>0 && destination>=0 && destination<output.size())
            {
                if(source_order==0)
                {
                    output[destination] = source;
                }
                else if(source>=0 && source<data.size())
                {
                    output[destination] = data[source];
                }
            }


            break;

        case instruction::INC:
            // increment
            // increment data at second adress into first one

            if(destination_order>0 && destination>=0 && destination<data.size())
            {
                data[destination]++;
            }

           break;

        case instruction::DEC:
            // decrement
            // decrement data at second adress into first one

            if(destination_order>0 && destination>=0 && destination<data.size())
            {
                data[destination]--;
            }

           break;

        case instruction::ADD:
            // add
            // add the data in the two adresses into the first one

            if(destination_order>0 && destination>=0 && arg2_>=0 && arg3_>=0
                && destination<data.size() && arg2_<data.size() && arg3_<data.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0)
                    {
                        data[destination] = arg2_ + arg3_;
                    }
                    else if(arg3_>=0 && arg3_<data.size())
                    {
                        data[destination] = arg2_ + data[arg3_];
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0)
                    {
                        data[destination] = data[arg2_] + arg3_;
                    }
                    else if(arg3_>=0 && arg3<data.size())
                    {
                        data[destination] = data[arg2_] + data[arg3_];
                    }
                }
            }

            break;

        case instruction::SUB:
            // substract
            // substract the data in the two adresses into the first one

                if(addr2_order==0)
                {
                    if(addr3_order==0)
                    {
                        data[destination] = arg2_ - arg3_;
                    }
                    else if(arg3_>=0 && arg3_<data.size())
                    {
                        data[destination] = arg2_ - data[arg3_];
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0)
                    {
                        data[destination] = data[arg2_] - arg3_;
                    }
                    else if(arg3_>=0 && arg3<data.size())
                    {
                        data[destination] = data[arg2_] - data[arg3_];
                    }
                }

           break;

        case instruction::MUL:
            // multiply
            // multiply the data in the two adresses into the first one

                if(addr2_order==0)
                {
                    if(addr3_order==0)
                    {
                        data[destination] = arg2_ * arg3_;
                    }
                    else if(arg3_>=0 && arg3_<data.size())
                    {
                        data[destination] = arg2_ * data[arg3_];
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0)
                    {
                        data[destination] = data[arg2_] * arg3_;
                    }
                    else if(arg3_>=0 && arg3<data.size())
                    {
                        data[destination] = data[arg2_] * data[arg3_];
                    }
                }

           break;

        case instruction::DIV:
            // divide
            // divide the data in the two adresses into the first one

                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg3_!=0)
                    {
                        data[destination] = arg2_ / arg3_;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg3_]!=0)
                    {
                        data[destination] = arg2_ / data[arg3_];
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && arg3_!=0)
                    {
                        data[destination] = data[arg2_] / arg3_;
                    }
                    else if(arg3_>=0 && arg3<data.size() && data[arg3_]!=0)
                    {
                        data[destination] = data[arg2_] / data[arg3_];
                    }
                }

           break;

        case instruction::OPP:
            // opposite
            // take opposite of given number

            if(destination_order>0 && destination>=0 && destination<data.size())
            {
                data[destination] = -data[destination];
            }

           break;

        case instruction::CMP:
            // compare
            // compare data at arg2 and arg3, stores 0 in destination if they are equal,
            // 1 if data at arg2 < data at arg3, -1 otherwise

            if(destination_order>0 && destination>=0 && destination<data.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0)
                    {
                        data[destination] = arg2_== arg3_ ? 0 : (arg2_ < arg3_ ? 1 : -1);
                    }
                    else if(arg3_>=0 && arg3_<data.size())
                    {
                        data[destination] = arg2_== data[arg3_] ? 0 : (arg2_ < data[arg3_] ? 1 : -1);
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0)
                    {
                        data[destination] = data[arg2_]== arg3_ ? 0 : (data[arg2_] < arg3_ ? 1 : -1);
                    }
                    else if(arg3_>=0 && arg3_<data.size())
                    {
                        data[destination] = data[arg2_]== data[arg3_] ? 0 : (data[arg2_] < data[arg3_] ? 1 : -1);
                    }
                }
            }

            break;


        case instruction::CPYIS:
            // copy input size

            if(destination_order>0 && destination>=0 && destination<data.size() )
            {
                data[destination] = input.size();
            }

            break;

        case instruction::SETOS:
        {
            // set output size

            int new_out_size = -1;
            if(addr1_order==0)
            {
                new_out_size = arg1_;
            }
            else if(arg1_>=0 && arg1<data.size())
            {
                new_out_size = data[arg1_];
            }

            if(new_out_size >= 0 && new_out_size < MAX_OUTPUT_SIZE_X86)
            {
                if(output.size() > new_out_size)
                {
                    while(output.size()!=new_out_size)
                    {
                        output.pop_back();
                    }
                }

                if(output.size() < new_out_size)
                {
                    while(output.size() != new_out_size)
                    {
                        output.push_back(0);
                    }
                }
            }

            break;
        }

        case instruction::JMP:
            // jump
            // set prog ptr to given position 

            if(addr1_order==0 && arg1_>=0 && arg1_<code.size())
            {
                 // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                program_counter = arg1_ - 1;               
            }
            else if(arg1_>=0 && arg1_<data.size() 
                && data[arg1_]>=0 && data[arg1_]<code.size())
            {                
                // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                program_counter = data[arg1_] - 1;
            }

            break;


        case instruction::JRA:
            // relative jump (+ shift)
            // shift positively the prog ptr according to data at second adress

            if(addr1_order==0 
                && program_counter + arg1_ >= 0 
                && program_counter + arg1_<code.size() )
            {
                 // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                program_counter += arg1_ - 1;               
            }
            else if(arg1_>=0 && arg1_<data.size()
                && program_counter + data[arg1_] >= 0 
                && program_counter + data[arg1_] < code.size())
            {                
                // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                program_counter += data[arg1_] - 1;
            }

            break;

        case instruction::JRS:
            // relative jump (-shift)
            // shift negatively the prog ptr according to data at second adress

            if(addr1_order==0 
                && program_counter - arg1_ >= 0 
                && program_counter - arg1_<code.size() )
            {
                 // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                program_counter = (program_counter - arg1_) - 1;               
            }
            else if(arg1_>=0 && arg1_<data.size()
                && program_counter - data[arg1_] >= 0 
                && program_counter - data[arg1_] < code.size())
            {
                // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                program_counter = (program_counter - data[arg1_]) - 1;
            }
            break;

        case instruction::JE:
            // (absolute) jump if equal
            // set prog ptr if data at arg2 equals data at arg3

            if(destination_order==0 
                && destination >= 0 
                && destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_==arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_==data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]==arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]==data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && data[destination] >= 0 
                && data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_==arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_==data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]==arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]==data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
            }

            break;


        case instruction::JL:
            // jump if lower (strict)
            // jump at adress at destination if data at arg2 is < data at arg3

            if(destination_order==0 
                && destination >= 0 
                && destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_<arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_<data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]<arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]<data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && data[destination] >= 0 
                && data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_<arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_<data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]<arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]<data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
            }

            break;


        case instruction::JG:
            // jump if greater (strict)
            // jump at adress at destination if data at arg2 is > data at arg3

            if(destination_order==0 
                && destination >= 0 
                && destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_>arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_>data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]>arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]>data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && data[destination] >= 0 
                && data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_>arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_>data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]>arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]>data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
            }

            break;

        case instruction::JLE:
            // jump if lower or equal
            // jump at adress at destination if data at arg2 is <= data at arg3

            if(destination_order==0 
                && destination >= 0 
                && destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_<=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_<=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]<=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]<=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && data[destination] >= 0 
                && data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_<=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_<=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]<=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]<=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
            }

            break;



        case instruction::JGE:
            // jump if greater or equal
            // jump at adress at destination if data at arg2 is >= data at arg3

            if(destination_order==0 
                && destination >= 0 
                && destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_>=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_>=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]>=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]>=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && data[destination] >= 0 
                && data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_>=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_>=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]>=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]>=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter = data[destination] - 1;
                    }
                }
            }

            break;


        case instruction::JRE:
            // (absolute) jump if equal
            // set prog ptr if data at arg2 equals data at arg3

            if(destination_order==0 
                && program_counter+destination >= 0
                && program_counter+destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_==arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_==data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]==arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]==data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && program_counter+data[destination] >= 0 
                && program_counter+data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_==arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_==data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]==arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]==data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
            }

            break;


        case instruction::JRL:
            // jump if lower (strict)
            // jump at adress at destination if data at arg2 is < data at arg3

            if(destination_order==0
                && program_counter+destination >= 0
                && program_counter+destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_<arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_<data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]<arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]<data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && program_counter+data[destination] >= 0 
                && program_counter+data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_<arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_<data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]<arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]<data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
            }

            break;


        case instruction::JRG:
            // jump if greater (strict)
            // jump at adress at destination if data at arg2 is > data at arg3

            if(destination_order==0 
                && program_counter+destination >= 0 
                && program_counter+destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_>arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_>data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]>arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]>data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && program_counter+data[destination] >= 0 
                && program_counter+data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_>arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_>data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]>arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]>data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
            }

            break;

        case instruction::JRLE:
            // jump if lower or equal
            // jump at adress at destination if data at arg2 is <= data at arg3

            if(destination_order==0
                && program_counter+destination >= 0
                && program_counter+destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_<=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_<=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]<=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]<=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && program_counter+data[destination] >= 0 
                && program_counter+data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_<=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_<=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]<=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]<=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
            }

            break;



        case instruction::JRGE:
            // jump if greater or equal
            // jump at adress at destination if data at arg2 is >= data at arg3

            if(destination_order==0 
                && program_counter+destination >= 0 
                && program_counter+destination < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_>=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_>=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]>=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]>=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += destination - 1;
                    }
                }
            }
            else if(destination>=0 && destination<data.size() 
                && program_counter+data[destination] >= 0 
                && program_counter+data[destination] < code.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_>=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && arg2_>=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]>=arg3_)
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                    else if(arg3_>=0 && arg3_<data.size() && data[arg2_]>=data[arg3_])
                    {
                        // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
                        program_counter += data[destination] - 1;
                    }
                }
            }

            break;

        case instruction::BEG:
            // do nothing

            break;

        case instruction::HALT:
            // set prog ptr at end of code ('-1' because prog ptr is incremented at end of instr exec)

            program_counter = code.size() - 1;
            break;

        case instruction::RN:
            // nandom normal
            // normal law at first given adress

            if(destination_order>0 && destination>=0 && destination<data.size())
            {
                data[destination] = rand_gen::rand_normal(0,1);
            }

            break;

        case instruction::RUD:
            // random uniform double
            // uniform random double between 0 and 1 at first given adress

            if(destination_order>0 && destination>=0 && destination<data.size())
            {
                data[destination] = rand_gen::rand_double(0,1);
            }

            break;

        case instruction::RUI:
            // random uniform int
            // uniform random int between the bounds at arg2 and arg3

            if(destination_order>0 && destination>=0 && destination<data.size()
                && arg2_>=0 && arg2_<data.size()
                && arg3_>=0 && arg3_<data.size())
            {
                if(addr2_order==0)
                {
                    if(addr3_order==0 && arg2_<=arg3_)
                    {
                        data[destination] = rand_gen::rand_int(arg2_,arg3_);
                    }
                    else if(arg3>=0 && arg3_<data.size()
                        && arg2_<data[arg3_])
                    {
                        data[destination] = rand_gen::rand_int(arg2_,data[arg3_]);
                    }
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    if(addr3_order==0 && data[arg2_]<=arg3_)
                    {
                        data[destination] = rand_gen::rand_int(data[arg2_],arg3_);
                    }
                    else if(arg3>=0 && arg3_<data.size()
                        && data[arg2_]<data[arg3_])
                    {
                        data[destination] = rand_gen::rand_int(data[arg2_],data[arg3_]);
                    }
                }               
            }

            break;

        default:
            // does nothing
            break;
    }
}

std::array<int,SIZE_INSTR> X86Algo::get_addrs(bool &is_valid, int addr1_order, int addr2_order, int addr3_order, 
    int arg1, int arg2, int arg3)
{
    std::array<int,SIZE_INSTR> result = { arg1, arg2, arg3 };

    while(addr1_order>1)
    {
        is_valid = arg1>=0 && arg1<data.size();

        if(!is_valid)
            break;

        arg1 = data[arg1];
        result[0] = arg1;
        addr1_order--;
    }

    while(addr2_order>1)
    {
        is_valid = arg2>=0 && arg2<data.size();

        if(!is_valid)
            break;

        arg2 = data[arg2];
        result[1] = arg2;
        addr2_order--;
    }

    while(addr3_order>1)
    {
        is_valid = arg3>=0 && arg3<data.size();

        if(!is_valid)
            break;

        arg3 =data[arg3];
        result[2] = arg3;
        addr3_order--;
    }

    return result;
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

void X86Algo::reset_code_to_size(int code_size)
{
    code = std::vector<std::array<int,SIZE_INSTR>>(code_size);
}

void X86Algo::set_code(std::vector<std::array<int,SIZE_INSTR>> code, int place_at)
{
    if(place_at>=0 && place_at<this->code.size())
    {
        reset_code_to_size(code.size() + place_at);

        for(int i=0;i<code.size();i++)
        {
            for(int j=0;j<SIZE_INSTR;j++)
            {
                this->code[place_at+i][j] = code[i][j];
            }
        }
    }
}

void X86Algo::set_input(std::vector<int> in)
{
    set_input_size(in.size());
    for(int i=0; i<std::min(in.size(), input.size());i++)
    {
        input[i] = in[i];
    }
}

void X86Algo::reset_data()
{
    for(int i=0;i<data.size();i++)
    {
        data[i] = 0;
    }
}

void X86Algo::reset_code(std::vector<std::array<int,SIZE_INSTR>> code)
{
    this->code = code;
}

//----- getters

std::vector<std::array<int,SIZE_INSTR>> X86Algo::get_code()
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
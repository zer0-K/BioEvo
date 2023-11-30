#include "EvoX.hpp"

#include "../../../Utils/Constants.hpp"
#include "InstructionMapping.hpp"

void EvoX::init()
{
    X86Algo::init();

    type = EVOX;
    add_type(EVOX);
}

std::vector<sp_entity> EvoX::exec(std::vector<sp_entity> entries)
{
    ///< 
    ///<    creates the code from the genes
    ///<    execute the code
    ///< 

    if(debug)
    {
        bool test = true;
    }

    create_code_from_genes();

    return X86Algo::exec(entries);
}

void EvoX::create_code_from_genes()
{
    int nb_instructions = (int) (genes.size()/SIZE_INSTR);

    if(nb_instructions == 0)
    {
        // if empty, complete with HALT only
        this->code = std::vector<std::array<int,SIZE_INSTR>>({{instruction::HALT, 0, 0, 0, 0, 0, 0}});
    }
    else
    {
        // INSTRUCTION, ISADDR1, ISADDR2, ISADDR3, ARG1, ARG2, ARG3

        this->code = std::vector<std::array<int,SIZE_INSTR>>(nb_instructions);
        
        for(int i=0;i<nb_instructions;i++)
        {
            this->code[i] = std::array<int,SIZE_INSTR>({
                this->genes[i*SIZE_INSTR], 
                this->genes[i*SIZE_INSTR+1], 
                this->genes[i*SIZE_INSTR+2], 
                this->genes[i*SIZE_INSTR+3], 
                this->genes[i*SIZE_INSTR+4], 
                this->genes[i*SIZE_INSTR+5], 
                this->genes[i*SIZE_INSTR+6]
            });
        }
        // note that code above can end without HALT instruction (exec loop will end)
    }

}

void EvoX::exec_instruction_gene(int instr, int addr1_order, int addr2_order, int addr3_order, 
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
    int source = arg2_;

    int nb_genes = genes.size();

    switch(instr)
    { 
        case instruction::GR:
            // read gene at arg2 and stores it arg1

            if(addr1_order>0 && arg1_>=0 && arg1_<data.size())
            {
                if(addr2_order==0)
                {
                    data[arg1_] = arg2_;
                }
                else if(arg2_>=0 && arg2_<genes.size())
                {
                    data[arg1_] = genes[arg2_];
                }
            }
 
            break;

        case instruction::GINS:
            // insert gene at arg1 with value of code at arg2

            if(addr1_order>0 && arg1_>=0 && arg1_<genes.size())
            {
                if(addr2_order==0)
                {
                    nb_genes++;
                    genes.push_back(0);

                    for(int i=0;i<genes.size()-arg1_-1;i++)
                    {
                        genes[nb_genes-i-1] = genes[nb_genes-i-2];
                    }
                    genes[arg1_] = arg2_;
                }
                else if(arg2_>=0 && arg2<data.size())
                {
                    nb_genes++;
                    genes.push_back(0);

                    for(int i=0;i<genes.size()-arg1_-1;i++)
                    {
                        genes[nb_genes-i-1] = genes[nb_genes-i-2];
                    }
                    genes[arg1_] = data[arg2_];
                }
            }

            break;

        case instruction::GDEL:
            // delete gene at arg1

            if(addr1_order == 0)
            {
                if(arg1_>=0 && arg1_<genes.size())
                {
                    for(int i=arg1_;i<nb_genes-1;i++)
                    {
                        genes[i] = genes[i+1];
                    }

                    nb_genes--;
                    genes.pop_back();
                }
            } 
            else if(arg1_>=0 && arg1_<data.size())
            {
                if(data[arg1_]>=0 && data[arg1_]<genes.size())
                {
                    for(int i=data[arg1_];i<nb_genes-1;i++)
                    {
                        genes[i] = genes[i+1];
                    }

                    nb_genes--;
                    genes.pop_back();
                }
            }
            
            break;

        case instruction::GDELW:
        {
            // delete whole instruction at arg1 
            // (3 genes genes at once if not at the end)
            // can delete only at beginning of instruction

            bool valid_args = true;
            if(addr1_order>0)
            {
                if(arg1_>=0 && arg1_<data.size())
                {
                    arg1_ = data[arg1_];
                }
                else
                {
                    valid_args = false;
                }
            }

            if(valid_args && arg1_>=0 && arg1_<genes.size()
                && arg1_%SIZE_INSTR==0)
            {

                // first case : deleting gene at the end of the genome
                // ( incomplete gene )
                if(arg1_+SIZE_INSTR>genes.size())
                {
                    while(nb_genes%SIZE_INSTR!=0)
                    {
                        genes.pop_back();
                        nb_genes--;
                    }
                }
                else
                {
                    int nb_instructions = (int) ( genes.size() / SIZE_INSTR ) ;
                    int instr_to_del = (int) ( arg1_ / SIZE_INSTR );

                    // shift all genes by 3

                    for(int i=instr_to_del;i<nb_instructions-1;i++)
                    {
                        for(int j=0;j<SIZE_INSTR;j++)
                        {
                            genes[i*SIZE_INSTR + j] = genes[SIZE_INSTR*(i+1) + j];
                        }
                    }

                    // if there are incomplete genes at the end
                    if(genes.size()%SIZE_INSTR!=0)
                    {
                        for(int j=0;j<genes.size()%SIZE_INSTR;j++)
                        {
                            genes[(nb_instructions-1)*SIZE_INSTR+j] = genes[nb_instructions*SIZE_INSTR+j];
                        }
                    }

                    // remove the last gene
                    for(int j=0;j<SIZE_INSTR;j++)
                    {
                        genes.pop_back();
                        nb_genes--;
                    }
               }
            }

            break;
        }
        case instruction::GSET:
            // set gene at arg1 with data at arg2

            if(addr1_order>0 && arg1_>=0 && arg1_<genes.size())
            {
                if(addr2_order==0)
                {
                    genes[arg1_] = arg2_;
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    genes[arg1_] = data[arg2_];
                }
            }

            break;

        case instruction::GADD:
            // add to gene at arg1 with data at arg2

            if(addr1_order>0 && arg1_>=0 && arg1_<genes.size())
            {
                if(addr2_order==0)
                {
                    genes[arg1_] += arg2_;
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    genes[arg1_] += data[arg2_];
                }
            }

            break;

        case instruction::GCPY:
        {
            // copy at destination data between arg2 and arg3 (included)

            if(addr1_order>0 && addr2_order>0 && addr3_order>0
                && destination>=0 && destination<genes.size()+1
                && arg2_>=0 && arg2_<data.size()
                && arg3_>=0 && arg3_<data.size())
            {
                int input_cpy_begin = arg2_;
                int input_cpy_end = arg3_;

                int nb_new_genes = input_cpy_end-input_cpy_begin+1;
                int nb_old_genes = genes.size();

                // add 0 at the end
                for(int i=0;i<nb_new_genes;i++)
                {
                    genes.push_back(0);
                }
                
                // shift everything
                for(int i=0;i<nb_old_genes-destination;i++)
                {
                    genes[nb_old_genes+nb_new_genes - i - 1] = genes[nb_old_genes-i-1];
                }

                // fill the genes with data
                for(int i=0;i<nb_new_genes;i++)
                {
                    genes[destination+i] = data[input_cpy_begin+i];
                }
            }

            break;
        }
        case instruction::MARKER:
            // do nothing

            /*
                genes[maker_pos] : position (in the genome) of the genetic marker
                genes[maker_pos+1] : type of the marker (for later)
                genes[maker_pos+2] : id 1 (func ID)
                genes[maker_pos+3] : id 2 (teleonomical ID)
                genes[maker_pos+4] : id 3 or genetic storage
                genes[maker_pos+5] : id 4 or genetic storage
                genes[maker_pos+6] : id 5 or genetic storage
            */

            break;

        case instruction::GCPYM:
        {
            // copy data between arg2 and arg3 at first genetic marker

            // find first genetic marker with given id (arg1_)

            bool valid_args = true;
            if(addr1_order>0)
            {
                if(arg1_>=0 && arg1_<data.size())
                {
                    arg1_ = data[arg1_];
                }
                else
                {
                    valid_args = false;
                }
            }
            addr2_order = addr2_order == 0 ? 0 : 1;
            addr3_order = addr3_order == 0 ? 0 : 1;

            if(valid_args)
            {

                int marker_pos = 0;
                bool found = false;
                while(!found && marker_pos<genes.size() )
                {
                    if(genes[marker_pos] == instruction::MARKER
                        && genes[marker_pos+1] == arg1_)
                    {
                        found = true;
                    }
                    else
                    {
                        marker_pos += 7;
                    }
                }

                // then, copy after the genetic marker
                //data.push_back(marker_pos);
                //marker_pos +=7 ;
                exec_instruction_gene(instruction::GCPY, 1, addr2_order, addr3_order, marker_pos, arg2_, arg3_);
                //data.pop_back();

                post_process_marker(marker_pos);
            }
            
            break;
        }
        case instruction::EXEC:
        {
            // execute genome at given pos
            // arg1 : pos in genome (multiple of 7)
            // arg2 : nb of instructions to execute (1 = 7 genes)

            //
            // !! executing once n genes at pos p is different than !!
            // !! executing n times a single gene from p to p+n-1 !!
            // !! -> indeed, some genes might have been added by the code executed !!
            //
            // avoid executing more than one line, because of jumps

            bool is_valid = true;
            
            if(addr1_order>0)
            {
                if(arg1_>=0 && arg1_<data.size())
                {
                    arg1_ = data[arg1_];
                }
                else
                {
                    is_valid = false;
                }
            }

            if(addr2_order>0)
            {
                if(arg2_>=0 && arg2_<data.size())
                {
                    arg2_ = data[arg2_];
                }
                else
                {
                    is_valid = false;
                }
            }

            if(is_valid && arg1_>=0 && arg2>=1
                && (arg1_ + arg2_)*SIZE_INSTR<genes.size())
            {
                auto code_exec = std::vector<std::array<int,SIZE_INSTR>>(arg2_);
        
                // save all the genes at once
                // garantee that code will be executed even if genes have been added in the meantime
                for(int i=0;i<arg2_;i++)
                {
                    auto i_genes = (i+arg1_)*SIZE_INSTR;
                    code_exec[i] = std::array<int,SIZE_INSTR>({
                        this->genes[i_genes], 
                        this->genes[i_genes+1], 
                        this->genes[i_genes+2], 
                        this->genes[i_genes+3], 
                        this->genes[i_genes+4], 
                        this->genes[i_genes+5], 
                        this->genes[i_genes+6]
                    });
                }

                for(int i=0;i<code_exec.size();i++)
                {
                    auto code_line = code_exec[i];
                    
                    exec_instruction(code_line[0], code_line[1], code_line[2], code_line[3], code_line[4], code_line[5], code_line[6]);
                    instr_counter++;
                }
            }
   
            break;
        }

        case instruction::CALL:
        {
            // call a function
            // works only for the JMP01 function execution architecture
            // (where the meta-exec function is at pos specified at 01)
            //
            // args of the function must be put on top of the stack before
            // we use "CALL" function
            //
            // arg1 :   if ==0, increment the stack to put the func ID on
            //          if ==1, put the func ID at the existing top
            // arg2 :   func ID

            bool is_valid = true;

            if(addr1_order>0)
            {
                if(arg1_>=0 && arg1_<data.size())
                {
                    arg1_ = data[arg1_];
                }
                else
                {
                    is_valid = false;
                }
            }

            if(addr2_order>0)
            {
                if(arg2_>=0 && arg2_<data.size())
                {
                    arg2_ = data[arg2_];
                }
                else
                {
                    is_valid = false;
                }
            }

            // to ensure we can check if algo has JMP01 arch
            if(genes.size()<30 || genes[1]<1)
            {
                is_valid = false;
            }

            if(is_valid)
            {
                int meta_exec_func_pos = genes[1];

                if(arg1_==0)
                {
                    exec_instruction(instruction::INC, 1, 0, 0, 99, 0, 0);
                    instr_counter++;
                }

                // put func ID on top of data stack
                exec_instruction(instruction::CPY, 2, 0, 0, 99, arg2_, 0);
                instr_counter++;

                // increment call stack
                exec_instruction(instruction::INC, 1, 0, 0, 0, 0, 0);
                instr_counter++;

                // save next instruction position on top of call stack
                program_counter++;
                exec_instruction(instruction::GPTR, 2, 0, 0, 0, 0, 0);
                program_counter--;
                instr_counter++;

                // call function
                exec_instruction(instruction::JMP, 0, 0, 0, meta_exec_func_pos, 0, 0);
                instr_counter++;
            }
 
            break;
        }
        case instruction::REGEN:
            // regenerate code from genes

            create_code_from_genes();

            // ! prog ptr will be incremented at end of instr exec (so '-1' ) !
            //program_counter -= 1;

            break;
        default:
            // does nothing
            break;
    }
}

void EvoX::post_process_marker(int marker_pos)
{
    int marker_type = genes[marker_pos+1];

    if(marker_type == 0)
    {
        // do nothing
    }
    if(marker_type == 1)
    {
        // delete marker
        // TODO
    }
}

// setters

void EvoX::set_genes(std::vector<int> genes)
{
    this->genes = genes;
}

// getters

std::vector<int> EvoX::get_genes()
{
    return genes;
}

// utils

void EvoX::print_genome()
{
    int nb_instructions = (int) (genes.size()/3);

    for(int i=0; i<nb_instructions; i++)
    {
        int instr = genes[i*3];
        int addr1 = genes[i*3+1];
        int addr2 = genes[i*3+2];

        std::string instr_str = (instr>=0 || instr<instruction::size)
            ? instruction_str[static_cast<instruction>(instr)]
            : "WRONG";
        std::cout << instr_str << "\t | " << addr1 << "\t | " << addr2 << std::endl;
    }

    // if there are some incomplete genes at the end
    if(genes.size() > nb_instructions*3)
    {
        int last_instr_pos = nb_instructions*3; 
        int instr = genes[last_instr_pos];

        std::string instr_str = (instr>=0 || instr<instruction::size)
            ? instruction_str[static_cast<instruction>(instr)]
            : "WRONG";

        std::cout << instr_str;

        if(genes.size() > last_instr_pos+1)    
        {
            std::cout << "\t | " << genes[last_instr_pos+1];
        }

        std::cout << std::endl;
    }
}

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
    int nb_instructions = (int) (genes.size()/3);

    if(nb_instructions == 0)
    {
        // if empty, complete with HALT only
        this->code = std::vector<std::array<int, 3>>({{instruction::HALT, 0, 0}});
    }
    else
    {
        // INSTRUCTION, ADDR1, ADDR2

        this->code = std::vector<std::array<int, 3>>(nb_instructions);
        
        for(int i=0;i<nb_instructions;i++)
        {
            this->code[i] = std::array<int, 3>({
                this->genes[i*3], 
                this->genes[i*3+1], 
                this->genes[i*3+2]
            });
        }
        // note that code above can end without HALT instruction (exec loop will end)
    }

}

void EvoX::exec_instruction_meta(int instr, int addr1, int addr2)
{
    int nb_genes = genes.size();

    switch(instr)
    { 
        case instruction::GINS:
            // insert gene at addr1 with value of code at addr2
            if(addr1>=0 && addr1<data.size()
                && addr2>=0 && addr2<data.size()
                && data[addr1]>=0 && data[addr1]<nb_genes)
            {
                nb_genes++;
                genes.push_back(0);

                for(int i=0;i<nb_genes-data[addr1]-1;i++)
                {
                    genes[nb_genes-i-1] = genes[nb_genes-i-2];
                }
                genes[data[addr1]] = data[addr2];
            }

            break;

        case instruction::GDEL:
            // delete gene at addr1
            if(addr1>=0 && addr1<data.size()
                && data[addr1]>=0 && data[addr1]<nb_genes)
            {
                for(int i=data[addr1];i<nb_genes-1;i++)
                {
                    genes[i] = genes[i+1];
                }

                nb_genes--;
                genes.pop_back();
            }
            break;

        case instruction::GDELW:
            // delete whole instruction at addr1 
            // (3 genes genes at once if not at the end)
            // can delete only at beginning of instruction
            if(addr1>=0 && addr1<data.size()
                && data[addr1]>=0 && data[addr1]<genes.size()
                && data[addr1]%3==0)
            {

                // first case : deleting gene at the end of the genome
                // ( incomplete gene )
                if(data[addr1]+3>genes.size())
                {
                    while(nb_genes%3!=0)
                    {
                        genes.pop_back();
                        nb_genes--;
                    }
                }
                else
                {
                    int nb_instructions = (int) ( genes.size() / 3 ) ;
                    int instr_to_del = (int) ( data[addr1] / 3 );

                    // shift all genes by 3

                    for(int i=instr_to_del;i<nb_instructions-1;i++)
                    {
                        genes[i*3] = genes[3*(i+1)];
                        genes[i*3+1] = genes[3*(i+1)+1];
                        genes[i*3+2] = genes[3*(i+1)+2];
                    }

                    // if there are incomplete genes at the end
                    if(genes.size()%3!=0)
                    {
                        genes[(nb_instructions-1)*3] = genes[nb_instructions*3];

                        if(genes.size()%3==2)
                        {
                            genes[(nb_instructions-1)*3+1] = genes[nb_instructions*3+1];
                        }
                    }

                    // remove the 3 last
                    genes.pop_back();
                    nb_genes--;
                    genes.pop_back();
                    nb_genes--;
                    genes.pop_back();
                    nb_genes--;
                }
            }
            break;

        case instruction::GSET:
            // set gene at addr1 with val of data at addr2
            if(addr1>=0 && addr1<data.size()
                && addr2>=0 && addr2<data.size()
                && data[addr1]>=0 && data[addr1]<nb_genes)
            {
               genes[data[addr1]] = data[addr2];
            }
            break;

        case instruction::GADD:
            // add to gene at addr1 with val of data at addr2
            if(addr1>=0 && addr1<data.size()
                && addr2>=0 && addr2<data.size()
                && data[addr1]>=0 && data[addr1]<nb_genes)
            {
               genes[data[addr1]] += data[addr2];
            }
            break;

        default:
            // does nothing
            break;
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
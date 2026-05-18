#include "EvoX.hpp"

#include <sstream>

#include "../../../Utils/Constants.hpp"
#include "InstructionMapping.hpp"
#include "Parsing/tRNATable.hpp"

void EvoX::init()
{
    XASMAlgo::init();

    type = EVOX;
    add_type(EVOX);
}

std::vector<sp_entity> EvoX::exec(std::vector<sp_entity> entries)
{
    ///< 
    ///<    creates the code from the phenotypic body
    ///<    execute the code
    ///< 

    if(debug)
    {
        bool test = true;
    }

    create_code_from_body();

    return XASMAlgo::exec(entries);
}

void EvoX::create_code_from_body()
{
    int nb_instructions = (int) (body.size()/SIZE_INSTR);

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
                this->body[i*SIZE_INSTR], 
                this->body[i*SIZE_INSTR+1], 
                this->body[i*SIZE_INSTR+2], 
                this->body[i*SIZE_INSTR+3], 
                this->body[i*SIZE_INSTR+4], 
                this->body[i*SIZE_INSTR+5], 
                this->body[i*SIZE_INSTR+6]
            });
        }
        // note that code above can end without HALT instruction (exec loop will end)
    }

}

void EvoX::exec_instruction_molecule(int instr, int arg1_depth, int arg2_depth, int arg3_depth, 
    int arg1, int arg2, int arg3)
{
    bool is_valid = true;

    auto transformed_args = get_addrs(is_valid, arg1_depth, arg2_depth, arg3_depth,
        arg1, arg2, arg3);

    if(!is_valid)
        return;

    int arg1_ = transformed_args[0];
    int arg2_ = transformed_args[1];
    int arg3_ = transformed_args[2];

    int destination = arg1_;
    int source = arg2_;

    int nb_body = body.size();

    switch(instr)
    { 
        case instruction::GR:
            // read gene at arg2 and stores it arg1

            if(arg1_depth>0 && arg1_>=0 && arg1_<data.size())
            {
                if(arg2_depth==0)
                {
                    data[arg1_] = arg2_;
                }
                else if(arg2_>=0 && arg2_<body.size())
                {
                    data[arg1_] = body[arg2_];
                }
            }
 
            break;

        case instruction::GINS:
            // insert gene at arg1 with value of code at arg2

            if(arg1_depth>0 && arg1_>=0 && arg1_<body.size())
            {
                if(arg2_depth==0)
                {
                    nb_body++;
                    body.push_back(0);

                    for(int i=0;i<body.size()-arg1_-1;i++)
                    {
                        body[nb_body-i-1] = body[nb_body-i-2];
                    }
                    body[arg1_] = arg2_;
                }
                else if(arg2_>=0 && arg2<data.size())
                {
                    nb_body++;
                    body.push_back(0);

                    for(int i=0;i<body.size()-arg1_-1;i++)
                    {
                        body[nb_body-i-1] = body[nb_body-i-2];
                    }
                    body[arg1_] = data[arg2_];
                }
            }

            break;

        case instruction::GDEL:
            // delete gene at arg1

            if(arg1_depth == 0)
            {
                if(arg1_>=0 && arg1_<body.size())
                {
                    for(int i=arg1_;i<nb_body-1;i++)
                    {
                        body[i] = body[i+1];
                    }

                    nb_body--;
                    body.pop_back();
                }
            } 
            else if(arg1_>=0 && arg1_<data.size())
            {
                if(data[arg1_]>=0 && data[arg1_]<body.size())
                {
                    for(int i=data[arg1_];i<nb_body-1;i++)
                    {
                        body[i] = body[i+1];
                    }

                    nb_body--;
                    body.pop_back();
                }
            }
            
            break;

        case instruction::GDELW:
        {
            // delete whole instruction at arg1 
            // can delete only at beginning of instruction

            bool valid_args = true;
            if(arg1_depth>0)
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

            if(valid_args && arg1_>=0 && arg1_<body.size()
                && arg1_%SIZE_INSTR==0)
            {

                // first case : deleting gene at the end of the phenotypic body
                // ( incomplete gene )
                if(arg1_+SIZE_INSTR>body.size())
                {
                    while(nb_body%SIZE_INSTR!=0)
                    {
                        body.pop_back();
                        nb_body--;
                    }
                }
                else
                {
                    int nb_instructions = (int) ( body.size() / SIZE_INSTR ) ;
                    int instr_to_del = (int) ( arg1_ / SIZE_INSTR );

                    // shift all phenotypic body

                    for(int i=instr_to_del;i<nb_instructions-1;i++)
                    {
                        for(int j=0;j<SIZE_INSTR;j++)
                        {
                            body[i*SIZE_INSTR + j] = body[SIZE_INSTR*(i+1) + j];
                        }
                    }

                    // if there are incomplete phenotypic moleculesat the end
                    if(body.size()%SIZE_INSTR!=0)
                    {
                        for(int j=0;j<body.size()%SIZE_INSTR;j++)
                        {
                            body[(nb_instructions-1)*SIZE_INSTR+j] = body[nb_instructions*SIZE_INSTR+j];
                        }
                    }

                    // remove the last gene
                    for(int j=0;j<SIZE_INSTR;j++)
                    {
                        body.pop_back();
                        nb_body--;
                    }
               }
            }

            break;
        }
        case instruction::GSET:
            // set gene at arg1 with data at arg2

            if(arg1_depth>0 && arg1_>=0 && arg1_<body.size())
            {
                if(arg2_depth==0)
                {
                    body[arg1_] = arg2_;
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    body[arg1_] = data[arg2_];
                }
            }

            break;

        case instruction::GADD:
            // add to gene at arg1 with data at arg2

            if(arg1_depth>0 && arg1_>=0 && arg1_<body.size())
            {
                if(arg2_depth==0)
                {
                    body[arg1_] += arg2_;
                }
                else if(arg2_>=0 && arg2_<data.size())
                {
                    body[arg1_] += data[arg2_];
                }
            }

            break;

        case instruction::GCPY:
        {
            // copy at destination data between arg2 and arg3 (included)

            if(arg1_depth>0 && arg2_depth>0 && arg3_depth>0
                && destination>=0 && destination<body.size()+1
                && arg2_>=0 && arg2_<data.size()
                && arg3_>=0 && arg3_<data.size())
            {
                int input_cpy_begin = arg2_;
                int input_cpy_end = arg3_;

                int nb_new_body = input_cpy_end-input_cpy_begin+1;
                int nb_old_body = body.size();

                // add 0 at the end
                for(int i=0;i<nb_new_body;i++)
                {
                    body.push_back(0);
                }
                
                // shift everything
                for(int i=0;i<nb_old_body-destination;i++)
                {
                    body[nb_old_body+nb_new_body - i - 1] = body[nb_old_body-i-1];
                }

                // fill the phenotypic body with data
                for(int i=0;i<nb_new_body;i++)
                {
                    body[destination+i] = data[input_cpy_begin+i];
                }
            }

            break;
        }
        case instruction::MARKER:
            // do nothing

            /*
                body[maker_pos] : position (in the phenotypic body) of the phenotypic marker
                body[maker_pos+1] : type of the marker (for later)
                body[maker_pos+2] : id 1 (func ID)
                body[maker_pos+3] : id 2 (teleonomical ID)
                body[maker_pos+4] : id 3 or genetic storage
                body[maker_pos+5] : id 4 or genetic storage
                body[maker_pos+6] : id 5 or genetic storage
            */

            break;

        case instruction::GCPYM:
        {
            // copy data between arg2 and arg3 at first phenotypic marker

            // find first phenotypic marker with given id (arg1_)

            bool valid_args = true;
            if(arg1_depth>0)
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
            arg2_depth = arg2_depth == 0 ? 0 : 1;
            arg3_depth = arg3_depth == 0 ? 0 : 1;

            if(valid_args)
            {

                int marker_pos = 0;
                bool found = false;
                while(!found && marker_pos<body.size() )
                {
                    if(body[marker_pos] == instruction::MARKER
                        && body[marker_pos+1] == arg1_)
                    {
                        found = true;
                    }
                    else
                    {
                        marker_pos += 7;
                    }
                }

                // then, copy after the phenotypic marker
                //data.push_back(marker_pos);
                //marker_pos +=7 ;
                exec_instruction_molecule(instruction::GCPY, 1, arg2_depth, arg3_depth, marker_pos, arg2_, arg3_);
                //data.pop_back();

                post_process_marker(marker_pos);
            }
            
            break;
        }
        case instruction::EXEC:
        {
            // execute phenotypic body at given pos
            // arg1 : pos in phenotypic body (multiple of 7)
            // arg2 : nb of instructions to execute (1 = 7 phenotypic body)

            //
            // !! executing once n phenotypic molecules at pos p is different than !!
            // !! executing n times a single gene from p to p+n-1 !!
            // !! -> indeed, some phenotypic molecules might have been added by the code executed !!
            //
            // avoid executing more than one line, because of jumps

            bool is_valid = true;
            
            if(arg1_depth>0)
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

            if(arg2_depth>0)
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
                && (arg1_ + arg2_)*SIZE_INSTR<body.size())
            {
                auto code_exec = std::vector<std::array<int,SIZE_INSTR>>(arg2_);
        
                // save all the phenotypic body at once
                // garantee that code will be executed even if phenotypic molecules have been added in the meantime
                for(int i=0;i<arg2_;i++)
                {
                    auto i_body = (i+arg1_)*SIZE_INSTR;
                    code_exec[i] = std::array<int,SIZE_INSTR>({
                        this->body[i_body], 
                        this->body[i_body+1], 
                        this->body[i_body+2], 
                        this->body[i_body+3], 
                        this->body[i_body+4], 
                        this->body[i_body+5], 
                        this->body[i_body+6]
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

            if(arg1_depth>0)
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

            if(arg2_depth>0)
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
            if(body.size()<30 || body[1]<1)
            {
                is_valid = false;
            }

            if(is_valid)
            {
                int meta_exec_func_pos = body[1];

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
            // regenerate code from phenotypic body

            create_code_from_body();

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
    int marker_type = body[marker_pos+1];

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

void EvoX::set_body(std::vector<int> body)
{
    this->body = body;
}

// getters

std::vector<int> EvoX::get_body()
{
    return body;
}

// utils

std::string EvoX::body_to_evox_string() const
{
    if (body.empty()) return "";

    int nb_mol = (int)(body.size() / SIZE_INSTR);

    auto mol = [&](int m) {
        std::array<int, SIZE_INSTR> arr{};
        for (int j = 0; j < SIZE_INSTR; j++) arr[j] = body[m * SIZE_INSTR + j];
        return arr;
    };

    auto is_dna_marker = [&](int m) {
        auto mv = mol(m);
        return mv[0] == instruction::MARKER && mv[1] == 0 && mv[2] == -1;
    };

    // Locate the DNA section (pair of {MARKER, 0, -1, ...})
    int dna_start = -1, dna_end = -1;
    for (int m = 0; m < nb_mol; m++) {
        if (is_dna_marker(m)) {
            if (dna_start < 0) dna_start = m;
            else { dna_end = m; break; }
        }
    }

    int prog_end    = (dna_start >= 0) ? dna_start : nb_mol;
    int trail_start = (dna_end   >= 0) ? dna_end + 1 : nb_mol;

    // Instruction name lookup
    auto instr_name = [&](int code) -> std::string {
        auto it = instruction_str.find(static_cast<instruction>(code));
        return (it != instruction_str.end()) ? it->second : std::to_string(code);
    };

    auto fmt_instr = [&](const std::array<int, SIZE_INSTR>& m) -> std::string {
        std::ostringstream s;
        s << instr_name(m[0]);
        for (int j = 1; j < SIZE_INSTR; j++) s << " " << m[j];
        return s.str();
    };

    auto fmt_raw = [&](const std::array<int, SIZE_INSTR>& m) -> std::string {
        std::ostringstream s;
        for (int j = 0; j < SIZE_INSTR; j++) s << (j ? " " : "") << m[j];
        return s.str();
    };

    std::ostringstream out;

    // ── 1. RAW section ──────────────────────────────────────────────────────
    int cur = 0;
    while (cur < prog_end && mol(cur)[0] != instruction::MARKER) cur++;

    if (cur > 0) {
        out << "RAW\n";
        for (int m = 0; m < cur; m++)
            out << "    " << fmt_raw(mol(m)) << "\n";
        out << "END\n\n";
    }

    // ── 2. Progteins ────────────────────────────────────────────────────────
    while (cur < prog_end) {
        auto hdr = mol(cur);
        if (hdr[0] != instruction::MARKER) { cur++; continue; }

        int pid = hdr[2];

        // optional tRNA label
        std::string label;
        auto trna_it = tRNA_by_id.find(pid);
        if (trna_it != tRNA_by_id.end()) {
            const std::string& name = trna_it->second.name;
            label = " " + (name.size() > 5 ? name.substr(5) : name);
        }
        out << "PROGTEIN" << label << " id=" << pid << "\n";
        cur++;

        while (cur < prog_end) {
            auto cm = mol(cur++);
            out << "    " << fmt_instr(cm) << "\n";
            if (cm[0] == instruction::MARKER && cm[2] == pid) break;
        }
        out << "END\n\n";
    }

    // ── 3. DNA section ──────────────────────────────────────────────────────
    if (dna_start >= 0 && dna_end >= 0) {
        out << "DNA\n";

        int flat_start = (dna_start + 1) * SIZE_INSTR;
        int flat_end   = dna_end * SIZE_INSTR;
        int j = flat_start;

        while (j < flat_end) {
            if (body[j] != GSTART_ID) { j++; continue; }
            j++;
            if (j >= flat_end) break;
            int gene_id = body[j++];
            out << "    GENE id=" << gene_id << "\n";

            while (j < flat_end && body[j] != GSTOP_ID) {
                int tok = body[j];
                auto it = tRNA_by_id.find(tok);
                if (it != tRNA_by_id.end()) {
                    const std::string& name = it->second.name;
                    out << "        " << (name.size() > 5 ? name.substr(5) : name);
                    int arity = it->second.arity;
                    j++;
                    for (int a = 0; a < arity && j < flat_end && body[j] != GSTOP_ID; a++)
                        out << " " << body[j++];
                    out << "\n";
                } else {
                    out << "        " << tok << "\n";
                    j++;
                }
            }
            if (j < flat_end && body[j] == GSTOP_ID) j++;
            while (j < flat_end && body[j] == 0) j++;  // skip padding
            out << "    END\n";
        }
        out << "END\n";
    }

    // ── 4. Trail section ────────────────────────────────────────────────────
    if (trail_start < nb_mol) {
        out << "\nTRAIL\n";
        for (int m = trail_start; m < nb_mol; m++)
            out << "    " << fmt_raw(mol(m)) << "\n";
        out << "END\n";
    }

    return out.str();
}

void EvoX::print_body()
{
    int nb_instructions = (int) (body.size()/3);

    for(int i=0; i<nb_instructions; i++)
    {
        int instr = body[i*3];
        int addr1 = body[i*3+1];
        int addr2 = body[i*3+2];

        std::string instr_str = (instr>=0 || instr<instruction::size)
            ? instruction_str[static_cast<instruction>(instr)]
            : "WRONG";
        std::cout << instr_str << "\t | " << addr1 << "\t | " << addr2 << std::endl;
    }

    // if there are some incomplete phenotypic molecules at the end
    if(body.size() > nb_instructions*3)
    {
        int last_instr_pos = nb_instructions*3; 
        int instr = body[last_instr_pos];

        std::string instr_str = (instr>=0 || instr<instruction::size)
            ? instruction_str[static_cast<instruction>(instr)]
            : "WRONG";

        std::cout << instr_str;

        if(body.size() > last_instr_pos+1)    
        {
            std::cout << "\t | " << body[last_instr_pos+1];
        }

        std::cout << std::endl;
    }
}

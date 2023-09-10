#pragma once

/**
 * ! This file hpp only !
 */

#include <vector>
#include <iostream>
#include <string>

/**
 * @brief creates natural number recursively, with a cost
 */
class NaturalCreatorCost
{
private:
    uint cost;
    uint natural_number_created;

    std::vector<uint> temp_numbers;

public:
    NaturalCreatorCost(uint cost)
    {
        this->cost = cost;
    }

    void create()
    {

    }

};

class AbstractRecursiveFunction
{
protected:
    std::string name;
    uint in_dim;
    uint out_dim;

    bool check_in(std::vector<uint> args)
    {
        if(args.size() != in_dim)
        {
            std::cout << "Error : " << name
                << ", wrong param size. "
                << "\tGiven : " << args.size() << " args."
                << std::endl
                << "\tExpected : " << in_dim << " args."
                << std::endl
                << "Returning 0."
                << std::endl;

            return false;
        }

        return true;
    }

    void show_computation(std::vector<uint> args, std::vector<uint> res)
    {
        if(verbose_experiment_1)
        {
            std::cout << "Call of " << name << " : " << std::endl;
            std::cout << "\tArgs : ";
            for(int i=0;i<args.size();i++)
                std::cout << args[i] << ", ";
            std::cout << std::endl;
            std::cout << "\tResults : ";
            for(int i=0;i<res.size();i++)
                std::cout << res[i] << ", ";
            std::cout << std::endl;
        }
    }

public:
    AbstractRecursiveFunction(std::string name)
    {
        this->name = name;
    }

    virtual std::vector<uint> apply(std::vector<uint> args,
        uint &cost,
        bool apply_cost) = 0;

    std::string get_name() { return name; }
    uint get_in_dim() { return in_dim; }
    uint get_out_dim() { return out_dim; }
};

class CompositeFunction : public AbstractRecursiveFunction
{
protected:
    std::vector<AbstractRecursiveFunction*> funcs;

public:
    CompositeFunction(std::vector<AbstractRecursiveFunction*> funcs)
        : AbstractRecursiveFunction::AbstractRecursiveFunction("")
    {
        name = "composite";
        for(int i=0;i<funcs.size();i++)
        {
            name += " " + funcs[i]->get_name();
        }

        for(int i=1;i<funcs.size();i++)
        {
            if(funcs[i-1]->get_in_dim() != funcs[i]->get_out_dim())
            {
                std::cout << "Error : " << name
                    << ", wrong func sizing. "
                    << "\tIn of " << funcs[i-1]->get_name()
                    << " ( " << funcs[i-1]->get_in_dim() << " )"
                    << "\t\tmust be out of : " << funcs[i]->get_name()
                    << " ( " << funcs[i]->get_out_dim() << " )"
                    << std::endl;
            }
 
        }

        this->funcs = funcs;

        in_dim = funcs[funcs.size()-1]->get_in_dim();
        out_dim = funcs[0]->get_out_dim();
    }

    std::vector<uint> apply(std::vector<uint> args,
        uint &cost,
        bool apply_cost) override 
    {
        if(apply_cost)
            cost++;

        std::vector<uint> res = args;

        // last func of the vector is the first to be applied
        for(int i=funcs.size()-1;i>=0;i--)
        {
            res = funcs[i]->apply(res, cost, false);
        }

        this->show_computation(args, res);        

        return res;
    } 
};

class VectorFunction : public AbstractRecursiveFunction
{
protected:
    std::vector<AbstractRecursiveFunction*> funcs;

public:
    VectorFunction(std::vector<AbstractRecursiveFunction*> funcs)
        : AbstractRecursiveFunction::AbstractRecursiveFunction("")
    {
        name = "vector";

        for(int i=0;i<funcs.size();i++)
        {
            name += " " + funcs[i]->get_name();
        }

        this->funcs = funcs;

        in_dim = 0;
        out_dim = 0;
        for(int i=0;i<funcs.size();i++)
        {
            in_dim += funcs[i]->get_in_dim();
            out_dim += funcs[i]->get_out_dim();
        }
    }

    std::vector<uint> apply(std::vector<uint> args,
        uint &cost,
        bool apply_cost) override 
    {
        if(apply_cost)
            cost++;

        if(!check_in(args))
            return std::vector<uint>({0});


        // builds inputs for each function

        std::vector<std::vector<uint>> ins = std::vector<std::vector<uint>>(funcs.size());

        uint curr_index = 0;
        for(int i=0;i<funcs.size();i++)
        {
            std::vector<uint>::const_iterator first = args.begin() + curr_index;
            std::vector<uint>::const_iterator last = args.begin() + curr_index + funcs[i]->get_in_dim();

            ins[i] = std::vector<uint>(first, last);

            curr_index += funcs[i]->get_in_dim();
        }
    

        // compute each component

        std::vector<std::vector<uint>> outs = std::vector<std::vector<uint>>(funcs.size());

        for(int i=0;i<funcs.size();i++)
        {
            outs[i] = funcs[i]->apply(ins[i], cost, false);
        }


        // complete output

        std::vector<uint> res = std::vector<uint>(out_dim);

        curr_index = 0;
        for(int i=0;i<funcs.size();i++)
        {
            for(int j=0;j<funcs[i]->get_out_dim();j++)
            {
                res[curr_index+j] = outs[i][j];
            }

            curr_index += funcs[i]->get_out_dim();
        }

        this->show_computation(args, res);        

        return res;
    } 
};

class CreateZero : public AbstractRecursiveFunction
{
public:
    CreateZero() 
        : AbstractRecursiveFunction::AbstractRecursiveFunction("0 creator")
    {
        in_dim = 0;
        out_dim = 1;
    }

    std::vector<uint> apply(std::vector<uint> args,
        uint &cost,
        bool apply_cost) override 
    {
        if(apply_cost)
            cost++;

        if(!check_in(args))
            return std::vector<uint>({0});
    
        std::vector<uint> res({0});

        this->show_computation(args, res);        

        return res;
    }
};

class Id : public AbstractRecursiveFunction
{
public:
    Id() 
        : AbstractRecursiveFunction::AbstractRecursiveFunction("id")
    {
        in_dim = 1;
        out_dim = 1;
    }

    std::vector<uint> apply(std::vector<uint> args,
        uint &cost,
        bool apply_cost) override 
    {
        if(apply_cost)
            cost++;
    
        if(!check_in(args))
            return std::vector<uint>({0});
 
        std::vector<uint> res({args[0]});

        this->show_computation(args, res);        

        return res;
    }
};

class Successor : public AbstractRecursiveFunction
{
public:
    Successor() 
        : AbstractRecursiveFunction::AbstractRecursiveFunction("successor")
    {
        in_dim = 1;
        out_dim = 1;
    }

    std::vector<uint> apply(std::vector<uint> args,
        uint &cost,
        bool apply_cost) override 
    {
        if(apply_cost)
            cost++;
    
        if(!check_in(args))
            return std::vector<uint>({0});


        std::vector<uint> res({args[0]+1});

        this->show_computation(args, res);
 
        return res;
    }
};

class Selector : public AbstractRecursiveFunction
{
protected:
    uint arg_pos;

public:

    Selector(uint dim, uint pos) 
        : AbstractRecursiveFunction::AbstractRecursiveFunction("selector " + std::to_string(pos))
    { 
        in_dim = dim;
        out_dim = 1;
        arg_pos = pos; 

        if(pos>dim-1)
        {
            std::cout << "Selector position must be between 0 and "
                << dim-1 << ". Given : " << pos << std::endl;
        }
    }

    std::vector<uint> apply(std::vector<uint> args,
        uint &cost,
        bool apply_cost) override 
    {
        if(apply_cost)
            cost++;

        uint i = arg_pos;

        if(arg_pos<0 || arg_pos>args.size())
        {
            std::cout << "Error : " << name
                << ". Trying to select component "
                << arg_pos << ", but there were " << args.size() << "args."
                << std::endl
                << "Returning first argument."
                << std::endl;

            i = 0;
        }

        std::vector<uint> res({args[i]});

        this->show_computation(args, res);        

        return res;
    }
};

class RecursiveFunction : public AbstractRecursiveFunction
{
protected:
    AbstractRecursiveFunction *g;
    AbstractRecursiveFunction *h;
 
public:

    RecursiveFunction(std::string name,
        uint &cost, 
        AbstractRecursiveFunction *g,
        AbstractRecursiveFunction *h,
        bool apply_cost)
        : AbstractRecursiveFunction::AbstractRecursiveFunction(name)
    {
        if(apply_cost)
            cost++;

        this->g = g;
        this->h = h;

        in_dim = g->get_in_dim() + 1;
        out_dim = g->get_out_dim();

        if(h->get_in_dim() != g->get_in_dim() + 2
            || h->get_out_dim() != g->get_out_dim())
        {
            std::cout << "Error : " << name
                << ", wrong func sizing. "
                << "\th in must be g in + 2"
                << "\t\th in : " << h->get_in_dim() << " ; "
                << "g in : " << g->get_in_dim()
                << std::endl
                << "\th out and g out should be the same"
                << "\t\th out : " << h->get_out_dim() << " ; "
                << "g out : " << g->get_out_dim()
                << std::endl;
        }
    }

    /**
     * here args are k-ary
     */
    std::vector<uint> apply(std::vector<uint> args,
        uint &cost,
        bool apply_cost) override 
    {
        if(apply_cost)
            cost++;

        if(!check_in(args))
            return std::vector<uint>({0});

        std::vector<uint> res;

        if(args[0] == 0)
        {
            // k-ary args for g, beginning after first arg of f
            std::vector<uint>::const_iterator first = args.begin() + 1;
            std::vector<uint>::const_iterator last = args.end();

            std::vector<uint> args_g(first, last);
            res = g->apply(args_g, cost, false);
        }
        else
        {
            std::vector<uint> args_h_temp;
            std::vector<uint> args_h(args.size()+1);

            // remove/unpack successor to the first arg
            args[0] = args[0] - 1;

            args_h[0] = args[0];
            args_h_temp = this->apply(args, cost, false);
            for(int i=0;i<args_h_temp.size();i++)
                args_h[1+i] = args_h_temp[i];

            // completing with the k-ary args
            for(uint i=1;i<args.size();i++)
            {
                args_h[i+2] = args[i];
            }

            res = h->apply(args_h, cost, false);
        }

        this->show_computation(args, res);        

        return res;
    }   
};


class RecursiveApplier
{
public:
    RecursiveApplier()
    {
        AbstractRecursiveFunction* create0 = new CreateZero();
        AbstractRecursiveFunction* id = new Id();
        AbstractRecursiveFunction* successor = new Successor(); 
        AbstractRecursiveFunction* selector1 = new Selector(1, 0);
        AbstractRecursiveFunction* selector2 = new Selector(3, 1);

        AbstractRecursiveFunction* h = new CompositeFunction(std::vector<AbstractRecursiveFunction*>({
            successor, 
            selector2
        }));
        AbstractRecursiveFunction* g = id;

        uint cost = 0;
        AbstractRecursiveFunction* addition = new RecursiveFunction("addition", cost, g, h, false);

        uint x=15;
        uint y=24;
        std::vector<uint> args({x, y});
        std::vector<uint> res = addition->apply(args, cost, false);

        std::cout << "Results : " << x << " + " << y << " = " << res[0] << std::endl;
    }
};


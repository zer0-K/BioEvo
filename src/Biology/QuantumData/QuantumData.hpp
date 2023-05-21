#pragma once

#include "QuantumDataAbstract.hpp"

/// @brief Minimal piece of data
template<class T, class U>
class QuantumData : public QuantumDataAbstract
{
protected:
    T x;
    U f_x;

public:
    /**
     * @brief Constructor
     * 
     * @param[in] x argument
     * @param[in] f_x image
    */
    QuantumData(T x, U f_x)
    {
        this->x = x;
        this->f_x = f_x;
    }

    // getters
    T get_x() { return x; }
    U get_f_x() { return f_x; }
};

template<class T, class U>
using sp_qdata = std::shared_ptr<QuantumData<T,U>>;
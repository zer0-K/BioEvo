#pragma once

#include <vector>

template<typename X, typename Y>
class Pair
{
private:
    X* x;  ///< x (array reprenting a math vector)
    Y f_x; ///< f(x) (image of x)

public:
    /**
     * @brief Constructor
     * 
     * @param[in] x x (array reprenting a math vector)
     * @param[in] f_x f(x)
    */
    Pair(X* x, Y f_x)
    {
        this->x = x;
        this->f_x = f_x;
    }

    /**
     * getters
    */

    X* get_x() { return x; }
    Y get_f_x() { return f_x; }
};

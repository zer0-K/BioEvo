#pragma once

#include <string>

/// @brief empty trait for abstraction
class AbstractTrait
{
protected:
    std::string name;   ///< name of the trait

public:
    //----- setters
    void set_name(std::string name_) { name=name_; }

    //----- getters
    std::string get_name() { return name; }

    //----- other
    std::string to_string() { return this->name; }
};
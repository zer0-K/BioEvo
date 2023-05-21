#pragma once

#include <string>
#include <memory>

/// @brief empty trait for template abstraction
class AbstractTrait
{
protected:
    std::string name;   ///< name of the trait

public:
    // virtual default destructor to explicit polymorphism (needed for shared pointers dynamic cast)
    virtual ~AbstractTrait() {};

    //----- setters
    void set_name(std::string name_) { name=name_; }

    //----- getters
    std::string get_name() { return name; }

    //----- other
    std::string to_string() { return this->name; }
    std::string to_json() { return "{'name'"+this->name+"'}"; }
};

typedef std::shared_ptr<AbstractTrait> sp_abstracttrait;
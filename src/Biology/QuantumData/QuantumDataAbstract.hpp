#pragma once

#include "../AbstractTrait.hpp"

/// @brief Minimal piece of data
class QuantumDataAbstract : public AbstractTrait
{
};

typedef std::shared_ptr<QuantumDataAbstract> sp_qdata_abstr;
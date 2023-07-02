#pragma once

#include "../../../Entities/VoidEntity.hpp"

class TestEntity : public Entity
{
    sp_entity_void entity_x;
    sp_entity_void entity_f_x;

    TestEntity(sp_entity_void x, sp_entity_void f_x);

    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};
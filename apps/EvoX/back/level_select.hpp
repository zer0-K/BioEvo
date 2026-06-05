#pragma once

#include "tree.hpp"
#include "evox_universe.hpp"

#include <vector>
#include <string>
#include <cstring>

namespace back::level_select
{
    back::tree::Tree<std::string> menu("ROOT");

    void build_menu_tree()
    {
        auto* research = menu.addChild(menu.root(), "Research");

        auto* new_gene = menu.addChild(research, "1 - new gene");

        auto* new_gene_1 = menu.addChild(new_gene, "1.1 - new gene 1");


        auto* levels = menu.addChild(menu.root(), "levels");
    }
}

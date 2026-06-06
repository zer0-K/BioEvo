#pragma once

#include "tree.hpp"
#include "evox_universe.hpp"

#include <vector>
#include <filesystem>
#include <string>
#include <cstring>

namespace fs = std::filesystem;

namespace back::level_select
{
    fs::path data_path = fs::path("/home") / "adrien" / "Programmation" / 
        "Projets" / "BioEvo" / "apps" / "EvoX" / "data" / "levels";
    back::tree::Tree<std::string> menu("ROOT", data_path);

    void build_menu_tree()
    {
        auto* research = menu.addChild(menu.root(), "Research", "research");

        auto* new_gene = menu.addChild(research, "1 - new gene", "new_gene");

        auto* new_gene_1 = menu.addChild(new_gene, "1.1 - new gene 1", "new_gene_1");


        auto* levels = menu.addChild(menu.root(), "levels", "levels");
    }
}

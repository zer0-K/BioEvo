#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <filesystem>
#include "evox_universe.hpp"
#include "tree.hpp"
#include "level/level.hpp"

namespace fs = std::filesystem;

namespace back::app_state
{

    enum class AppScreen {
        MainMenu,
        MenuExp,
        Simulation,
    };

    struct AppState
    {
        // ── Navigation ────────────────────────────────────────────────
        AppScreen          screen      = AppScreen::MainMenu;
        std::string        current_exp = "ROOT";
        bool               show_about  = false;
        back::level::Level level       = back::level::Level();

        void start_simulation(back::tree::Tree<std::string>::Node* node)
        {
            level.start_simulation(node);
            screen = AppScreen::Simulation;
        }

        void exit_simulation()
        {
            level.exit_simulation();
            current_exp = "ROOT";
            screen      = AppScreen::MenuExp;
        }

        // ── Helpers for GridFBO ───────────────────────────────────────

        std::vector<bool> make_cell_grid() const
        {
            std::vector<bool> g(level.universe.cells.size());
            for (size_t i = 0; i < level.universe.cells.size(); i++)
                g[i] = !level.universe.cells[i].is_void;
            return g;
        }

        int grid_w() const { return (int)level.universe.cells.size(); }
        int grid_h() const { return 1; }
    };

} // namespace back::app_state

#pragma once

#include <vector>
#include <string>
#include <cstring>
#include "../evox_universe.hpp"

namespace back::level
{

    class Level
    {
    public:
        std::string experiment_name;

        // ── Default config (applied when starting a simulation) ───────
        int  cfg_nb_cells   = 4;
        int  cfg_max_instr  = 1 << 22;
        int  cfg_data_stack = 150;

        // ── Simulation state ──────────────────────────────────────────
        back::evox_universe::EvoXUniverse universe;

        bool  running       = false;
        float step_interval = 0.5f;   // seconds between auto-steps
        float step_timer    = 0.0f;

        // ── Grid display ──────────────────────────────────────────────
        float cell_size  = 80.0f;
        bool  show_editor = true;

        // ── Cell editor ───────────────────────────────────────────────
        int  selected_cell = -1;
        bool editor_dirty  = false;

        static constexpr size_t EDITOR_BUF = 1 << 20;  // 1 MB
        std::vector<char> editor_buf;

        char load_path[512] = "";
        char save_dir[512]  = "/tmp/evox_experiment";

        Level()
        {
            editor_buf.resize(EDITOR_BUF, '\0');
        }

        void start_simulation(std::string exp_name)
        {
            experiment_name            = exp_name;
            universe.nb_cells          = cfg_nb_cells;
            universe.max_nb_instr_exec = cfg_max_instr;
            universe.data_stack_init   = cfg_data_stack;
            universe.reset_cells();
            selected_cell = -1;
            editor_buf[0] = '\0';
            editor_dirty  = false;
            running       = false;
            step_timer    = 0.0f;
        }

        void exit_simulation()
        {
            running = false;
        }

        // ── Cell selection + editor ───────────────────────────────────
        void select_cell(int idx)
        {
            if (editor_dirty && selected_cell >= 0)
                apply_editor();
            selected_cell = idx;
            load_editor();
        }

        void load_editor()
        {
            editor_dirty = false;
            if (selected_cell < 0 || selected_cell >= (int)universe.cells.size()) {
                editor_buf[0] = '\0';
                return;
            }
            const auto& c = universe.cells[selected_cell];
            if (c.is_void) {
                editor_buf[0] = '\0';
            } else {
                size_t len = std::min(c.evox_str.size(), EDITOR_BUF - 1);
                std::memcpy(editor_buf.data(), c.evox_str.data(), len);
                editor_buf[len] = '\0';
            }
        }

        void apply_editor()
        {
            if (selected_cell < 0 || selected_cell >= (int)universe.cells.size()) return;
            std::string s(editor_buf.data());
            if (s.empty())
                universe.set_cell_void(selected_cell);
            else
                universe.set_cell_evox(selected_cell, s);
            editor_dirty = false;
        }
    };

} // namespace back::level

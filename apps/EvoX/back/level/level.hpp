#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include "level_config.hpp"
#include "../tree.hpp"
#include "../evox_universe.hpp"

namespace fs = std::filesystem;

namespace back::level
{

    class Level
    {
    public:
        // ── Default config (applied when starting a simulation) ───────
        LevelConfig base_config;
        LevelConfig config;
        fs::path config_directory;

        // ── Simulation state ──────────────────────────────────────────
        back::evox_universe::EvoXUniverse universe;

        bool  running       = false;
        float step_interval = 0.5f;   // seconds between auto-steps
        float step_timer    = 0.0f;

        // ── Grid display ──────────────────────────────────────────────
        bool  show_editor = true;

        // ── Cell editor ───────────────────────────────────────────────
        int  selected_cell = -1;
        bool editor_dirty  = false;

        static constexpr size_t EDITOR_BUF = 1 << 20;  // 1 MB
        std::vector<char> editor_buf;

        char load_path[512] = "";
        char save_dir[512]  = "/home/adrien/Programmation/Projets/BioEvo/apps/EvoX/data/evox_experiment";

        Level()
        {
            base_config = LevelConfig::from_json(
                json::parse(R"({
                    "experiment_name": "None",
                    "cell_size": 80.0,
                    "cells": [
                        "void",
                        "void",
                        "void",
                        "void"
                    ]
                })")
            );
            config      = base_config;
            editor_buf.resize(EDITOR_BUF, '\0');
        }

        void start_simulation(back::tree::Tree<std::string>::Node* node)
        {
            config_directory = node->getPath();
            config = get_level_config(config_directory / "config.json");

            universe.set_config(config, config_directory);

            selected_cell = -1;
            editor_buf[0] = '\0';
            editor_dirty  = false;
            running       = false;
            step_timer    = 0.0f;
        }

        LevelConfig get_level_config(fs::path cfg_path)
        {

            std::ifstream file(cfg_path);
            if (!file.is_open()) {
                std::cerr << "Error: could not open file: " << cfg_path << "\n";
                return base_config;
            }

            try {
                // Parse directly from the stream — no need to read into a string first
                json j = json::parse(file);
                LevelConfig cfg = LevelConfig::from_json(j);
                return cfg;
            } catch (const json::parse_error& e) {
                std::cerr << "JSON parse error: " << e.what() << "\n";
            } catch (const json::out_of_range& e) {
                std::cerr << "Missing field: " << e.what() << "\n";
            } catch (const json::type_error& e) {
                std::cerr << "Wrong field type: " << e.what() << "\n";
            }
            return base_config;
        }

        void exit_simulation()
        {
            config  = base_config;
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

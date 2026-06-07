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
        struct ProgteinEntry { std::string name; int id = 0; std::string body; };
        struct GeneEntry     { int id = 0;                   std::string body; };
        struct EvoxSummary   {
            std::vector<ProgteinEntry> progteins;
            std::vector<GeneEntry>     genes;
        };

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
    
        static EvoxSummary parse_evox_summary(const char* text)
        {
            EvoxSummary out;
            std::istringstream ss(text);
            std::string line;
            bool in_dna = false, in_prog = false, in_gene = false;
            ProgteinEntry cur_p;
            GeneEntry     cur_g;

            // read first whitespace-delimited token from a trimmed line, uppercased
            auto kw_of = [](const std::string& tr) {
                std::string kw; std::istringstream ls(tr); ls >> kw;
                for (auto& c : kw) c = (char)std::toupper((unsigned char)c);
                return kw;
            };
            // everything after the keyword (safe even if len >= tr.size())
            auto after_kw = [](const std::string& tr, size_t kw_len) {
                return (tr.size() > kw_len) ? tr.substr(kw_len) : std::string{};
            };

            while (std::getline(ss, line)) {
                // trim leading whitespace
                size_t f = line.find_first_not_of(" \t");
                std::string tr = (f != std::string::npos) ? line.substr(f) : std::string{};
                std::string kw = kw_of(tr);

                if (!in_dna && !in_prog && !in_gene) {
                    if (kw == "PROGTEIN") {
                        in_prog = true;  cur_p = {};
                        std::istringstream ls(after_kw(tr, kw.size()));
                        std::string tok;
                        while (ls >> tok) {
                            if (tok.rfind("id=", 0) == 0)
                                try { cur_p.id = std::stoi(tok.substr(3)); } catch (...) {}
                            else if (cur_p.name.empty() && !tok.empty() && tok[0] != '#')
                                cur_p.name = tok;
                        }
                    } else if (kw == "DNA") {
                        in_dna = true;
                    }
                } else if (in_prog) {
                    if (kw == "END") { out.progteins.push_back(cur_p);  in_prog = false; }
                    else             { if (!cur_p.body.empty()) cur_p.body += '\n'; cur_p.body += line; }
                } else if (in_dna && !in_gene) {
                    if (kw == "END") { in_dna = false; }
                    else if (kw == "GENE") {
                        in_gene = true;  cur_g = {};
                        std::istringstream ls(after_kw(tr, kw.size()));
                        std::string tok;
                        while (ls >> tok)
                            if (tok.rfind("id=", 0) == 0)
                                try { cur_g.id = std::stoi(tok.substr(3)); } catch (...) {}
                    }
                } else if (in_gene) {
                    if (kw == "END") { out.genes.push_back(cur_g);  in_gene = false; }
                    else             { if (!cur_g.body.empty()) cur_g.body += '\n'; cur_g.body += line; }
                }
            }
            return out;
        }

    };

} // namespace back::level

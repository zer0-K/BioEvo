#pragma once

#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "level/level_config.hpp"
// EvoX engine — included via relative path from apps/EvoX/back/
#include "../../../src/Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../src/Models/EvoAlgos/XASMAlgo/EvoX.hpp"
#include "../../../src/Models/EvoAlgos/XASMAlgo/Parsing/EvoXParser.hpp"
#include "../../../src/Entities/EntityVoid.hpp"
#include "../../../src/General/Place.hpp"
#include "../../../src/Utils/Constants.hpp"

namespace fs = std::filesystem;

namespace back::evox_universe
{
    struct EvoXUniverse
    {
        back::level::LevelConfig config;
        fs::path config_directory;

        int  nb_cells          = 4;
        int  max_nb_instr_exec = 1 << 22;
        int  data_stack_init   = 150;
        int  step_count        = 0;
        bool built             = false;
        bool needs_rebuild     = false;

        std::string last_error;

        std::vector<back::level::CellConfig>    cells;
        std::shared_ptr<UniverseEvoAlgos>       universe;

        void set_config(back::level::LevelConfig config, fs::path cfg_dir)
        {
            config_directory = cfg_dir;
            this->config = config;
            reset();
        }

        // (Re-)allocate cells from config and clear universe.
        void reset()
        {
            nb_cells = config.cells.size();

            cells.resize(nb_cells);
            for(int i=0; i<nb_cells; i++) 
            {
                std::string cell_name = config.cells[i];
                if(cell_name == "void")
                {
                    set_cell_void(i);
                }
                else
                {
                    fs::path cell_path = config_directory / cell_name;
                    load_cell_from_file(i, cell_path.string());
                }
            }

            universe.reset();
            built         = false;
            needs_rebuild = false;
            step_count    = 0;
            last_error.clear();
        }

        void set_cell_evox(int idx, const std::string& evox_str)
        {
            if (idx < 0 || idx >= (int)cells.size()) return;
            cells[idx].is_void  = false;
            cells[idx].evox_str = evox_str;
            needs_rebuild       = true;
        }

        void set_cell_void(int idx)
        {
            if (idx < 0 || idx >= (int)cells.size()) return;
            cells[idx].is_void  = true;
            cells[idx].evox_str.clear();
            needs_rebuild       = true;
        }

        bool load_cell_from_file(int idx, const std::string& path)
        {
            std::ifstream f(path);
            if (!f.good()) { last_error = "Cannot open: " + path; return false; }
            std::ostringstream ss;
            ss << f.rdbuf();
            set_cell_evox(idx, ss.str());
            last_error.clear();
            return true;
        }

        // Build (or rebuild) the live UniverseEvoAlgos
        bool build()
        {
            last_error.clear();
            try {
                std::vector<sp_place> places(cells.size());
                for (int i = 0; i < (int)cells.size(); i++) {
                    if (!cells[i].is_void) {
                        // Write to a named temp file so EvoXParser can read it.
                        std::string tmp = "/tmp/evoxapp_cell_" + std::to_string(i) + ".evox";
                        { std::ofstream f(tmp); f << cells[i].evox_str; }
                        auto algo = std::make_shared<EvoX>("algo_" + std::to_string(i));
                        algo->init();
                        algo->set_max_nb_instr_exec(max_nb_instr_exec);
                        algo->set_data_at(99, data_stack_init);
                        algo->set_body(EvoXParser::parse_body(tmp));
                        places[i] = std::make_shared<Place>(algo, i);
                    } else {
                        auto ev = std::make_shared<EntityVoid>("void_" + std::to_string(i));
                        ev->init();
                        places[i] = std::make_shared<Place>(ev, i);
                    }
                }
                universe = std::make_shared<UniverseEvoAlgos>("evox_ui", places);
                universe->link_universe_functions_to_individuals();
                step_count    = 0;
                built         = true;
                needs_rebuild = false;
                return true;
            } catch (const std::exception& e) {
                last_error = std::string("Build error: ") + e.what();
                universe.reset();
                built = false;
                return false;
            }
        }

        // Advance one step. Rebuilds first if needed. Returns false on error.
        bool step()
        {
            if (!built || needs_rebuild)
            {
                if (!build())
                    return false;
            }
            try
            {
                universe->exec();
                step_count++;
                _sync_cells_from_universe();
                last_error.clear();
                return true;
            } 
            catch (const std::exception& e)
            {
                last_error = std::string("Step error: ") + e.what();
                return false;
            }
        }

        // Write current cell state to <dir>/step_NNN/cell_N.{evox,void}.
        void save_snapshot(const std::string& dir)
        {
            std::ostringstream ss;
            ss << dir << "/step_" << std::setw(3) << std::setfill('0') << step_count;
            std::string step_dir = ss.str();
            fs::create_directories(step_dir);
            for (int i = 0; i < (int)cells.size(); i++) {
                std::string base = step_dir + "/cell_" + std::to_string(i);
                if (!cells[i].is_void) {
                    std::ofstream f(base + ".evox");
                    f << cells[i].evox_str;
                } else {
                    std::ofstream f(base + ".void");
                }
            }
        }

    private:
        void _sync_cells_from_universe()
        {
            if (!universe)
                return;
            
            auto places = universe->get_places();
            for (int i = 0; i < (int)cells.size() && i < (int)places.size(); i++)
            {
                auto entity = places[i]->get_entity();
                if (entity->is_type(EVOX))
                {
                    auto algo         = std::dynamic_pointer_cast<EvoX>(entity);
                    cells[i].is_void  = false;
                    cells[i].evox_str = algo->body_to_evox_string();
                }
                else
                {
                    cells[i].is_void  = true;
                    cells[i].evox_str.clear();
                }
            }
        }
    };

} // namespace back::evox_universe

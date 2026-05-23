/**
 * sandbox-runner  <dir> <nb_steps> <max_nb_instr_exec> [<data_stack_init>=150]
 *
 * Expects in <dir>:
 *   cell_0.evox, cell_1.evox, ...  (EvoX body)
 *   cell_N.void                    (empty place placeholder)
 *   Scanning stops at the first gap in the index sequence.
 *
 * Writes after each step:
 *   <dir>/step_000/cell_N.evox  or  <dir>/step_000/cell_N.void
 *
 * Progress lines ("step N done") are flushed to stdout so the caller
 * (Python subprocess) can stream them.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

#include "../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../Models/EvoAlgos/XASMAlgo/EvoX.hpp"
#include "../../Models/EvoAlgos/XASMAlgo/Parsing/EvoXParser.hpp"
#include "../../Entities/EntityVoid.hpp"
#include "../../General/Place.hpp"
#include "../../Utils/Constants.hpp"

namespace fs = std::filesystem;

static bool file_exists(const std::string& path)
{
    std::ifstream f(path);
    return f.good();
}

static void write_file(const std::string& path, const std::string& content)
{
    std::ofstream f(path);
    f << content;
}

int main(int argc, char* argv[])
{
    if (argc < 4) {
        std::cerr << "Usage: sandbox-runner <dir> <nb_steps> <max_nb_instr_exec> [<data_stack_init>]\n";
        return 1;
    }

    std::string dir             = argv[1];
    int nb_steps                = std::stoi(argv[2]);
    int max_nb_instr_exec       = std::stoi(argv[3]);
    int data_stack_init         = (argc >= 5) ? std::stoi(argv[4]) : 150;

    // ── detect cells ────────────────────────────────────────────────────────
    int nb_cells = 0;
    while (true) {
        std::string base = dir + "/cell_" + std::to_string(nb_cells);
        if (file_exists(base + ".evox") || file_exists(base + ".void"))
            ++nb_cells;
        else
            break;
    }

    if (nb_cells == 0) {
        std::cerr << "No cell_N.evox or cell_N.void files found in " << dir << "\n";
        return 1;
    }

    std::cout << "Detected " << nb_cells << " cells\n" << std::flush;

    // ── build places ────────────────────────────────────────────────────────
    std::vector<sp_place> places(nb_cells);
    for (int i = 0; i < nb_cells; i++) {
        std::string evox_path = dir + "/cell_" + std::to_string(i) + ".evox";
        if (file_exists(evox_path)) {
            auto algo = std::make_shared<EvoX>("algo_" + std::to_string(i));
            algo->init();
            algo->set_max_nb_instr_exec(max_nb_instr_exec);
            algo->set_data_at(99, data_stack_init);
            auto body = EvoXParser::parse_body(evox_path);
            algo->set_body(body);
            places[i] = std::make_shared<Place>(algo, i);
        } else {
            auto ev = std::make_shared<EntityVoid>("void_" + std::to_string(i));
            ev->init();
            places[i] = std::make_shared<Place>(ev, i);
        }
    }

    // ── build universe ───────────────────────────────────────────────────────
    auto universe = std::make_shared<UniverseEvoAlgos>("sandbox", places);
    universe->link_universe_functions_to_individuals();

    // ── run steps ────────────────────────────────────────────────────────────
    for (int step = 0; step < nb_steps; step++) {
        universe->exec();

        // step_NNN directory
        std::ostringstream ss;
        ss << dir << "/step_" << std::setw(3) << std::setfill('0') << step;
        std::string step_dir = ss.str();
        fs::create_directories(step_dir);

        for (int i = 0; i < nb_cells; i++) {
            auto entity     = universe->get_places()[i]->get_entity();
            std::string base = step_dir + "/cell_" + std::to_string(i);
            if (entity->is_type(EVOX)) {
                auto algo = std::dynamic_pointer_cast<EvoX>(entity);
                write_file(base + ".evox", algo->body_to_evox_string());
            } else {
                write_file(base + ".void", "");
            }
        }

        std::cout << "step " << step << " done\n" << std::flush;
    }

    return 0;
}

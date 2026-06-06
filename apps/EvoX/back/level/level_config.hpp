#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace back::level
{
    struct CellConfig {
        bool        is_void  = true;
        std::string evox_str;
    };

    class LevelConfig
    {
    public:
        std::string             experiment_name;
        int                     nb_cells;
        float                   cell_size;
        std::vector<std::string> cells;

        static LevelConfig from_json(const json& j)
        {
            LevelConfig l;

            j.at("experiment_name") .get_to(l.experiment_name);
            j.at("cell_size")       .get_to(l.cell_size);
            j.at("cells")           .get_to(l.cells);

            l.nb_cells = l.cells.size();

            return l;
        }
        
        json to_json() const
        {
            return {
                {"experiment_name", experiment_name},
                {"cell_size",       cell_size},
                {"cells",           cells}
            };
        }
    };

} // namespace back::level

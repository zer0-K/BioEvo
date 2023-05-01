#include "config.hpp"

std::vector<std::string> get_config_names()
{
    std::string path = "../config";

    std::vector<std::string> cfgs = std::vector<std::string>();

    for (const auto & entry : std::filesystem::directory_iterator(path))
        cfgs.push_back(entry.path());

    return cfgs;
}

std::string get_config_content(std::string cfg_path)
{
    std::ifstream t(cfg_path);
    return std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
}
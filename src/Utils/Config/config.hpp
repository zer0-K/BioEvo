#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <streambuf>
#include <iostream>

extern std::vector<std::string> get_config_names();
extern std::string get_config_content(std::string);
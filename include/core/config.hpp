#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <borealis.hpp>

#include "helper.hpp"

namespace Config {
    bool ReadConfigForCache(std::string cfgfile);
    bool ReadConfigForDownload(std::string cfgfile);
    std::string ReadConfig(std::string cfgfile, std::string content);
    void WriteConfig(std::string cfgfile, std::string what, std::string value);
    bool ConfigExists();
    void CheckCreateConfig();
};

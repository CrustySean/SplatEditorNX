#include "config.hpp"

using json = nlohmann::json;

bool Config::ReadConfigForCache(std::string cfgfile) {
    try {
	    std::ifstream f(cfgfile, std::ifstream::in);

        json j;
        f >> j;

        std::string contentS = j.at("cache");

        bool contentB = (contentS == "true");
        return contentB;

    } catch (std::exception& e) {
        brls::Logger::error("[Config] {}", e.what());
    }

    return false;
}

bool Config::ReadConfigForDownload(std::string cfgfile) {
    try {
	    std::ifstream f(cfgfile, std::ifstream::in);

        json j;
        f >> j;

        std::string contentS = j.at("images");

        bool contentB = (contentS == "true");
        return contentB;

    } catch (std::exception& e) {
        brls::Logger::error("[Config] {}", e.what());
    }

    return false;
}

std::string Config::ReadConfig(std::string cfgfile, std::string content) {
    try {
	    std::ifstream f(cfgfile, std::ifstream::in);

        json j;
        f >> j;

        std::string contentS = j.at(content);

        return contentS;

    } catch (std::exception& e) {
        brls::Logger::error("[Config] {}", e.what());
    }

    return NULL;
}

void Config::WriteConfig(std::string cfgfile, std::string what, std::string value) {
    try {
        nlohmann::json json;
        json[what] = value;

        std::ofstream file(g_defaultPath + "/cfg.json");
        file << std::setw(4) << json << std::endl;

    } catch (std::exception& e) {
        brls::Logger::error("[Exception] {}", e.what());
    }
}

bool Config::ConfigExists() {
    if (!std::filesystem::exists(g_defaultPath + "/cfg.json")) {
        return false;
    } else {
        return true;
    }
}

void Config::CheckCreateConfig() {
    if (!ConfigExists()) {
        WriteConfig(g_defaultPath + "/cfg.json", "cache", "false");
    }
}

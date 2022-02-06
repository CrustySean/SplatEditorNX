#pragma once

#include <filesystem>
#include <borealis.hpp>
#include <future>
#include <nlohmann/json.hpp>

#include "downloader.hpp"
#include "config.hpp"
#include "helper.hpp"
#include "utilities.hpp"

#include "Loading_Overlay.hpp"

namespace Cache {
    void DownloadImage(const std::string& url, const std::string& path);
    void CreateDirectory();
    void Init();
    std::string isInRangeWeapons(u32 id);
    std::string isInRangeSub(u32 id);
    std::string isInRangeSpecials(u32 id);
    std::string isInRangeClothes(u32 id);
    std::string isInRangeHead(u32 id);
    std::string isInRangeShoes(u32 id);

    void DownloadNecessary();

    bool tryGetImage(const std::string& type, const std::string& weapon, u32 id);
};

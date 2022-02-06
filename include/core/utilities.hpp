#pragma once

#include <cstdint>
#include <iostream>
#include <borealis.hpp>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iomanip>
#include <fstream>

#include <memory>
#include <string>
#include <stdexcept>

#include <cstdlib>
#include <future>

#include "splat/SaveDataFactory.h"
#include "helper.hpp"

namespace Utilities {

    /* From Flagbrew's Checkpoint. */
    Result OpenSaveData(FsFileSystem* fileSystem, u64 titleID, AccountUid userID);
    int MountSave(FsFileSystem fs);
    void UnmountSave(void);
    void CopyFile(const std::string& srcPath, const std::string& dstPath);

    void CreateDirectories();
    void CopySave(u64 TitleID);

    void Init();

    void AddokAndOpen(brls::Dialog* dialog);
    void InjectSave();

    std::string DumpAppControl(u64 titleId);
    bool isValidInRangeString(std::unordered_map<std::string, int> map, std::string key);

    void Test();

    bool HasWifi();

    void splatsave(std::string path);
    void UpdateApp();

    void RemoveFromString(std::string &p, const std::string &remove);

    template<typename ... Args>
    std::string format_string(const std::string& format, Args ... args)
    {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
        
        if (size_s <= 0 )
        { 
            throw std::runtime_error("Error during formatting."); 
        }

        auto size = static_cast<size_t>(size_s);
        auto buf = std::make_unique<char[]>(size);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1);
    }

};

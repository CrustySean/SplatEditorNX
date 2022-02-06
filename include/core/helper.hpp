#pragma once
#include <memory>
#include <switch.h>
#include <codecvt>
#include <locale>
#include <string>
#include <filesystem>
#include <borealis.hpp>

#include "main_activity.hpp"

inline static const std::string g_defaultPath = "sdmc:/SplatEditor";
inline static const std::string g_editedPath = g_defaultPath + "/Edited";
inline static const std::string g_savePath = g_defaultPath + "/Saves";

template<class T>
inline static auto& getInstance(T) {
    T s_Instance;
    return s_Instance;
}

inline std::string g_currentFile = "";
inline u64 TitleID = 0;
brls::Dialog* createLoadingDialog(std::string text);
inline int hasBeenSelected = 0;
inline bool hasBeenModified = false;

inline bool hasInitialized = false;
inline bool initWireFrame = false;
inline bool isModified = false;

inline u32 value = 0;

std::string char16_to_string(const char16_t* s16);
long char16_to_long(const char16_t* s16);
int char16_to_int(const char16_t* s16);

auto utf8toutf16(std::string source);
std::string utf16toutf8(char16_t* source);

void PushMainView();
void PushRomtypeView();

auto ConvertUTFStr(char16_t str16);

inline u32 g_username_dotsize;

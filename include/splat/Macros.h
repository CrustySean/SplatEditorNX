#pragma once
#include <cstdint>
#include "helper.hpp"
#include "cache.hpp"
#include "utilities.hpp"

#include <borealis.hpp>

#define STRINGIFY(x) #x
#define COMBINE(x, y) x##y

using namespace brls::literals;

#define S_CREATECELL(cellname, booleanCell, titlestr, titleID, imgpath)                                                                                 \
    cellname->setThumbnail(imgpath);                                                                                                                    \
    cellname->title->setText(titlestr);                                                                                                                 \
    cellname->setSelected(booleanCell);                                                                                                                 \
    cellname->registerClickAction([this](brls::View* view) {                                                                                            \
        booleanCell = !booleanCell;                                                                                                                     \
        this->cellname->setSelected(booleanCell);                                                                                                       \
        if  (booleanCell) {                                                                                                                             \
            brls::Dialog* f = createLoadingDialog("Copying save...");                                                                                   \
            f->open();                                                                                                                                  \
            brls::Threading::sync([f]() {                                                                                                               \
                f->close();                                                                                                                             \
            });                                                                                                                                         \
            brls::Threading::start();                                                                                                                   \
        }                                                                                                                                               \
        return true;                                                                                                                                    \
    });                                                                                                                                                 \

#define S_CREATEEDITORITEM(cellname, titlestr, function, savefile, SavedatacmnMemb, keyboardHint, keyboardMaxLengthInput, imgpath)                      \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [savefile](u32 num) {                                                                                          \
        savefile->SavedatacmnMemb = num;                                                                                                                \
    },                                                                                                                                                  \
    keyboardHint, keyboardMaxLengthInput, 0, imgpath);                                                                                                  \

#define S_CREATEWEAPON(cellname, titlestr, function, savefile, SavedatacmnMemb, keyboardHint, keyboardMaxLengthInput)                                   \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [this, savefile](u32 num) {                                                                                    \
        savefile->SavedatacmnMemb = num;                                                                                                                \
        cellname->setThumbnail(Cache::isInRangeWeapons(num));                                                                                           \
    },                                                                                                                                                  \
    keyboardHint, keyboardMaxLengthInput, 0);                                                                                                           \

#define S_CREATESUB(cellname, titlestr, function, savefile, SavedatacmnMemb, keyboardHint, keyboardMaxLengthInput)                                      \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [this, savefile](u32 num) {                                                                                    \
        savefile->SavedatacmnMemb = num;                                                                                                                \
        cellname->setThumbnail(Cache::isInRangeSub(num));                                                                                               \
    },                                                                                                                                                  \
    keyboardHint, keyboardMaxLengthInput, 0);                                                                                                           \

#define S_CREATESPECIALS(cellname, titlestr, function, savefile, SavedatacmnMemb, keyboardHint, keyboardMaxLengthInput)                                 \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [this, savefile](u32 num) {                                                                                    \
        savefile->SavedatacmnMemb = num;                                                                                                                \
        cellname->setThumbnail(Cache::isInRangeSpecials(num));                                                                                          \
    },                                                                                                                                                  \
    keyboardHint, keyboardMaxLengthInput, 0);                                                                                                           \

#define S_CREATECLOTHES(cellname, titlestr, function, savefile, SavedatacmnMemb, keyboardHint, keyboardMaxLengthInput)                                  \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [this, savefile](u32 num) {                                                                                    \
        savefile->SavedatacmnMemb = num;                                                                                                                \
        cellname->setThumbnail(Cache::isInRangeClothes(num));                                                                                           \
    },                                                                                                                                                  \
    keyboardHint, keyboardMaxLengthInput, 0);                                                                                                           \

#define S_CREATEHEAD(cellname, titlestr, function, savefile, SavedatacmnMemb, keyboardHint, keyboardMaxLengthInput)                                     \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [this, savefile](u32 num) {                                                                                    \
        savefile->SavedatacmnMemb = num;                                                                                                                \
        cellname->setThumbnail(Cache::isInRangeHead(num));                                                                                              \
    },                                                                                                                                                  \
    keyboardHint, keyboardMaxLengthInput, 0);                                                                                                           \

#define S_CREATESHOES(cellname, titlestr, function, savefile, SavedatacmnMemb, keyboardHint, keyboardMaxLengthInput)                                     \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [this, savefile](u32 num) {                                                                                    \
        savefile->SavedatacmnMemb = num;                                                                                                                \
        cellname->setThumbnail(Cache::isInRangeShoes(num));                                                                                              \
    },                                                                                                                                                  \
    keyboardHint, keyboardMaxLengthInput, 0);                                                                                                           \


#define S_CREATEEDITORITEM_UNKNOWN(cellname, titlestr, function, savefile, SavedatacmnMemb, keyboardHint, keyboardMaxLengthInput)                       \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [this, savefile](u32 num) {                                                                                    \
        savefile->SavedatacmnMemb = num;                                                                                                                \
    },                                                                                                                                                  \
    keyboardHint, keyboardMaxLengthInput, 0, "sdmc:/SplatEditor/cache/unknown.png");                                                                    \


#define S_CREATEEDITORITEMFOR(cellname, titlestr, function, savefile, forvar, SavedatacmnMemb, keyboardHint, keyboardMaxLengthInput)                    \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [savefile, forvar](u32 num) {                                                                                  \
        savefile->SavedatacmnMemb = num;                                                                                                                \
    },                                                                                                                                                  \
    keyboardHint, keyboardMaxLengthInput);                                                                                                              \

#define S_CREATEEDITORITEMFORWITHCHARKEYBOARD(cellname, titlestr, function, savefile, forvar, SavedatacmnMemb, keyboardHint)                            \
    cellname->init(                                                                                                                                     \
        std::string(titlestr), function, [savefile, forvar](std::string str) {                                                                          \
        utf16toutf8(savefile->SavedatacmnMemb) = str;                                                                                                   \
    },                                                                                                                                                  \
    keyboardHint);                                                                                                                                      \

#define S_CREATESPLATFUNC(name, value)                                                                                                                  \
    auto get_ ## name() {                                                                                                                               \
        return value;                                                                                                                                   \
    }                                                                                                                                                   \

#define S_EDITSAVEMEMBER(savedatamember, value)                                                                                                         \
    savedatamember = value;                                                                                                                             \

#define APPEND_IMPL(x, y) x ## y
#define APPEND(x, y) APPEND_IMPL(x, y)

#define _LOOKUP_SUFFIX ToStringLookup
#define _GETTER_SUFFIX ToString

#define _ENUM_LOOKUP_NAME(name)                                                                                                                         \
    APPEND(name, _LOOKUP_SUFFIX)
#define _ENUM_GETTER_NAME(name)                                                                                                                         \
    APPEND(name, _GETTER_SUFFIX)

#define ENUM_MAKE_TOSTRINGLOOKUP(name)                                                                                                                  \
    static const char* _ENUM_LOOKUP_NAME(name)[]

#define ENUM_MAKE_TOSTRINGGETTER(name)                                                                                                                  \
    const char* _ENUM_GETTER_NAME(name)(int e) {                                                                                                        \
        if(e >= name##_End) {                                                                                                                           \
            return NULL;                                                                                                                                \
        }                                                                                                                                               \
        return _ENUM_LOOKUP_NAME(name)[(int)e];                                                                                                         \
    }

#define ENUM_TOSTRING(type, e)  \
    _ENUM_GETTER_NAME(type)(e)

/* From the dolphin-emu project */
/// Textually concatenates two tokens. The double-expansion is required by the C preprocessor.
#define CONCAT2(x, y) DO_CONCAT2(x, y)
#define DO_CONCAT2(x, y) x##y

// helper macro to properly align structure members.
// Calling INSERT_PADDING_BYTES will add a new member variable with a name like "pad121",
// depending on the current source line to make sure variable names are unique.
#define INSERT_PADDING_BYTES(num_bytes) uint8_t CONCAT2(pad, __LINE__)[(num_bytes)];
#define INSERT_PADDING_WORDS(num_words) uint32_t CONCAT2(pad, __LINE__)[(num_words)];

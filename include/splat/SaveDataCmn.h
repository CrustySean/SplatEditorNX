#pragma once

#include <array>

#include "Macros.h"

class SaveDataCmnC {
   public:
    typedef struct {
        CommonStructs::Weapon weapon;
        u64 lastEquippedTime;
        u32 freshness;
        u32 flagColor;
        using WeaponFlags = std::array<u32, 66>;
        WeaponFlags weaponFlags;
        u32 isNew;
        INSERT_PADDING_BYTES(4);
    } HaveWeapon;
    static_assert(sizeof(HaveWeapon) == 0x130, "SaveDataCmn::HaveWeapon must be 0x130 bytes long");

    typedef struct {
        CommonStructs::Gear gear;
        u64 lastEquippedTime;
        u32 isNew;
        INSERT_PADDING_BYTES(4);
    } HaveGear;
    static_assert(sizeof(HaveGear) == 0x30, "SaveDataCmn::HaveGear must be 0x30 bytes long");

    typedef struct {
        s32 id;
        u32 amount;
    } HaveSkillChip;
    static_assert(sizeof(HaveSkillChip) == 8, "SaveDataCmn::HaveSkillChip must be 8 bytes long");

    typedef struct {
        s32 id;
        s32 boostedId;
        u32 amount;
    } HaveBoostTicket;
    static_assert(sizeof(HaveBoostTicket) == 0xC, "SaveDataCmn::HaveBoostTicket must be 0xC bytes long");

    typedef struct {
        // inkling customizations
        s32 inklingPlayerModelType;
        s32 inklingPlayerHairId;
        s32 inklingPlayerBottomId;
        s32 inklingPlayerSkinColorId;
        s32 inklingPlayerEyeColorId;
        CommonStructs::Weapon equippedWeapon;
        INSERT_PADDING_BYTES(4);
        using WeaponInventory = std::array<HaveWeapon, 0x100>;
        WeaponInventory weaponInventory;
        s32 equippedShoesId;
        s32 equippedClothesId;
        s32 equippedHeadGearId;
        INSERT_PADDING_BYTES(4);
        using GearKindInventory = std::array<HaveGear, 0x200>;
        GearKindInventory shoeInventory;
        GearKindInventory clothesInventory;
        GearKindInventory headGearInventory;
        using SkillChipInventory = std::array<HaveSkillChip, 0x40>;
        SkillChipInventory skillChipInventory;
        using BoostTicketInventory = std::array<HaveBoostTicket, 0x40>;
        BoostTicketInventory ticketInventory;
        u32 hasSeenTutorial;
        // control options
        float handheldStickSensitivity;
        float handheldMotionSensitivity;
        u8 handheldMotionEnabled;
        u8 handheldMotionInvertY;
        u8 handheldMotionInvertX;
        INSERT_PADDING_BYTES(0x41);
        float detachedStickSensitivity;
        float detachedMotionSensitivity;
        u8 detachedMotionEnabled;
        u8 detachedMotionInvertY;
        u8 detachedMotionInvertX;
        INSERT_PADDING_BYTES(0x41);
        u32 onlinePlayPenalty[4];  // TODO: Look into this
        u64 penaltyEndTime;
        INSERT_PADDING_BYTES(0x188);
        u32 money;
        u32 seaSnails;
        INSERT_PADDING_BYTES(0x108);
        u64 saveTime;
        INSERT_PADDING_BYTES(0x54);
        u8 colorLock;
        u8 showPlazaPosts;
        INSERT_PADDING_BYTES(0x2BEA);
        // octoling customizations
        s32 octolingPlayerModelType;
        s32 octolingPlayerHairId;
        s32 octolingPlayerBottomId;
        s32 octolingPlayerSkinColorId;
        s32 octolingPlayerEyeColorId;
        s32 isOctoling;
        INSERT_PADDING_BYTES(0x2D24);
    } SaveDataCmnData;
    static_assert(sizeof(SaveDataCmnData) == 0x2B210, "SaveDataCmnData must be 0x2B210 bytes long");

    virtual ~SaveDataCmnC();
    u64 unk0;
};

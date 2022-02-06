#pragma once
#include <cstdint>
#include "Macros.h"
#include "CommonStructs.h"
#include <cuchar>

class SaveDataVssC {
    public:
        typedef struct {
            float Power;
            float Rd; // Rating Deviation
            float Volatility;
            float Unknown;
        } MMR_;
        static_assert(sizeof(MMR_) == 0x10, "SaveDataVss::MMR must be 0x10 bytes long");
        typedef struct {
            uint64_t LastUpdated; // Unix time localized to current time zone
            uint64_t CurrentSeasonStart; // Unix time GMT
            uint64_t NextSeasonStart; // Unix time GMT
            MMR_ MMR1;
            MMR_ MMR2;
            INSERT_PADDING_BYTES(0x10);
        } UdemaeX;
        static_assert(sizeof(UdemaeX) == 0x48, "SaveDataVss::UdemaeX must be 0x48 bytes long");
        typedef struct {
            char16_t Name[0xA];
            INSERT_PADDING_BYTES(0x14);
        } PlayerSystemInfo;
        static_assert(sizeof(PlayerSystemInfo) == 0x28, "SaveDataVss::PlayerSystemInfo must be 0x28 bytes long");
        typedef struct {
            INSERT_PADDING_BYTES(0x16);
            char16_t Name[0xA];
            INSERT_PADDING_BYTES(0x12);
            uint32_t PlayerModelType;
            uint32_t PlayerHairId;
            uint32_t PlayerSkinColorId;
            uint32_t PlayerEyeColorId;
            CommonStructs::Weapon Weapon;
            INSERT_PADDING_BYTES(8);
            CommonStructs::Gear Shoes;
            CommonStructs::Gear Clothes;
            CommonStructs::Gear HeadGear;
            uint32_t Tank;
            uint32_t PlayerBottomId;
            INSERT_PADDING_BYTES(0x10);
            uint32_t Level;
            uint32_t Stars;
            uint32_t RainmakerRank;
            uint32_t SplatZonesRank;
            uint32_t TowerControlRank;
            uint32_t ClamBlitzRank;
            INSERT_PADDING_BYTES(0xAC);
        } PlayerInfo;
        static_assert(sizeof(PlayerInfo) == 0x1A0, "SaveDataVss::PlayerInfo must be 0x1A0 bytes long");
        typedef struct {
            uint64_t Player1NexUid;
            PlayerSystemInfo Player1SystemInfo;
            uint64_t Player2NexUid;
            PlayerSystemInfo Player2SystemInfo;
            uint64_t Player3NexUid;
            PlayerSystemInfo Player3SystemInfo;
            uint64_t Player4NexUid;
            PlayerSystemInfo Player4SystemInfo;
            uint64_t PlayerCount;
        } TagPlayers;
        static_assert(sizeof(TagPlayers) == 0xC8, "SaveDataVss::TagPlayers must be 0xC8 bytes long");
        typedef struct {
            uint64_t Time;
            INSERT_PADDING_BYTES(8);
            TagPlayers Players;
            MMR_ MMR[6];
            INSERT_PADDING_BYTES(2);
        } TagScore;
        static_assert(sizeof(TagScore) == 0x140, "SaveDataVss::TagScore must be 0x140 bytes long");
        typedef struct {
            uint32_t Level;
            uint32_t Exp;
            uint32_t Stars;
            INSERT_PADDING_BYTES(0x8);
            uint32_t TicketBoostRemaining;
            // Ranks
            uint32_t RainmakerRank;
            INSERT_PADDING_BYTES(8);
            uint32_t SplatZonesRank;
            INSERT_PADDING_BYTES(8);
            uint32_t TowerControlRank;
            INSERT_PADDING_BYTES(8);
            uint32_t ClamBlitzRank;
            INSERT_PADDING_BYTES(8);
            INSERT_PADDING_BYTES(0x18);
            MMR_ MMR[0x20]; // 0 = Turf War, 1 = Rainmaker, 2 = Splat Zones, 3 = Tower Control, 4 = Clam Blitz
            TagScore PairLeagueResults[0x20];
            TagScore TeamLeagueResults[0x20];
            INSERT_PADDING_BYTES(0xC50);
            PlayerInfo PlazaNPCs[0x19];
            UdemaeX UdemaeX1[6];
            UdemaeX UdemaeX2[6];
            INSERT_PADDING_BYTES(0x3CA0);
        } Section;
        static_assert(sizeof(Section) == 0xC750, "SaveDataVss::Section must be 0xC750 bytes long");
};

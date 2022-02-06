#pragma once
#include <cstdint>
#include "Macros.h"

class CommonStructs {
    public:
        typedef struct {
            uint32_t Main;
            uint32_t Sub;
            uint32_t Special;
            uint32_t InkTurfed;
        } Weapon;
        static_assert(sizeof(Weapon) == 0x10, "CommonStructs::Weapon must be 0x10 bytes long");
    	typedef struct {
            uint32_t Id;
            uint32_t Level;
            uint32_t Slots;
            uint32_t MainAbility;
            uint32_t SubAbility1;
            uint32_t SubAbility2;
            uint32_t SubAbility3;
            uint32_t Exp;
        } Gear;
        static_assert(sizeof(Gear) == 0x20, "CommonStructs::Gear must be 0x20 bytes long");
};

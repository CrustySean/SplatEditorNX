#pragma once

#include <switch.h>
#include <borealis.hpp>
#include <iomanip>

#include "utilities.hpp"

/* This work was done by WerWolv, see README for details. */

namespace ExceptionHandler {
    static void PrintInfo(ThreadExceptionDump *ctx);
    void unwindStack(u64 *outStackTrace, s32 *outStackTraceSize, size_t maxStackTraceSize, u64 currFp);
    u64 getHomebrewBaseAddress();

    template<typename T>
    std::string toHexString(T value, size_t width = sizeof(T) * 2) {
        std::stringstream sstream;
        sstream << std::uppercase << std::setfill('0') << std::setw(width) << std::hex << value;

        return sstream.str();
    }
}

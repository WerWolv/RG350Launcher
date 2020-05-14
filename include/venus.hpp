#pragma once

#include <cstdint>
#include "types.hpp"

#include "result.hpp"
#include "results.hpp"

/* == Utils == */

#define UNUSED(x) ((void)(x))

/* == Config == */

namespace cfg {

    constexpr u32 ScreenWidth = 640;
    constexpr u32 ScreenHeight = 480;
    constexpr bool ShowFPS = true;

    constexpr enum class Platform {
        Desktop, OpenDingux
    } Platform = Platform::Desktop;

}
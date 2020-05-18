#pragma once

#include "types.hpp"

#include "result.hpp"
#include "results.hpp"

/* == Utils == */

#define UNUSED(x) ((void)(x))

/* == Config == */

namespace cfg {

    constexpr s32 ScreenWidth = 640;
    constexpr s32 ScreenHeight = 480;
    constexpr bool ShowFPS = true;

    constexpr enum class Platform {
        Desktop, OpenDingux
    } Platform = Platform::Desktop;

}
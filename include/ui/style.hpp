#pragma once

#include <venus.hpp>

namespace ui {

    struct Style {
        static constexpr u32 Padding = 10;
        static constexpr u32 ScrollingDuration = 200; // ms

        struct Header {
            static constexpr u32 Height = 25;
            static constexpr u32 ShadowOffset = 5;
            static constexpr u32 PageButtonWidth = 80;
            static constexpr u32 TabDotsSpacing = 12;
        };

    };

}
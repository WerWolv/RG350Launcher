#pragma once

#include "ui/view/view.hpp"

#include "ui/view/header.hpp"
#include "ui/view/image.hpp"
#include "ui/view/image_button.hpp"
#include "ui/view/grid.hpp"

namespace gui::page {

    class PageHomebrew : public ui::view::View {
    public:
        PageHomebrew();

    private:
        void draw(NVGcontext *vg) override;
        void layout() override;

        void drawWave(NVGcontext *vg, NVGcolor startColor, u32 offset, float frequency, u32 amplitude, u32 phase);

    };

}
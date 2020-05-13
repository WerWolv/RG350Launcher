#pragma once

#include "view.hpp"

namespace ui::view {

    class DebugRectangle : public View {
    public:
        DebugRectangle(NVGcolor color);

        void draw(NVGcontext *vg) override;

    private:
        NVGcolor m_color;
    };

}
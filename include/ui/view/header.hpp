#pragma once

#include "view.hpp"

namespace ui::view {

    class Header : public View {
    public:
        Header();
        ~Header();

        void draw(NVGcontext *vg) override;
        void layout() override;

    private:
        int m_background = 0;
        NVGpaint m_backgroundPaint;
    };

}
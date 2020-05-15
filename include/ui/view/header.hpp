#pragma once

#include "view.hpp"

namespace ui::view {

    class Header : public View {
    public:
        Header();
        ~Header();

        void draw(NVGcontext *vg) override;
        void layout() override;

        void setSelectedTab(s32 numTabs, s32 selectedTab);

    private:
        int m_background = 0;
        NVGpaint m_backgroundPaint;

        s32 m_numTabs;
        s32 m_selectedTab;

        void drawPill(NVGcontext *vg, s32 x, s32 y, const char *string);
        void drawTabDots(NVGcontext *vg);
    };

}
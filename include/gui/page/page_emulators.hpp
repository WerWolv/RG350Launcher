#pragma once

#include "ui/view/view.hpp"

#include "ui/view/header.hpp"
#include "ui/view/image.hpp"
#include "ui/view/button.hpp"
#include "ui/view/grid.hpp"

namespace gui::page {

    class PageEmulators : public ui::view::View {
    public:
        PageEmulators();

    private:
        ui::view::Grid m_grid;
        ui::view::Image m_backgroundImage;
        ui::view::Header m_header;

        void draw(NVGcontext *vg) override;
        void layout() override;

        View* getDefaultFocus() override;

    };

}
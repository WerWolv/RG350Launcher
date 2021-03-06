#pragma once

#include "ui/view/view.hpp"

#include "ui/view/header.hpp"
#include "ui/view/image.hpp"
#include "ui/view/image_button.hpp"
#include "ui/view/grid.hpp"

namespace gui::page {

    class PageEmulators : public ui::view::View {
    public:
        PageEmulators();

    private:
        ui::view::Grid m_grid;
        ui::view::Image m_backgroundImage;

        void draw(NVGcontext *vg) override;
        void layout() override;

        View* getDefaultFocus() override;

    };

}
#pragma once

#include "ui/view/view.hpp"

#include "ui/view/header.hpp"
#include "ui/view/image.hpp"
#include "ui/view/image_button.hpp"
#include "ui/view/grid.hpp"

namespace gui::page {

    class PageSettings : public ui::view::View {
    public:
        PageSettings();

    private:

        void draw(NVGcontext *vg) override;
        void layout() override;

        View* getDefaultFocus() override;

    };

}
#pragma once

#include "ui/view/view.hpp"

namespace ui::view {

    class Button : public View {
    public:
        Button();

        void draw(NVGcontext *vg) override;
        void layout() override;

        View* getDefaultFocus();
        View* getNextFocus(const FocusDirection direction);
    };

}
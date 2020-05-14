#pragma once

#include "ui/view/view.hpp"
#include "ui/view/image.hpp"

#include <string>

namespace ui::view {

    class ImageButton : public View {
    public:
        ImageButton(const std::string &path);

        void draw(NVGcontext *vg) override;
        void layout() override;

        View* getDefaultFocus();
        View* getNextFocus(const FocusDirection direction);

    private:
        Image m_image;
    };

}
#include "ui/view/image_button.hpp"

namespace ui::view {

    ImageButton::ImageButton(const std::string &path) : View(), m_image(path) {

    }

    void ImageButton::draw(NVGcontext *vg) {
        NVGpaint shadowPaint = nvgBoxGradient(vg, getX(), getY(), getWidth(), getHeight(), 3, 10, nvgRGBA(0x20, 0x20, 0x20, 0xFF), nvgRGBA(0x20, 0x20, 0x20, 0x00));

        nvgBeginPath(vg);
        nvgFillPaint(vg, shadowPaint);
        nvgRoundedRect(vg, getX() - 5, getY() - 5, getWidth() + 10, getHeight() + 10, 3);
        nvgFill(vg);

        this->m_image.frame(vg);
    }

    void ImageButton::layout() {
        this->m_image.setBoundaries(getX(), getY(), getWidth(), getHeight());
        this->m_image.layout();
    }

    View * ImageButton::getDefaultFocus() {
        return this;
    }

    View * ImageButton::getNextFocus(const FocusDirection direction) {
        return this->getParent()->getNextFocus(direction);
    }

}
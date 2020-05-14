#include "ui/view/image_button.hpp"

namespace ui::view {

    ImageButton::ImageButton(const std::string &path) : View(), m_image(path) {

    }

    void ImageButton::draw(NVGcontext *vg) {
        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGB(0xFF, 0xFF, 0xFF));
        nvgRoundedRect(vg, getX(), getY(), getWidth(), getHeight(), 3);
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
#include "ui/view/button.hpp"

namespace ui::view {

    Button::Button() : View() {

    }

    void Button::draw(NVGcontext *vg) {
        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGB(0xFF, 0xFF, 0xFF));
        nvgRoundedRect(vg, getX(), getY(), getWidth(), getHeight(), 5);
        nvgFill(vg);
    }

    void Button::layout() {

    }

    View * Button::getDefaultFocus() {
        return this;
    }

    View * Button::getNextFocus(const FocusDirection direction) {
        return this->getParent()->getNextFocus(direction);
    }

}
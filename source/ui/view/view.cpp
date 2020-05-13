#include "ui/view/view.hpp"

namespace ui::view {

    void View::setBoundaries(s32 x, s32 y, s32 width, s32 height) {
        this->m_x = x;
        this->m_y = y;
        this->m_width = width;
        this->m_height = height;
    }

    void View::frame(NVGcontext *vg) {
        this->draw(vg);

        if (this->isFocused())
            this->drawHighlight(vg);
    }

    s32 View::getX() {
        return this->m_x;
    }

    s32 View::getY() {
        return this->m_y;
    }

    s32 View::getWidth() {
        return this->m_width;
    }

    s32 View::getHeight() {
        return this->m_height;
    }

    void View::setFocused(bool focused) {
        this->m_focused = focused;
    }

    bool View::isFocused() {
        return this->m_focused;
    }

    void View::drawHighlight(NVGcontext *vg) {

    }

}


#include "ui/view/debug_rectangle.hpp"

namespace ui::view {

    DebugRectangle::DebugRectangle(NVGcolor color) : View(), m_color(color) {

    }

    void DebugRectangle::draw(NVGcontext *vg) {
        nvgBeginPath(vg);
        nvgFillColor(vg, this->m_color);
        nvgRect(vg, getX(), getY(), getWidth(), getHeight());
        nvgFill(vg);
    }

}
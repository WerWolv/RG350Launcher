#include "ui/view/view.hpp"

#include "ui/gui.hpp"

#include <SDL.h>

namespace ui::view {

    void View::setBoundaries(s32 x, s32 y, s32 width, s32 height) {
        this->m_x = x;
        this->m_y = y;
        this->m_width = width;
        this->m_height = height;
    }

    void View::frame(NVGcontext *vg) {
        const bool focused = this->isFocused();

        if (focused)
            this->drawHighlightBackground(vg);

        this->draw(vg);

        if (focused)
            this->drawHighlight(vg);
    }

    void View::setParent(View * const parent) {
        this->m_parent = parent;
    }

    View* const View::getParent() const {
        if (this->m_parent == nullptr) {
            printf("Parent of %s is nullptr!\n", typeid(this).name());
            std::abort();
        }

        return this->m_parent;
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

    bool View::isFocused() const {
        return this->m_focused;
    }

    void View::drawHighlightBackground(NVGcontext *vg) {
        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGB(0xFF, 0xFF, 0xFF));
        nvgRect(vg, getX(), getY(), getWidth(), getHeight());
        nvgFill(vg);
    }

    void View::drawHighlight(NVGcontext *vg) {
        nvgSave(vg);
        nvgResetScissor(vg);

        float cornerRadius = 3;

        const s32 strokeWidth = 3;
        const s32 shadowOffset = 10;
        const NVGcolor transparent = nvgRGBA(0,0,0,0);

        const NVGcolor highlightColor1 = nvgRGB(13, 182, 213);
        const NVGcolor highlightColor2 = nvgRGB(80, 239, 217);

        s32 x      = getX() - strokeWidth / 2;
        s32 y      = getY() - strokeWidth / 2;
        s32 width  = getWidth() + strokeWidth;
        s32 height = getHeight() + strokeWidth;

        NVGpaint shadowPaint = nvgBoxGradient(vg,
                                              x, y + 2,
                                              width, height,
                                              cornerRadius * 2, 10,
                                              nvgRGBA(0, 0, 0, 0x80), transparent);

        nvgBeginPath(vg);
        nvgRect(vg, x - shadowOffset, y - shadowOffset,
                width + shadowOffset * 2, height + shadowOffset * 3);
        nvgRoundedRect(vg, x, y, width, height, cornerRadius);
        nvgPathWinding(vg, NVG_HOLE);
        nvgFillPaint(vg, shadowPaint);
        nvgFill(vg);

        // Border
        const double highlightSpeed = 350.0;
        u32 currTick = SDL_GetTicks();
        float gradientX = (cos((double)currTick / highlightSpeed / 3.0) + 1.0) / 2.0;
        float gradientY = (sin((double)currTick / highlightSpeed / 3.0) + 1.0) / 2.0;
        float color     = (sin((double)currTick / highlightSpeed * 2.0) + 1.0) / 2.0;

        NVGcolor pulsationColor = nvgRGBAf((color * highlightColor1.r) + (1 - color) * highlightColor2.r,
                                        (color * highlightColor1.g) + (1 - color) * highlightColor2.g,
                                        (color * highlightColor1.b) + (1 - color) * highlightColor2.b,
                                        1.0F);

        NVGcolor borderColor = highlightColor2;
        borderColor.a        = 0.5f;

        NVGpaint border1Paint = nvgRadialGradient(vg,
                                                  x + gradientX * width, y + gradientY * height,
                                                  strokeWidth * 10, strokeWidth * 40,
                                                  borderColor, transparent);

        NVGpaint border2Paint = nvgRadialGradient(vg,
                                                  x + (1 - gradientX) * width, y + (1 - gradientY) * height,
                                                  strokeWidth * 10, strokeWidth * 40,
                                                  borderColor, transparent);

        nvgBeginPath(vg);
        nvgStrokeColor(vg, pulsationColor);
        nvgStrokeWidth(vg, strokeWidth);
        nvgRoundedRect(vg, x, y, width, height, cornerRadius);
        nvgStroke(vg);

        nvgBeginPath(vg);
        nvgStrokePaint(vg, border1Paint);
        nvgStrokeWidth(vg, strokeWidth);
        nvgRoundedRect(vg, x, y, width, height, cornerRadius);
        nvgStroke(vg);

        nvgBeginPath(vg);
        nvgStrokePaint(vg, border2Paint);
        nvgStrokeWidth(vg, strokeWidth);
        nvgRoundedRect(vg, x, y, width, height, cornerRadius);
        nvgStroke(vg);

        nvgRestore(vg);
    }

    View* View::getDefaultFocus() {
        return NON_FOCUSABLE;
    }

    View* View::getNextFocus(const FocusDirection direction) {
        return NON_FOCUSABLE;
    }

    void View::onInput(ui::Button button) {
        if (this->getParent() != nullptr)
            this->getParent()->onInput(button);
    }

}


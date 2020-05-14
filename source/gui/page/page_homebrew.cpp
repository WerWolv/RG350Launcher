#include "gui/page/page_homebrew.hpp"

#include <cmath>
#include <SDL.h>

namespace gui::page {

    PageHomebrew::PageHomebrew() : View() {
    }

    void PageHomebrew::drawWave(NVGcontext *vg, NVGcolor startColor, u32 offset, float frequency, u32 amplitude, u32 phase) {
        NVGcolor endColor = startColor;
        endColor.r -= 0.2F;
        endColor.g -= 0.2F;
        endColor.b -= 0.2F;

        NVGpaint paint = nvgLinearGradient(vg, 0, getHeight() - (offset + amplitude), 0, getHeight(), startColor, endColor);

        nvgBeginPath(vg);
        nvgFillPaint(vg, paint);
        nvgMoveTo(vg, getX(), getHeight() - offset);
        for (s32 x = 0; x <= getWidth(); x++) {
            nvgLineTo(vg, getX() + x, getHeight() - (offset + std::sin(nvgDegToRad(x * frequency + phase)) * amplitude));
        }
        nvgLineTo(vg, getX() + getWidth(), getHeight());
        nvgLineTo(vg, getX(), getHeight());
        nvgLineTo(vg, getX(), getHeight() - offset);
        nvgFill(vg);
    }

    void PageHomebrew::draw(NVGcontext *vg) {
        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGB(45, 45, 50));
        nvgRect(vg, getX(), getY(), getWidth(), getHeight());
        nvgFill(vg);

        this->drawWave(vg, nvgRGB(73, 103, 169), 100, 0.5, 20, 120 + SDL_GetTicks() / 20.0F);
        this->drawWave(vg, nvgRGB(66, 154, 159), 90, 0.3, 15, 240 + SDL_GetTicks() / 20.0F);
        this->drawWave(vg, nvgRGB(96, 204, 204), 80, 0.1, 10, 360 + SDL_GetTicks() / 20.0F);
    }

    void PageHomebrew::layout() {

    }

}


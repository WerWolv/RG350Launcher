#include "ui/view/header.hpp"

#include <ctime>
#include <chrono>
#include <string>

#include "ui/application.hpp"

using namespace std::string_literals;

namespace ui::view {

    Header::Header() : View() {

    }

    Header::~Header() {

    }

    void Header::drawPill(NVGcontext *vg, s32 x, s32 y, const char *string) {
        nvgFontFace(vg, "regular");
        nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
        nvgFontSize(vg, 14);

        float bounds[4];
        nvgTextBounds(vg, x, y, string, nullptr, bounds);

        NVGpaint pillShadow = nvgBoxGradient(vg, x, y, bounds[2] - bounds[0] + 10, bounds[3] - bounds[1] + 5, 10, 5, nvgRGBA(0x00, 0x00, 0x00, 0xFF), nvgRGBA(0xFF, 0xFF, 0xFF, 0x00));
        nvgBeginPath(vg);
        nvgFillPaint(vg, pillShadow);
        nvgRoundedRect(vg, x - 5, y - 5, bounds[2] - bounds[0] + 20, bounds[3] - bounds[1] + 15, 10);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGB(0xE0, 0xE0, 0xE0));
        nvgRoundedRect(vg, x, y, bounds[2] - bounds[0] + 10, bounds[3] - bounds[1] + 5, 10);
        nvgFill(vg);

        nvgFillColor(vg, nvgRGB(0x00, 0x00, 0x00));
        nvgBeginPath(vg);
        nvgText(vg, x + (bounds[2] - bounds[0] + 10) / 2, y + (bounds[3] - bounds[1] + 5) / 2 + 1, string, nullptr);
    }

    void Header::draw(NVGcontext *vg) {
        NVGpaint bottomShadow = nvgLinearGradient(vg, getX(), getY(), getX(), Style::Header::Height + Style::Header::ShadowOffset, nvgRGBA(0x00, 0x00, 0x00, 0xFF), nvgRGBA(0xFF, 0xFF, 0xFF, 0x00));

        nvgBeginPath(vg);
        nvgFillPaint(vg, bottomShadow);
        nvgRect(vg, getX(), getY(), getWidth(), Style::Header::Height + Style::Header::ShadowOffset);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGBA(0xEF, 0xEF, 0xEF, 0xFF));
        nvgRect(vg, getX(), getY(), getWidth(), Style::Header::Height);
        nvgFill(vg);

        if (Application::isButtonHeld(Button::PageLeft)) {
            NVGpaint shadow = nvgLinearGradient(vg, getX() + Style::Header::PageButtonWidth - 4, getY(), getX() + Style::Header::PageButtonWidth + 4, getY(), nvgRGBA(0xFF, 0xFF, 0xFF, 0x00), nvgRGBA(0xA0, 0xA0, 0xA0, 0xFF));

            nvgBeginPath(vg);
            nvgFillColor(vg, nvgRGBA(0xE0, 0xE0, 0xE0, 0xFF));
            nvgRect(vg, getX(), getY(), Style::Header::PageButtonWidth, Style::Header::Height);
            nvgFill(vg);

            nvgBeginPath(vg);
            nvgFillPaint(vg, shadow);
            nvgRect(vg, getX() + Style::Header::PageButtonWidth - 4, getY(), 4, Style::Header::Height);
            nvgFill(vg);
        } else {
            NVGpaint shadow = nvgLinearGradient(vg, getX() + Style::Header::PageButtonWidth, getY(), getX() + Style::Header::PageButtonWidth + 4, getY(), nvgRGBA(0xA0, 0xA0, 0xA0, 0xFF), nvgRGBA(0xFF, 0xFF, 0xFF, 0x00));

            nvgBeginPath(vg);
            nvgFillPaint(vg, shadow);
            nvgRect(vg, getX() + Style::Header::PageButtonWidth, getY(), 4, Style::Header::Height);
            nvgFill(vg);
        }

        if (Application::isButtonHeld(Button::PageRight)) {
            NVGpaint shadow = nvgLinearGradient(vg, getWidth() - Style::Header::PageButtonWidth, getY(), getWidth() - Style::Header::PageButtonWidth + 4, getY(), nvgRGBA(0xA0, 0xA0, 0xA0, 0xFF), nvgRGBA(0xFF, 0xFF, 0xFF, 0x00));

            nvgBeginPath(vg);
            nvgFillColor(vg, nvgRGBA(0xE0, 0xE0, 0xE0, 0xFF));
            nvgRect(vg, getWidth() - Style::Header::PageButtonWidth, getY(), Style::Header::PageButtonWidth, Style::Header::Height);
            nvgFill(vg);

            nvgBeginPath(vg);
            nvgFillPaint(vg, shadow);
            nvgRect(vg, getWidth() - Style::Header::PageButtonWidth, getY(), 4, Style::Header::Height);
            nvgFill(vg);
        } else {
            NVGpaint shadow = nvgLinearGradient(vg, getWidth() - Style::Header::PageButtonWidth - 4, getY(), getWidth() - Style::Header::PageButtonWidth, getY(), nvgRGBA(0xFF, 0xFF, 0xFF, 0x00), nvgRGBA(0xA0, 0xA0, 0xA0, 0xFF));

            nvgBeginPath(vg);
            nvgFillPaint(vg, shadow);
            nvgRect(vg, getWidth() - Style::Header::PageButtonWidth - 4, getY(), 4, Style::Header::Height);
            nvgFill(vg);
        }

        time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        struct tm *now = std::localtime(&time);

        char timeString[6];
        char dateString[11];
        sprintf(timeString, "%02d:%02d", now->tm_hour, now->tm_min);
        sprintf(dateString, "%02d.%02d.%02d", now->tm_mday, now->tm_mon + 1, 1900 + now->tm_year);

        nvgFillColor(vg, nvgRGB(0x00, 0x00, 0x00));
        nvgFontFace(vg, "regular");
        nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

        nvgBeginPath(vg);
        nvgFontSize(vg, 20);
        nvgText(vg, getWidth() / 2, 20, timeString, nullptr);
        nvgBeginPath(vg);
        nvgFontSize(vg, 15);
        nvgText(vg, getWidth() / 2, 45, dateString, nullptr);


        u32 lOffset = Style::Header::PageButtonWidth / 2;
        u32 rOffset = Style::Header::PageButtonWidth / 2;

        if (Application::isButtonHeld(Button::PageLeft))
            lOffset -= 4;
        if (Application::isButtonHeld(Button::PageRight))
            rOffset -= 4;

        nvgBeginPath(vg);
        nvgFontSize(vg, 20);
        nvgText(vg, lOffset, Style::Header::Height / 2, "L", nullptr);
        nvgBeginPath(vg);
        nvgFontSize(vg, 20);
        nvgText(vg, getWidth() - rOffset, Style::Header::Height / 2, "R", nullptr);

        drawPill(vg, getX() + 5, getHeight() - 25, timeString);
        drawPill(vg, getX() + 60, getHeight() - 25, "69%");

    }

    void Header::layout() {

    }

}


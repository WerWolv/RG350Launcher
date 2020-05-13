#include "ui/view/header.hpp"

#include <ctime>
#include <chrono>
#include <string>

using namespace std::string_literals;

namespace ui::view {

    Header::Header() : View() {

    }

    Header::~Header() {

    }

    void Header::draw(NVGcontext *vg) {
        NVGpaint shadow = nvgLinearGradient(vg, 0, 0, 0, 70, nvgRGBA(0x00, 0x00, 0x00, 0xFF), nvgRGBA(0xFF, 0xFF, 0xFF, 0x00));


        nvgBeginPath(vg);
        nvgFillPaint(vg, shadow);
        nvgRect(vg, 0, 0, ScreenWidth, 75);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGBA(0xF0, 0xF0, 0xFF, 0xFF));
        nvgRect(vg, 0, 0, ScreenWidth, 60);
        nvgFill(vg);

        nvgFillColor(vg, nvgRGB(0x00, 0x00, 0x00));
        nvgFontSize(vg, 20);
        nvgFontFace(vg, "regular");
        nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
        nvgBeginPath(vg);

        time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        struct tm *now = std::localtime(&time);

        std::string timeString = std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min);
        std::string dateString = std::to_string(now->tm_mday) + "." + std::to_string(now->tm_mon + 1) + "." + std::to_string(1900 + now->tm_year);

        nvgText(vg, ScreenWidth / 2, 20, timeString.c_str(), nullptr);
        nvgBeginPath(vg);
        nvgFontSize(vg, 15);
        nvgText(vg, ScreenWidth / 2, 45, dateString.c_str(), nullptr);

        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGB(0xFF, 0xFF, 0xFF));
        nvgRoundedRect(vg, 25, 75, 200, 100, 5);
        nvgFill(vg);

    }

    void Header::layout() {

    }

}


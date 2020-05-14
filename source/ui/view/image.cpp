#include "ui/view/image.hpp"
#include "ui/application.hpp"

namespace ui::view {

    Image::Image(const std::string &path) : View() {
        this->m_texture = nvgCreateImage(Application::getNVGContext(), path.c_str(), 0);
    }

    Image::Image(u8 *data, size_t size) : View() {
        this->m_texture = nvgCreateImageMem(Application::getNVGContext(), 0, data, size);
    }

    Image::Image(u8 *data, u32 width, u32 height) : View() {
        this->m_texture = nvgCreateImageRGBA(Application::getNVGContext(), width, height, 0, data);
    }

    Image::~Image() {
        nvgDeleteImage(Application::getNVGContext(), this->m_texture);
        this->m_texture = -1;
    }

    void Image::draw(NVGcontext *vg) {
        nvgBeginPath(vg);
        nvgFillPaint(vg, this->m_paint);
        nvgRect(vg, getX(), getY(), getWidth(), getHeight());
        nvgFill(vg);
    }

    void Image::layout() {
        this->m_paint = nvgImagePattern(Application::getNVGContext(), getX(), getY(), getX() + getWidth(), getY() + getHeight(), 0, this->m_texture, 1.0F);
    }

}


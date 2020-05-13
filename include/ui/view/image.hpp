#pragma once

#include "view.hpp"

namespace ui::view {

    class Image : public View {
    public:
        Image(const std::string &path);
        Image(u8 *data, size_t size);
        Image(u8 *data, u32 width, u32 height);

        ~Image();

        void draw(NVGcontext *vg) override;
        void layout() override;

    private:
        int m_texture = -1;
        NVGpaint m_paint;
    };

}
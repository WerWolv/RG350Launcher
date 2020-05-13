#pragma once

#include <venus.hpp>

#include <nanovg.h>
#include <list>
#include <memory>

namespace ui::view {

    class View {
    public:
        View() = default;

        template<typename T, typename ... Args>
        T& addChild(Args... args) {
            this->m_children.push_back(std::make_unique<T>(std::forward(args...)));

            return this->m_children.back();
        }

        virtual void draw(NVGcontext *vg) = 0;
        virtual void layout() = 0;

        virtual void drawHighlight(NVGcontext *vg);

        void frame(NVGcontext *vg);

        void setBoundaries(s32 x, s32 y, s32 width, s32 height);

        s32 getX();
        s32 getY();
        s32 getWidth();
        s32 getHeight();

        void setFocused(bool focused);
        bool isFocused();

    private:
        bool m_focused = false;
        s32 m_x, m_y;
        s32 m_width, m_height;

        std::list<std::unique_ptr<View>> m_children;
    };

}
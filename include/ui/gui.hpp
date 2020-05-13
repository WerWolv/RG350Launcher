#pragma once

#include <venus.hpp>

#include <nanovg.h>
#include <memory>
#include <utility>

#include "ui/view/view.hpp"

namespace ui {

    class Gui {
    public:
        Gui();

        void draw(NVGcontext *vg);
        void layout();

    protected:
        template<typename T, typename ... Args>
        T& setRootView(Args... args) {
            this->m_rootView = std::make_unique<T>(args...);
            this->m_rootView->setBoundaries(0, 0, ScreenWidth, ScreenHeight);

            return static_cast<T&>(*this->m_rootView);
        }
    private:
        std::unique_ptr<view::View> m_rootView;
    };

}
#pragma once

#include <venus.hpp>

#include <nanovg.h>
#include <memory>
#include <utility>

#include "ui/view/view.hpp"

namespace ui {

    enum class Button {
        None,
        Up,
        Down,
        Left,
        Right,
        Ok,
        Back,
        PageLeft,
        PageRight
    };

    class Gui {
    public:
        Gui();

        void draw(NVGcontext *vg);
        void layout();

    protected:
        template<typename T, typename ... Args>
        T& setRootView(Args... args) {
            this->m_rootView = std::make_unique<T>(args...);
            this->m_rootView->setBoundaries(0, 0, cfg::ScreenWidth, cfg::ScreenHeight);

            this->m_currFocus = this->m_rootView->getDefaultFocus();

            if (this->m_currFocus != nullptr)
                this->m_currFocus->setFocused(true);

            return static_cast<T&>(*this->m_rootView);
        }
    private:
        friend class Application;

        std::unique_ptr<view::View> m_rootView;
        view::View *m_currFocus = nullptr;

        void navigate(Button button);
    };

}
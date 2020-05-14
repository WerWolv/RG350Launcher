#include "ui/gui.hpp"

namespace ui {

    Gui::Gui() {

    }

    void Gui::draw(NVGcontext *vg) {
        this->m_rootView->draw(vg);
    }

    void Gui::layout() {
        this->m_rootView->setBoundaries(0, 0, cfg::ScreenWidth, cfg::ScreenHeight);
        this->m_rootView->layout();
    }

    void Gui::navigate(Button button) {
        if (this->m_currFocus == nullptr) {
            this->m_currFocus = this->m_rootView->getDefaultFocus();

            if (this->m_currFocus != nullptr)
                this->m_currFocus->setFocused(true);

            return;
        }

        ui::view::View *nextFocus = nullptr;

        switch (button) {
            case Button::Up:
                nextFocus = this->m_currFocus->getNextFocus(view::FocusDirection::Up);
                break;
            case Button::Down:
                nextFocus = this->m_currFocus->getNextFocus(view::FocusDirection::Down);
                break;
            case Button::Left:
                nextFocus = this->m_currFocus->getNextFocus(view::FocusDirection::Left);
                break;
            case Button::Right:
                nextFocus = this->m_currFocus->getNextFocus(view::FocusDirection::Right);
                break;
            default: break;
        }

        if (nextFocus == nullptr || nextFocus == this->m_currFocus)
            ; // Play shake animation
        else {
            if (this->m_currFocus != nullptr)
                this->m_currFocus->setFocused(false);
            this->m_currFocus = nextFocus;
            this->m_currFocus->setFocused(true);
        }

        if (this->m_currFocus != nullptr)
            this->m_currFocus->onInput(button);
    }

}


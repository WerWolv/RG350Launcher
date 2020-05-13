#include "ui/gui.hpp"

namespace ui {

    Gui::Gui() {

    }

    void Gui::draw(NVGcontext *vg) {
        this->m_rootView->draw(vg);
    }

    void Gui::layout() {
        this->m_rootView->setBoundaries(0, 0, ScreenWidth, ScreenHeight);
        this->m_rootView->layout();
    }

}


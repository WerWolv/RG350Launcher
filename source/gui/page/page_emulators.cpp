#include "gui/page/page_emulators.hpp"

namespace gui::page {

    PageEmulators::PageEmulators() : View(), m_backgroundImage("bg.png"), m_header() {

    }

    void PageEmulators::draw(NVGcontext *vg) {
        this->m_backgroundImage.draw(vg);
        this->m_header.draw(vg);
    }

    void PageEmulators::layout() {
        this->m_backgroundImage.setBoundaries(getX(), getY(), getWidth(), getHeight());
        this->m_header.setBoundaries(getX(), getY(), getWidth(), getHeight());

        this->m_backgroundImage.layout();
        this->m_header.layout();
    }

}


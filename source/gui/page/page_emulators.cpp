#include "gui/page/page_emulators.hpp"

namespace gui::page {

    PageEmulators::PageEmulators() : View(), m_grid(3, 80), m_backgroundImage("bg.png"), m_header() {
        CHILD(this->m_grid);
        CHILD(this->m_backgroundImage);
        CHILD(this->m_header);

        this->m_grid.addItem<ui::view::Button>();
        this->m_grid.addItem<ui::view::Button>();
        this->m_grid.addItem<ui::view::Button>();
        this->m_grid.addItem<ui::view::Button>();
        this->m_grid.addItem<ui::view::Button>();
        this->m_grid.addItem<ui::view::Button>();
        this->m_grid.addItem<ui::view::Button>();
        this->m_grid.addItem<ui::view::Button>();
        this->m_grid.addItem<ui::view::Button>();
        this->m_grid.addItem<ui::view::Button>();

    }

    void PageEmulators::draw(NVGcontext *vg) {
        this->m_backgroundImage.frame(vg);
        this->m_header.frame(vg);
        this->m_grid.frame(vg);
    }

    void PageEmulators::layout() {
        this->m_grid.setBoundaries(0, 75, getWidth(), getHeight() - 75);
        this->m_backgroundImage.setBoundaries(getX(), getY(), getWidth(), getHeight());
        this->m_header.setBoundaries(getX(), getY(), getWidth(), getHeight());

        this->m_grid.layout();
        this->m_backgroundImage.layout();
        this->m_header.layout();
    }

    ui::view::View* PageEmulators::getDefaultFocus() {
        return this->m_grid.getDefaultFocus();
    }

}


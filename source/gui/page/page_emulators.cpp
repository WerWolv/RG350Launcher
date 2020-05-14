#include "gui/page/page_emulators.hpp"

namespace gui::page {

    PageEmulators::PageEmulators() : View(), m_grid(3, 0.545), m_backgroundImage("bg.png") {
        CHILD(this->m_grid);
        CHILD(this->m_backgroundImage);

        this->m_grid.addItem<ui::view::ImageButton>("NES.png");
        this->m_grid.addItem<ui::view::ImageButton>("SNES.png");
        this->m_grid.addItem<ui::view::ImageButton>("GB.png");
        this->m_grid.addItem<ui::view::ImageButton>("");
        this->m_grid.addItem<ui::view::ImageButton>("");
        this->m_grid.addItem<ui::view::ImageButton>("");
        this->m_grid.addItem<ui::view::ImageButton>("");
        this->m_grid.addItem<ui::view::ImageButton>("");
        this->m_grid.addItem<ui::view::ImageButton>("");

    }

    void PageEmulators::draw(NVGcontext *vg) {
        this->m_backgroundImage.frame(vg);
        this->m_grid.frame(vg);
    }

    void PageEmulators::layout() {
        this->m_grid.setBoundaries(getX(), 75, getWidth(), getHeight() - 75);
        this->m_backgroundImage.setBoundaries(getX(), getY(), getWidth(), getHeight());

        this->m_grid.layout();
        this->m_backgroundImage.layout();
    }

    ui::view::View* PageEmulators::getDefaultFocus() {
        return this->m_grid.getDefaultFocus();
    }

}


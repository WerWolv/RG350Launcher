#include "gui/page/page_emulators.hpp"

#include "ui/style.hpp"

namespace gui::page {

    PageEmulators::PageEmulators() : View(), m_grid(2, 0.545), m_backgroundImage("res/bg.png") {
        CHILD(this->m_grid);
        CHILD(this->m_backgroundImage);

        this->m_grid.addItem<ui::view::ImageButton>("res/icons/NES.png");
        this->m_grid.addItem<ui::view::ImageButton>("res/icons/SNES.png");
        this->m_grid.addItem<ui::view::ImageButton>("res/icons/GB.png");
        this->m_grid.addItem<ui::view::ImageButton>("res/icons/GBC.png");
        this->m_grid.addItem<ui::view::ImageButton>("res/icons/GBA.png");
        this->m_grid.addItem<ui::view::ImageButton>("res/icons/PCE.png");
        this->m_grid.addItem<ui::view::ImageButton>("res/icons/PS1.png");

    }

    void PageEmulators::draw(NVGcontext *vg) {
        this->m_backgroundImage.frame(vg);
        this->m_grid.frame(vg);
    }

    void PageEmulators::layout() {
        this->m_grid.setBoundaries(getX(), ui::Style::Header::Height + ui::Style::Header::ShadowOffset + ui::Style::Padding,
                                   getWidth(), getHeight() - ui::Style::Header::Height + ui::Style::Header::ShadowOffset + ui::Style::Padding);
        this->m_backgroundImage.setBoundaries(getX(), getY(), getWidth(), getHeight());

        this->m_grid.layout();
        this->m_backgroundImage.layout();
    }

    ui::view::View* PageEmulators::getDefaultFocus() {
        return this->m_grid.getDefaultFocus();
    }

}


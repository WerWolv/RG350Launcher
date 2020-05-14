#pragma once

#include "ui/gui.hpp"

#include "gui/page/page_emulators.hpp"
#include "gui/page/page_homebrew.hpp"
#include "gui/page/page_settings.hpp"

#include "ui/view/page_switcher.hpp"

namespace gui {

    class GuiHome : public ui::Gui {
    public:
        GuiHome() {
            auto &pageSwitcher = this->setRootView<ui::view::PageSwitcher>();

            pageSwitcher.addPage<gui::page::PageEmulators>();
            pageSwitcher.addPage<gui::page::PageHomebrew>();
            pageSwitcher.addPage<gui::page::PageSettings>();

            this->resetFocus();
        }
    };

}
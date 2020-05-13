#pragma once

#include "ui/gui.hpp"
#include "gui/page/page_emulators.hpp"

namespace gui {

    class GuiHome : public ui::Gui {
    public:
        GuiHome() {
            this->setRootView<gui::page::PageEmulators>();
        }

    };

}
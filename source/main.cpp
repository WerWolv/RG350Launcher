#include <venus.hpp> // TODO: Temporary project name, find better one

#include "ui/application.hpp"
#include "gui/gui_home.hpp"

int main(int argc, char **argv) {
    UNUSED(argc); UNUSED(argv);

    ui::Application application;
    if (Result res = application.getInitResult(); res.failed()) {
        printf("Window initialization failed! %s\n", res.getString().c_str());
        return EXIT_FAILURE;
    }

    application.registerFont("regular", "Roboto-Regular.ttf");

    gui::GuiHome guiHome;
    application.pushGui(guiHome);

    while (application.loop());

    return EXIT_SUCCESS;
}
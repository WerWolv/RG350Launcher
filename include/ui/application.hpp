#pragma once

#include <SDL.h>

#include <list>
#include <vector>

#include "gui.hpp"

namespace ui {

    class Application {
    public:
        Application();
        ~Application();

        static NVGcontext* getNVGContext() {
            return Application::s_vgCtx;
        }

        const Result& getInitResult() const;

        void pushGui(Gui &gui);
        void pushGui(Gui &&gui);
        void goBack();

        void registerFont(const std::string &fontName, const std::string &path);
        void registerFont(const std::string &fontName, u8 *data, size_t size, bool freeMemory = false);

        bool loop();

    private:
        std::list<Gui> m_guis;

        u32 m_currFps = 60;

        static inline SDL_Window *s_window = nullptr;
        static inline SDL_GLContext s_glCtx = nullptr;
        static inline NVGcontext *s_vgCtx = nullptr;

        bool m_running = true;
        Result m_initResult = 0;

        void handleEvents();
        void draw();
    };

}
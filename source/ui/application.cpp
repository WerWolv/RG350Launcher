#include "ui/application.hpp"

#include <SDL.h>
#include <glad\gl.h>
#include <nanovg.h>

#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

namespace ui {

    constexpr u32 TargetFPS = 60;
    constexpr u32 TargetFrameTime = 1000.0F / TargetFPS;

    Application::Application() {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            this->m_initResult = ResultSDLInitFailed;
            return;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);


        Application::s_window = SDL_CreateWindow("RG350M Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_OPENGL);
        if (Application::s_window == nullptr) {
            this->m_initResult = ResultSDLWindowCreationFailed;
            return;
        }

        Application::s_glCtx = SDL_GL_CreateContext(Application::s_window);
        if (Application::s_glCtx == nullptr) {
            this->m_initResult = ResultSDLGLCreationFailed;
            return;
        }

        SDL_GL_MakeCurrent(Application::s_window, Application::s_glCtx);
        gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress));

        Application::s_vgCtx = nvgCreateGL3(NVG_STENCIL_STROKES | NVG_ANTIALIAS);
    }

    Application::~Application() {
        nvgDeleteGL3(Application::s_vgCtx);

        SDL_GL_DeleteContext(Application::s_glCtx);
        SDL_DestroyWindow(Application::s_window);
        SDL_Quit();

        Application::s_vgCtx = nullptr;
        Application::s_glCtx = nullptr;
        Application::s_window = nullptr;
    }

    const Result& Application::getInitResult() const {
        return this->m_initResult;
    }

    void Application::pushGui(Gui &gui) {
        gui.layout();
        this->m_guis.push_back(std::move(gui));
    }

    void Application::pushGui(Gui &&gui) {
        gui.layout();
        this->m_guis.push_back(std::move(gui));
    }

    void Application::goBack() {
        this->m_guis.pop_back();
    }

    void Application::registerFont(const std::string &fontName, const std::string &path) {
        nvgCreateFont(Application::s_vgCtx, fontName.c_str(), path.c_str());
    }

    void Application::registerFont(const std::string &fontName, u8 *data, size_t size, bool freeMemory) {
        nvgCreateFontMem(Application::s_vgCtx, fontName.c_str(), data, size, freeMemory);
    }

    void drawFPS(NVGcontext *vg, u32 fps) {
        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGBA(0x00, 0x00, 0x00, 0x80));
        nvgRect(vg, ScreenWidth - 40, 0, 40, 25);
        nvgFill(vg);

        nvgFillColor(vg, nvgRGB(0xFF, 0xFF, 0xFF));
        nvgFontSize(vg, 20);
        nvgFontFace(vg, "regular");
        nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
        nvgBeginPath(vg);

        nvgText(vg, ScreenWidth - 8, 5, std::to_string(fps).c_str(), nullptr);
    }

    bool Application::loop() {
        static u32 frameStart = SDL_GetTicks();
        static u32 frameEnd = 0;

        u32 frameTime = frameEnd - frameStart;

        this->handleEvents();
        this->draw();

        if (frameTime < TargetFrameTime)
            SDL_Delay(TargetFrameTime - frameTime);

        if (frameTime > TargetFrameTime)
            this->m_currFps = 1000.0F / frameTime;
        else this->m_currFps = TargetFPS;

        frameStart = frameEnd;
        frameEnd = SDL_GetTicks();

        return this->m_running;
    }

    void Application::handleEvents() {
        for (SDL_Event event = { 0 }; SDL_PollEvent(&event);) {
            switch (event.type) {
                case SDL_QUIT:
                    this->m_running = false;
                    break;
            }
        }
    }

    void Application::draw() {
        glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        nvgBeginFrame(Application::s_vgCtx, ScreenWidth, ScreenHeight, 1.0F);

        this->m_guis.back().draw(Application::s_vgCtx);
        drawFPS(Application::getNVGContext(), this->m_currFps);

        nvgEndFrame(Application::s_vgCtx);

        SDL_GL_SwapWindow(Application::s_window);
    }

}
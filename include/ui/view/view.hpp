#pragma once

#include <venus.hpp>

#include <nanovg.h>
#include <list>
#include <memory>
#include <optional>

#include "ui/style.hpp"

namespace ui {

    enum class Button {
        None,
        Up,
        Down,
        Left,
        Right,
        Ok,
        Back,
        PageLeft,
        PageRight,

        NumButtons  // Number of buttons
    };

}

namespace ui::view {

#define NON_FOCUSABLE nullptr
#define CHILD(view) (view).setParent(this)

    enum class FocusDirection {
        Up,
        Down,
        Left,
        Right
    };

    class View {
    public:
        View() = default;

        void setParent(View* const parent);
        View* const getParent() const;

        virtual void draw(NVGcontext *vg) = 0;
        virtual void layout() = 0;

        virtual void drawHighlightBackground(NVGcontext *vg);
        virtual void drawHighlight(NVGcontext *vg);

        void frame(NVGcontext *vg);

        void setBoundaries(s32 x, s32 y, s32 width, s32 height);

        s32 getX();
        s32 getY();
        s32 getWidth();
        s32 getHeight();

        void setFocused(bool focused);
        bool isFocused() const;

        virtual View* getDefaultFocus();
        virtual View* getNextFocus(const FocusDirection direction);

        virtual void onInput(Button button);

    private:
        bool m_focused = false;
        s32 m_x, m_y;
        s32 m_width, m_height;

        View *m_parent;
    };

}
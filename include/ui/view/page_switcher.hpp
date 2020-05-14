#pragma once

#include "ui/view/view.hpp"
#include "ui/view/header.hpp"

#include <vector>

namespace ui::view {

    class PageSwitcher : public View {
    public:
        PageSwitcher();

        template<typename T, typename... Args>
        const View& addPage(Args... args) {
            auto view = std::make_unique<T>(args...);
            view->setParent(this);
            this->m_pages.push_back(std::move(view));

            return *this->m_pages.back();
        }

        void draw(NVGcontext *vg) override;
        void layout() override;

        View* getDefaultFocus() override;
        View* getNextFocus(const FocusDirection direction) override;

        void onInput(ui::Button button) override;

    private:
        u32 m_currPage = 0;
        u32 m_nextPage = 0;
        s32 m_pageAnimationOffset = 0;
        enum class SwipeDirection { None, Left, Right } m_swipeDirection;

        std::vector<std::unique_ptr<View>> m_pages;

        ui::view::Header m_header;

    };

}
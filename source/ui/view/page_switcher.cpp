#include "ui/view/page_switcher.hpp"

namespace ui::view {

    PageSwitcher::PageSwitcher() : View(), m_currPage(0), m_nextPage(0), m_swipeDirection(SwipeDirection::None) {
        CHILD(this->m_header);
    }

    s8 sign(s32 value) {
        return (value > 0) - (value < 0);
    }

    void PageSwitcher::draw(NVGcontext *vg) {
        this->m_pages[this->m_currPage]->draw(vg);

        if (this->m_swipeDirection != SwipeDirection::None) {
            this->m_pages[this->m_nextPage]->draw(vg);
            this->layout();
        }

        this->m_header.draw(vg);
    }

    void PageSwitcher::layout() {
        if (this->m_swipeDirection == SwipeDirection::None) {
            for (auto &page : this->m_pages) {
                page->setBoundaries(getX(), getY(), getWidth(), getHeight());
                page->layout();
            }

            this->m_header.setBoundaries(getX(), getY(), getWidth(), getHeight());
            this->m_header.layout();
        } else if (this->m_swipeDirection == SwipeDirection::Left) {
            this->m_pages[this->m_currPage]->setBoundaries(getX() - this->m_pageAnimationOffset + cfg::ScreenWidth, getY(), getWidth(), getHeight());
            this->m_pages[this->m_nextPage]->setBoundaries(getX() - this->m_pageAnimationOffset, getY(), getWidth(), getHeight());
            this->m_pages[this->m_currPage]->layout();
            this->m_pages[this->m_nextPage]->layout();
        } else if (this->m_swipeDirection == SwipeDirection::Right) {
            this->m_pages[this->m_currPage]->setBoundaries(getX() + this->m_pageAnimationOffset - cfg::ScreenWidth, getY(), getWidth(), getHeight());
            this->m_pages[this->m_nextPage]->setBoundaries(getX() + this->m_pageAnimationOffset, getY(), getWidth(), getHeight());
            this->m_pages[this->m_currPage]->layout();
            this->m_pages[this->m_nextPage]->layout();
        }


        if (this->m_pageAnimationOffset <= 0 && this->m_swipeDirection != SwipeDirection::None) {
            this->m_pageAnimationOffset = 0;
            this->m_swipeDirection = SwipeDirection::None;
            this->m_currPage = this->m_nextPage;
        } else {
            this->m_pageAnimationOffset = std::max(0, this->m_pageAnimationOffset - s32(cfg::ScreenWidth / 15));
        }

    }


    View* PageSwitcher::getDefaultFocus() {
        if (this->m_pages.size() == 0)
            return NON_FOCUSABLE;

        return this->m_pages[this->m_currPage]->getDefaultFocus();
    }

    View* PageSwitcher::getNextFocus(const FocusDirection direction) {
        if (this->m_pages.size() == 0)
            return NON_FOCUSABLE;

        return this->m_pages[this->m_currPage]->getNextFocus(direction);
    }

    void PageSwitcher::onInput(Button button) {
        if (this->m_swipeDirection != SwipeDirection::None)
            return;

        if (button == Button::PageLeft) {
            if (this->m_currPage > 0) {
                this->m_nextPage = this->m_currPage - 1;
                this->m_pageAnimationOffset = cfg::ScreenWidth;
                this->m_swipeDirection = SwipeDirection::Left;
            }
        } else if (button == Button::PageRight) {
            if (this->m_currPage < this->m_pages.size() - 1) {
                this->m_nextPage = this->m_currPage + 1;
                this->m_pageAnimationOffset = cfg::ScreenWidth;
                this->m_swipeDirection = SwipeDirection::Right;
            }
        }
    }

}

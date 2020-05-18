#include "ui/view/page_switcher.hpp"

namespace ui::view {

    PageSwitcher::PageSwitcher() : View(), m_currPage(0), m_nextPage(0),
    m_swipeDirection(SwipeDirection::None), m_queuedSwipeDirection(SwipeDirection::None) {
        CHILD(this->m_header);
    }

    void PageSwitcher::draw(NVGcontext *vg) {
        if (this->m_swipeDirection == SwipeDirection::None) {
            this->m_pages[this->m_currPage]->draw(vg);
        } else {
            nvgSave(vg);
            if (this->m_swipeDirection == SwipeDirection::Left)
                nvgTranslate(vg, getX() - this->m_pageAnimationOffset + cfg::ScreenWidth, 0);
            else
                nvgTranslate(vg, getX() + this->m_pageAnimationOffset - cfg::ScreenWidth, 0);

            this->m_pages[this->m_currPage]->draw(vg);
            nvgRestore(vg);

            nvgSave(vg);
            if (this->m_swipeDirection == SwipeDirection::Left)
                nvgTranslate(vg, getX() - this->m_pageAnimationOffset, 0);
            else
                nvgTranslate(vg, getX() + this->m_pageAnimationOffset, 0);

            this->m_pages[this->m_nextPage]->draw(vg);
            nvgRestore(vg);

            {
                this->m_header.setSelectedTab(this->m_pages.size(), this->m_nextPage);

                if (this->m_pageAnimationOffset <= 0 && this->m_swipeDirection != SwipeDirection::None) {
                    this->m_pageAnimationOffset = 0;
                    this->m_swipeDirection = SwipeDirection::None;
                    this->m_currPage = this->m_nextPage;

                    if (this->m_queuedSwipeDirection != SwipeDirection::None) {
                        this->startSwipe(this->m_queuedSwipeDirection);
                        this->m_queuedSwipeDirection = SwipeDirection::None;
                    }
                } else {
                    this->m_pageAnimationOffset = std::max(0.0F, this->m_pageAnimationOffset * 0.80F);
                }
            }

        }

        this->m_header.draw(vg);
    }

    void PageSwitcher::layout() {
        for (auto &page : this->m_pages) {
            page->setBoundaries(getX(), getY(), getWidth(), getHeight());
            page->layout();
        }

        this->m_header.setBoundaries(getX(), getY(), getWidth(), getHeight());
        this->m_header.layout();

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
        if (this->m_swipeDirection != SwipeDirection::None) {
            if (button == Button::PageLeft)
                this->m_queuedSwipeDirection = SwipeDirection::Left;
            else if (button == Button::PageRight)
                this->m_queuedSwipeDirection = SwipeDirection::Right;

            return;
        }

        if (button == Button::PageLeft)
            this->startSwipe(SwipeDirection::Left);
        else if (button == Button::PageRight)
            this->startSwipe(SwipeDirection::Right);

    }

    void PageSwitcher::startSwipe(SwipeDirection direction) {
        if (direction == SwipeDirection::Left) {
            if (this->m_currPage > 0) {
                this->m_nextPage = this->m_currPage - 1;
                this->m_pageAnimationOffset = cfg::ScreenWidth;
                this->m_swipeDirection = SwipeDirection::Left;
            }
        } else if (direction == SwipeDirection::Right) {
            if (this->m_currPage < this->m_pages.size() - 1) {
                this->m_nextPage = this->m_currPage + 1;
                this->m_pageAnimationOffset = cfg::ScreenWidth;
                this->m_swipeDirection = SwipeDirection::Right;
            }
        }
    }

}


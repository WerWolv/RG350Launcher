#include "ui/view/grid.hpp"

#include <SDL.h>
#include "venus.hpp"

namespace ui::view {

    Grid::Grid(u16 columns, float aspectRatio, u32 spacing) : View(), m_rows(0), m_columns(columns), m_aspectRatio(aspectRatio), m_rowHeight(0), m_spacing(spacing) {

    }

    void Grid::draw(NVGcontext *vg) {
        u32 currentTicks = SDL_GetTicks();

        if (this->m_offset != this->m_targetOffset) {
            float timeProgress = static_cast<float>(currentTicks - m_animationStartTick) / static_cast<float>(m_animationEndTick - m_animationStartTick);
            float animationProgress = (timeProgress >= 1.f) ? 1.f : 1.f - powf(2, -10 * timeProgress);
            this->m_offset = m_startOffset + static_cast<s32>((m_targetOffset - m_startOffset) * animationProgress);
        }

        nvgSave(vg);
        nvgTranslate(vg, 0, this->m_offset * -1);

        for (auto &child : this->m_children) {
            child->frame(vg);
        }
        
        nvgRestore(vg);
    }

    void Grid::layout() {
        u32 placeX = getX() + this->m_spacing * 2;
        u32 placeY = getY() - this->m_offset;
        const u32 itemWidth = (getWidth() - (this->m_spacing * (this->m_columns + 3))) / this->m_columns;
        const u32 itemHeight = this->m_aspectRatio != 0.0F ? itemWidth * this->m_aspectRatio : (getHeight() / this->m_rows) - (this->m_spacing * (this->m_rows - 1));

        u32 index = 0;
        for (auto &child : this->m_children) {
            child->setBoundaries(placeX, placeY, itemWidth, itemHeight);
            child->layout();

            placeX += itemWidth + this->m_spacing;
            if (++index % this->m_columns == 0) {
                placeX = getX() + this->m_spacing * 2;
                placeY += itemHeight + this->m_spacing;
            }
        }
    }

    View* Grid::getDefaultFocus() {
        for (auto& child : this->m_children) {
            if (View *nextFocus = child->getDefaultFocus(); nextFocus != nullptr)
                return nextFocus;
        }

        return NON_FOCUSABLE;
    }

    View* Grid::getNextFocus(const FocusDirection direction) {
        switch (direction) {
            case FocusDirection::Right:
                for (s32 i = (this->m_focusedIndex % this->m_columns) + 1; i < this->m_columns; i++) {
                    s32 offset = i - (this->m_focusedIndex % this->m_columns);
                    if (this->m_focusedIndex + offset >= this->m_children.size())
                        break;
                    if (View *nextFocus = this->m_children[this->m_focusedIndex + offset]->getDefaultFocus(); nextFocus != nullptr) {
                        this->checkForScrolling(nextFocus);
                        this->m_focusedIndex += offset;
                        return nextFocus;
                    }
                }
                break;
            case FocusDirection::Left:
                for (s32 i = (this->m_focusedIndex % this->m_columns) - 1; i >= 0; i--) {
                    s32 offset = i - (this->m_focusedIndex % this->m_columns);
                    if (this->m_focusedIndex - offset > this->m_children.size() || this->m_focusedIndex - offset < 0)
                        break;
                    if (View *nextFocus = this->m_children[this->m_focusedIndex + offset]->getDefaultFocus(); nextFocus != nullptr) {
                        this->checkForScrolling(nextFocus);
                        this->m_focusedIndex += offset;
                        return nextFocus;
                    }
                }
                break;

            case FocusDirection::Up:
                for (s32 i = this->m_focusedIndex - this->m_columns; i >= 0; i -= this->m_columns) {
                    if (i > this->m_children.size() || i < 0)
                        break;
                    if (View *nextFocus = this->m_children[i]->getDefaultFocus(); nextFocus != nullptr) {
                        this->checkForScrolling(nextFocus);
                        this->m_focusedIndex = i;
                        return nextFocus;
                    }
                }
                break;
            case FocusDirection::Down:
                for (s32 i = this->m_focusedIndex + this->m_columns; i < this->m_children.size(); i += this->m_columns) {
                    if (i > this->m_children.size() || i < 0)
                        break;
                    if (View *nextFocus = this->m_children[i]->getDefaultFocus(); nextFocus != nullptr) {
                        this->checkForScrolling(nextFocus);
                        this->m_focusedIndex = i;
                        return nextFocus;
                    }
                }
                break;
        }

        return NON_FOCUSABLE;
    }

    void Grid::checkForScrolling(View* nextFocus) {
        s32 screenHeight = cfg::ScreenHeight;

        if (nextFocus->getY() - this->m_offset < 0) {
            this->m_targetOffset += nextFocus->getY() - this->m_offset - getY() - Style::Padding;
            this->m_startOffset = this->m_offset;
            this->m_animationStartTick = SDL_GetTicks();
            this->m_animationEndTick = this->m_animationStartTick + Style::ScrollingDuration;
        }
        else if (nextFocus->getY() - this->m_offset >= screenHeight - nextFocus->getHeight() - Style::Padding) {
            this->m_targetOffset += nextFocus->getY() - this->m_offset + nextFocus->getHeight() + Style::Padding - screenHeight;
            this->m_startOffset = this->m_offset;
            this->m_animationStartTick = SDL_GetTicks();
            this->m_animationEndTick = this->m_animationStartTick + Style::ScrollingDuration;
        }
    }

}
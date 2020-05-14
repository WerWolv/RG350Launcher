#include "ui/view/grid.hpp"

namespace ui::view {

    Grid::Grid(u16 columns, float aspectRatio, u32 spacing) : View(), m_rows(0), m_columns(columns), m_aspectRatio(aspectRatio), m_rowHeight(0), m_spacing(spacing) {

    }

    void Grid::draw(NVGcontext *vg) {
        for (auto &child : this->m_children)
            child->frame(vg);
    }

    void Grid::layout() {
        u32 placeX = getX() + this->m_spacing * 2;
        u32 placeY = getY();
        const u32 itemWidth = (getWidth() / this->m_columns) - (this->m_spacing * (this->m_columns - 1));
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
                        this->m_focusedIndex = i;
                        return nextFocus;
                    }
                }
                break;
        }

        return NON_FOCUSABLE;
    }

}
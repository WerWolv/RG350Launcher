#pragma once

#include "ui/view/view.hpp"
#include "ui/style.hpp"

#include <vector>
#include <cmath>

namespace ui::view {

    class Grid : public View {
    public:
        Grid(u16 columns, float aspectRatio = 0.0F, u32 spacing = ui::Style::Padding);

        void draw(NVGcontext *vg) override;
        void layout() override;

        template<typename T, typename... Args>
        const View& addItem(Args... args) {
            auto view = std::make_unique<T>(args...);
            view->setParent(this);
            this->m_children.push_back(std::move(view));

            this->m_rows = std::ceil(this->m_children.size() / float(this->m_columns));

            return *this->m_children.back();
        }

        View * getDefaultFocus() override;
        View * getNextFocus(const FocusDirection direction) override;

    private:
        u16 m_rows, m_columns;
        float m_aspectRatio;
        u32 m_rowHeight;
        u32 m_spacing;

        std::vector<std::unique_ptr<View>> m_children;
        s32 m_focusedIndex = 0;
    };

}
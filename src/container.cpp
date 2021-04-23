#include "container.h"

Container::Container(const std::vector<Styler> &styles, const std::vector<Widget *> &children) : Widget(styles, children)
{
    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        // make big enough to contain all children
        int rightMost = self.left();
        int bottomMost = self.top();
        for (auto p_child : _children)
        {
            if (!p_child->style.isRelative)
            {
                continue;
            }

            if (rightMost < p_child->rightM())
            {
                rightMost = p_child->rightM();
            }

            if (bottomMost < p_child->bottomM())
            {
                bottomMost = p_child->bottomM();
            }
        }

        self.style.size.setX(rightMost - self.left());
        self.style.size.setY(bottomMost - self.top());
        return false;
    });
}

Container::~Container() = default;

#include "container.h"

Container::Container(std::vector<std::shared_ptr<Widget>> children) : Widget(std::move(children))
{
    // update size, so it contains all children elements
    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        int rightMost = self.left();
        int bottomMost = self.top();
        for (const auto &p_child : _children)
        {
            if (!p_child->style.isRelative || !p_child->isEnabled())
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

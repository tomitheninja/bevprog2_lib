#include "select.h"
#include <algorithm>
#include <iterator>
#include "fixed_size_label.h"

std::vector<Widget *> optionsToLabels(const std::vector<std::string> &options)
{
    std::vector<Widget *> result;
    for (auto &option : options)
    {
        Widget *p_w = new FixedSizeLabel(option, {[](Style &s) {
                                             s.isRelative = true;
                                             s.size.setX(100);
                                             s.bgColor.second = Color{96, 96, 96};
                                         }},
                                         true);
        p_w->disable();
        result.push_back(p_w);
    }
    return result;
}

Select::Select(const std::vector<std::string> &options, const std::vector<Styler> &styles) : Container(styles, optionsToLabels(options))
{
    style.size.setX(150);
    _isOpen = true;
    style.marginBottom = 2;
    style.innerBorderTop = style.innerBorderBottom = style.innerBorderLeft = style.innerBorderRight = {true, Color{255, 255, 255}};

    style.outerBorderBottom.second = Color(128, 128, 128);

    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        if (!isFocused())
            _isOpen = false;
        for (auto p_child : _children)
        {
            p_child->style.size.setX(100);
            p_child->disable();
        }
        style.outerBorderBottom.first = !isOpen();
        if (!isOpen())
        {
            Widget *w = _children[_selectedIdx];
            w->style.position.setY(0);
            w->enable();
        }
        if (isOpen())
        {
            for (int i = 0; i < _children.size(); i++)
            {
                Widget *w = _children[i];
                w->style.position.setY(i * _children[_selectedIdx]->style.size.y());
                w->style.bgColor.first = false;
                w->style.bgColor.second = Color(64, 64, 64);
                w->enable();
            }
            _children[_selectedIdx]->style.bgColor.first = true;
        }
        return false;
    });

    for (int i = 0; i < _children.size(); i++)
    {
        _children[i]->addEvent([&, i](const genv::event &evt, const Vector2 &cursor, Widget &self) {
            if (self.containsPoint(cursor))
            {
                self.style.bgColor.first = true;
                self.style.bgColor.second = Color{32, 32, 32};
                if (evt.button == genv::btn_left)
                {
                    _isOpen = !_isOpen;
                    _selectedIdx = i;
                   // if (!_isOpen) style.size.setY(self.style.size.y());
                    return true;
                }
            }
            return false;
        });
    }
}

Select::~Select() = default;

bool Select::isOpen() const { return _isOpen; }

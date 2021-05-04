#include "select.h"
#include <algorithm>
#include <iterator>
#include "fixed_size_label.h"

// maps options to disabled FixedSizeLabel-s
std::vector<std::shared_ptr<Widget>> optionsToLabels(const std::vector<std::string> &options)
{
    std::vector<std::shared_ptr<Widget>> result;
    for (auto &txt : options)
    {
        std::shared_ptr<Widget> p_w = std::make_unique<FixedSizeLabel>(txt, true);
        p_w->style.isRelative = true;
        p_w->style.size.setX(100);
        p_w->style.marginLeft = 5;
        p_w->style.marginRight = 5;
        p_w->disable();
        result.push_back(p_w);
    }
    return result;
}

Select::Select(const std::vector<std::string>& options) : Container(optionsToLabels(options))
{
    style.size.setX(150);
    _isOpen = false;
    style.innerBorderTop = style.innerBorderBottom = style.innerBorderLeft = style.innerBorderRight = {true, Color{255, 255, 255}};

    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        // Close when lost focus
        if (!isFocused())
            _isOpen = false;
        // Child fills area
        for (auto p_child : _children)
        {
            p_child->style.size.setX(100);
            p_child->disable(); // disable all
        }
        if (!isOpen())
        {
            Widget& w = *_children[_selectedIdx];
            w.style.position.setY(0); // On the top
            w.style.bgMColor = {true, Color(32, 32, 32)};
            w.enable();
        }
        if (isOpen())
        {
            for (auto i = 0; i + _offset < _children.size(); i++)
            {
                int j = i + _offset;
                Widget& w = *_children[j];
                // Only _children[_selectedIdx] has up-to-date size
                w.style.position.setY(i * _children[_selectedIdx]->style.size.y());
                w.style.bgMColor.first = false;
                if (i < _many)
                    w.enable();
            }
            _children[_selectedIdx]->style.bgMColor = {true, Color(32, 32, 32)};
        }
        if (isOpen() && isFocused())
        {
            if (evt.button == genv::btn_wheelup)
                scrollUp();
            if (evt.button == genv::btn_wheeldown)
                scrollDown();
        }
        else if (isFocused() && containsPoint(cursor))
        {
            if (evt.button == genv::btn_wheelup && _selectedIdx > 0)
                _selectedIdx--;
            if (evt.button == genv::btn_wheeldown && _selectedIdx + 1 < _children.size())
                _selectedIdx++;
        }
        return false;
    });

    // events
    for (auto i = 0; i < _children.size(); i++)
    {
        _children[i]->addEvent([&, i](const genv::event &evt, const Vector2 &cursor, Widget &self) {
            // is hovered
            if (self.containsPoint(cursor))
            {
                self.style.bgMColor.first = true;
                if (isOpen())
                {
                    self.style.bgMColor.second = Color{128, 128, 128};
                }
                else
                {
                    self.style.bgMColor.second = Color{64, 64, 64};
                }
                if (evt.button == genv::btn_left)
                {
                    _isOpen = !_isOpen;
                    _selectedIdx = i;
                    return true;
                }
            }
            return false;
        });
    }

    displayMany(3);
}

void Select::postChildDraw() const
{
    if (!isOpen())
    {
        (topRight() - Vector2{15, 0}).move_to();
        Color(96, 128, 128).apply();
        genv::gout << genv::text("v");
    }
}

Select::~Select() = default;

void Select::displayMany(int many)
{
    _many = std::min((int)_children.size(), std::max(1, many));
}

bool Select::isOpen() const { return _isOpen; }

std::string Select::getValue() const
{
    Widget& w = *_children[_selectedIdx];
    return static_cast<FixedSizeLabel *>(&w)->getText();
}

void Select::scrollUp()
{
    _offset = std::max(0, _offset - 1);
}

void Select::scrollDown(){
    _offset = std::min((int)(_children.size() - _many), _offset + 1);
}

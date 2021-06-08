#include "select.h"
#include "fixed_size_label.h"

Select::~Select() = default;

void Select::setOptions(const std::vector<std::string> &list)
{
    _children.clear();
    for (auto &txt : list)
        appendOption(txt);
}

int Select::getSelectedIdx() const
{
    return _selectedIdx;
}

void Select::setSelectedIdx(int idx)
{
    if (idx < 0)
        idx = 0;
    if (idx < _children.size() - 1)
    {
        idx = _children.size() - 1;
    }

    _selectedIdx = idx;
}

Select::Select(const std::vector<std::string> &options) : Container()
{
    setOptions(options);
    displayMany(_manyRequested);

    style.innerBorderTop = {true, Color{255, 255, 255}};
    style.innerBorderBottom = {true, Color{255, 255, 255}};
    style.innerBorderLeft = {true, Color{255, 255, 255}};
    style.innerBorderRight = {true, Color{255, 255, 255}};

    style.bgColor = {false, Color(32, 32, 32)};

    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
             {
                 style.size.setX(300);
                 // Close when lost focus
                 if (!isFocused())
                     _isOpen = false;

                 // responsive size for children
                 for (auto &p_child : _children)
                 {
                     p_child->disable(); // disable all
                 }
                 // hover effect
                 style.bgColor.first = !isOpen() && containsPoint(cursor);

                 if (!isOpen())
                 {
                     // render closed
                     Widget &selected = *_children[_selectedIdx];
                     selected.style.position.setY(0); // On the top
                     selected.enable();
                     // all the other options are disabled
                 }
                 else
                 {
                     // render opened
                     for (auto i = 0; i < _children.size() - _offset; i++)
                     {
                         Widget &w = *_children[i + _offset];
                         w.style.position.setY(i * _children[_selectedIdx]->style.size.y());
                         if (i < _many)
                             w.enable();
                     }
                 }
                 if (isFocused())
                 {
                     if (isOpen())
                     {
                         // scroll on opened list = rotate list
                         switch (evt.button)
                         {
                         case genv::btn_wheelup:
                             scrollUp();
                             return true;
                         case genv::btn_wheeldown:
                             scrollDown();
                             return true;
                         }
                     }
                     else if (containsPoint(cursor))
                     {
                         // scroll on closed = change value
                         if (evt.button == genv::btn_wheelup && _selectedIdx > 0)
                         {
                             _selectedIdx--;
                             return true;
                         }
                         if (evt.button == genv::btn_wheeldown && _selectedIdx + 1 < _children.size())
                         {
                             _selectedIdx++;
                             return true;
                         }
                     }
                 }
                 return false;
             });
}

void Select::appendOption(const std::string &txt)
{
    std::shared_ptr<Widget> p_w = std::make_shared<FixedSizeLabel>(txt, true);
    p_w->setParent(this);
    if (_children.empty())
    {
        p_w->style.isRelative = true;
        p_w->style.size.setX(style.size.x() - 5);
        p_w->style.bgMColor = {false, Color(64, 64, 64)};   // selected item
        p_w->style.bgColor = {false, Color(128, 128, 128)}; // hovered item
    }
    else
    {
        p_w->style = _children[0]->style;
    }

    p_w->disable();

    int i = _children.size();

    p_w->addEvent([&, i](const genv::event &evt, const Vector2 &cursor, Widget &self)
                  {
                      self.style.bgMColor.first = _isOpen && _selectedIdx == i;
                      self.style.bgColor.first = _isOpen && self.containsPoint(cursor);
                      if (evt.button == genv::btn_left && self.containsPoint(cursor))
                      {
                          if (_isOpen)
                          {
                              _selectedIdx = i;
                          }
                          _isOpen = !_isOpen;
                          return true;
                      }
                      return false;
                  });

    _children.push_back(p_w);
    displayMany(_manyRequested);
}

// draw the triangle
void Select::postChildDraw() const
{
    if (!isOpen())
    {
        (topRight() - Vector2{15, 0}).move_to();
        Color(96, 128, 128).apply();
        genv::gout << genv::text("v");
    }
}

void Select::displayMany(int many)
{
    _manyRequested = many;
    _many = std::min((int)_children.size(), std::max(1, many));
}

bool Select::isOpen() const { return _isOpen; }

std::string Select::getValue() const
{
    Widget &w = *_children[_selectedIdx];
    return static_cast<FixedSizeLabel *>(&w)->getText();
}

void Select::scrollUp()
{
    _offset = std::max(0, _offset - 1);
}

void Select::scrollDown()
{
    _offset = std::min((int)(_children.size() - _many), _offset + 1);
}

#include "checkbox.h"

CheckBox::CheckBox(std::string text) : Container({std::make_shared<FixedSizeLabel>("x"), std::make_shared<Label>(text)})
{
    style.size = {150, 25};
    box = std::static_pointer_cast<FixedSizeLabel>(_children[0]);
    box->style.size = {15, 15};
    box->style.isRelative = true;
    box->style.outerBorderTop = {true, Color{255, 255, 255}};
    box->style.outerBorderBottom = {true, Color{255, 255, 255}};
    box->style.outerBorderLeft = {true, Color{255, 255, 255}};
    box->style.outerBorderRight = {true, Color{255, 255, 255}};
    box->style.marginLeft = 5;
    box->style.marginTop = 2;
    _children.push_back(box);

    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
             {
                 if (isFocused())
                 {
                     box->focus();
                 }
                 return false;
             });

    box->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
                  {
                      box->setText(isChecked() ? "x" : " ");
                      return false;
                  });

    lb = std::static_pointer_cast<Label>(_children[1]);
    lb->style.position = {30, 0};
    lb->style.isRelative = true;
    _children.push_back(lb);

    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
             {
                 if (evt.button == genv::btn_left && self.containsPoint(cursor))
                 {
                     toggle();
                     return true;
                 }
                 return false;
             });
}

CheckBox::~CheckBox() = default;

bool CheckBox::isChecked() const
{
    return _checked;
}

void CheckBox::select()
{
    _checked = true;
}

void CheckBox::deselect()
{
    _checked = false;
}

void CheckBox::toggle()
{
    _checked = !_checked;
}

#include "text_input.h"

TextInput::TextInput() : Widget({std::make_shared<FixedSizeLabel>("")})
{
    style.size = {200, 25};
    style.innerBorderBottom = {true, Color(255, 255, 255)};
    style.innerBorderTop = {true, Color(255, 255, 255)};
    style.innerBorderLeft = {true, Color(255, 255, 255)};
    style.innerBorderRight = {true, Color(255, 255, 255)};

    lb = std::static_pointer_cast<FixedSizeLabel>(_children[0]);
    lb->style.isRelative = true;

    lb->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
                 {
                     lb->style.size = style.size;
                     if (evt.type == genv::ev_timer)
                     {
                         if (backspacePressed)
                         {
                             removeInsert();
                             std::string txt = lb->getText();
                             if (!txt.empty())
                                 txt.pop_back();
                             lb->setText(txt);
                             return true;
                         }
                         else
                         {
                             toggleInsert();
                             return true;
                         }
                     }
                     else if (evt.type == genv::ev_key && (self.containsPoint(cursor) || isFocused()))
                     {
                         char c = '\0';
                         if (evt.keyname.length() == 1)
                         {
                             c = evt.keyname[0];
                         }
                         else if (evt.keycode == genv::key_space)
                         {
                             c = ' ';
                         }
                         else if (evt.keycode == genv::key_backspace)
                         {
                             backspacePressed = true;
                         }
                         else if (evt.keycode == -genv::key_backspace)
                         {
                             backspacePressed = false;
                         }
                         if (c != '\0')
                         {
                             bool insert = insertState;
                             removeInsert();
                             std::string text = lb->getText();
                             text.push_back(c);
                             lb->setText(text);
                             if (insert)
                                 insertInsert();

                             return true;
                         }
                     }
                     return false;
                 });

    _children.push_back(lb);
}

TextInput::~TextInput() {}

void TextInput::toggleInsert()
{
    if (insertState)
        removeInsert();
    else
        insertInsert();
}

void TextInput::removeInsert()
{
    if (!insertState)
        return;
    std::string txt = lb->getText();
    if (!txt.empty())
    {
        txt.pop_back();
        lb->setText(txt);
    }
    insertState = false;
}

void TextInput::insertInsert()
{
    if (insertState)
        return;
    std::string txt = lb->getText();
    txt.push_back('|');
    lb->setText(txt);
    insertState = true;
}

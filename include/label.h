#ifndef LABEL_H
#define LABEL_H

#include "widget.h"

class Label : public Widget
{
public:
    Label(const Vector2 &position) : Widget(position){};
    virtual ~Label() = default;
    std::string getText() const { return _text; }
    void setText(const std::string &text)
    {
        _text = text;
        update();
    }
    Color getColor() const { return _color; }
    void setColor(Color color) { _color = color; }

    void draw() const override;
    void update() override;

protected:
private:
    std::string _text = "";
    Color _color = {255, 255, 255};
};

#endif // LABEL_H

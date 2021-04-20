#ifndef NUMBER_PICKER_H
#define NUMBER_PICKER_H

#include "widget.h"
#include "label.h"

class NumberPicker : public Widget
{
public:
    NumberPicker(const Vector2 &position, int min = 0, int max = 100);
    virtual ~NumberPicker() = default;
    int getValue() const { return _value; }
    void setValue(int value);

    void draw() const override;
    void update() override;
    void setSize(const Vector2 &size) override;
    EventResult handle(const genv::event &ev, const Vector2 &cursor, bool &canCaptureFocus) override;

protected:
private:
    int _min, _max;
    int _value = 0;
    Label _lbValue = Label({0, 0});
    Label _btnIncr = Label({0, 0});
    Label _btnDecr = Label({0, 0});
};

#endif // NUMBER_PICKER_H

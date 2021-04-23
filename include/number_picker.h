#ifndef NUMBERPICKER_H
#define NUMBERPICKER_H

#include "widget.h"
#include "label.h"
#include "button.h"
#include "container.h"

class NumberPicker : public Container
{
    public:
        NumberPicker(const std::vector<Styler> &styles, int lower, int upper);
        Label *lb;
        Button *btnIncr;
        Button *btnDecr;
        void setValue(int value);
        int getValue();
    protected:
        int _value = 0;
    private:
        int _lower;
        int _upper;

};

#endif // NUMBERPICKER_H

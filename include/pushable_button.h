#ifndef PUSHABLEBUTTON_H
#define PUSHABLEBUTTON_H

#include "button.h"

class PushableButton : public Button
{
public:
    PushableButton(const std::string &text);
    virtual ~PushableButton();
    Color hoverColor;

protected:
private:
    Color _preHoverColor;
};

#endif // PUSHABLEBUTTON_H

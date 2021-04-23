#ifndef PUSHABLEBUTTON_H
#define PUSHABLEBUTTON_H

#include "button.h"

class PushableButton : public Button
{
    public:
        PushableButton(const std::string &text, const std::vector<Styler> &styles = {}, const std::vector<Styler> &lbStyles = {});
        virtual ~PushableButton();
        Color hoverColor;

    protected:

    private:
        Color _preHoverColor;
};

#endif // PUSHABLEBUTTON_H

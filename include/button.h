#ifndef BUTTON_H
#define BUTTON_H

#include "label.h"
#include "container.h"

class Button : public Container
{
    public:
        Button(const std::string &text, const std::vector<Styler> &styles = {}, const std::vector<Styler> &lbStyles = {});
        virtual ~Button();

        std::string getText() const;
        void setText(const std::string &newText);
    protected:

    private:
        Label *_lb;
};

#endif // BUTTON_H

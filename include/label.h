#ifndef LABEL_H
#define LABEL_H

#include "widget.h"

class Label : public Widget
{
public:
    Label(const std::string &text);
    virtual ~Label();

    std::string getText() const;
    void setText(const std::string &newText);

protected:
    void preChildDraw() const override;

private:
    std::string _text;
};

#endif // LABEL_H

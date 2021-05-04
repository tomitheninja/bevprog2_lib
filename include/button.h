#ifndef BUTTON_H
#define BUTTON_H

#include "label.h"
#include "container.h"

class Button : public Container
{
public:
    Button(const std::string &text);
    virtual ~Button();

    std::string getText() const;
    void setText(const std::string &newText);

    std::shared_ptr<Label> lb;

protected:
private:
};

#endif // BUTTON_H

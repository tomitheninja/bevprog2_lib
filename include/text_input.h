#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "widget.h"
#include "fixed_size_label.h"

class TextInput : public Widget
{
public:
    TextInput();
    virtual ~TextInput();
    void removeInsert();
    void insertInsert();
    void toggleInsert();
    std::string getText();

    std::shared_ptr<FixedSizeLabel> lb;

protected:
private:
    bool insertState = false;
};

#endif // TEXTINPUT_H

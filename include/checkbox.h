#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "container.h"
#include "fixed_size_label.h"
#include "label.h"
#include <memory>

class CheckBox : public Container
{
public:
    CheckBox(std::string text = "checkbox");
    virtual ~CheckBox();
    bool isChecked() const;
    void select();
    void deselect();
    void toggle();
    std::function<void()> onChange = []() {};

protected:
private:
    std::shared_ptr<FixedSizeLabel> box;
    std::shared_ptr<Label> lb;
    bool _checked = false;
};

#endif // CHECKBOX_H

#ifndef APPLICATION_H
#define APPLICATION_H

#include "button.h"
#include "text_input.h"

#include "checkbox.h"
#include "select.h"
#include "label.h"
#include "number_picker.h"
#include "pushable_button.h"

struct Option
{
    std::string name;
    int priority;
    int idx;
};

class Application
{
public:
    Application();
    virtual ~Application();
    bool tick();

protected:
private:
    void addOption(Option o);
    void delOption(int index);
    void updateOptions();
    Option createOption(std::string name, int priority);

    Vector2 _screen;
    genv::event _ev;
    std::vector<std::shared_ptr<Widget>> _ws;
    Vector2 _cursor;

    std::shared_ptr<Label> lbItemName;
    std::shared_ptr<TextInput> itemName;
    std::shared_ptr<Label> lbPriority;
    std::shared_ptr<NumberPicker> priority;
    std::shared_ptr<PushableButton> btnAdd;
    std::shared_ptr<PushableButton> btnDel;
    std::shared_ptr<Select> list;
    std::shared_ptr<PushableButton> btnOrder1;
    std::shared_ptr<PushableButton> btnOrder2;
    std::vector<Option> options;
    int nextIdx = 0;
};

#endif // APPLICATION_H

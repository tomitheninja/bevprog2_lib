#ifndef LISTBOX_H
#define LISTBOX_H

#include "Widget.h"
#include "label.h"

class ListBox : public Widget
{
public:
    ListBox(const Vector2 &position, const std::vector<std::string> &options);
    virtual ~ListBox() = default;

    void setOptions(const std::vector<std::string> &options);

    void draw() const override;
    void update() override;
    EventResult handle(const genv::event &ev, const Vector2 &cursor, bool &canCaptureFocus) override;

    bool isOpen() const { return _isOpen; };

    void setOpenLength(int length);

    void tryIncr();
    void tryDecr();

protected:
    void setOpen(bool isOpen);

private:
    void updateOptions();
    void updateLabels();

    std::vector<std::string> _options;
    int _selectedIndex = 0;
    int _firstIndex = 0;
    int _displayMany = 1;
    bool _isOpen = false;
    Label _lbPrimary;
    std::vector<Label *> _labels;
};

#endif // LISTBOX_H

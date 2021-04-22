#include <memory>
#include "list_box.h"

ListBox::ListBox(const Vector2 &position, const std::vector<std::string> &options) : Widget(position), _lbPrimary(position)
{
    _lbPrimary.addEvent([&](const genv::event &evt, const Vector2 &cursor) {
        // open on click
        if (!isOpen() && evt.button == genv::btn_left && containsPoint(cursor))
        {
            setOpen(true);
            return EventResult::Handled;
        }
        return EventResult::Unhandled;
    });

    addEvent([&](const genv::event &evt, const Vector2 &cursor) {
        // close when lost focus
        if (isOpen() && !isFocused() && evt.button == genv::btn_left && !containsPoint(cursor))
        {
            setOpen(false);
            return EventResult::Continue;
        }

        // change selected option by arrows
        if (isFocused() && evt.type == genv::ev_key)
        {
            switch (evt.keycode)
            {
            case genv::key_up:
                tryDecr();
                return EventResult::Handled;
            case genv::key_down:
                tryIncr();
                return EventResult::Handled;
            }
        }
        return EventResult::Unhandled;
    });

    addEvent([&](const genv::event &evt, const Vector2 &cursor) {
        if (isOpen() && containsPoint(cursor))
        {
            switch (evt.button)
            {
            case genv::btn_wheelup:
                tryDecr();
                return EventResult::Continue;
            case genv::btn_wheeldown:
                tryIncr();
                return EventResult::Continue;
            }
        }
        return EventResult::Unhandled;
    });

    setOptions(options);
    setBorders(true, true, false, true);
    setBackground(true);
    update();
};

void ListBox::draw() const
{
    Widget::draw();
    if (_isOpen)
    {
        for (const auto &p_lb : _labels)
        {
            p_lb->draw();
        }
    }
    else
    {
        _lbPrimary.draw();
    }
}

void ListBox::update()
{
    if (isOpen())
    {
        setBorders(true, true, true, true);
        int lbHeight = _lbPrimary.getSize().y();
        int cnt = _labels.size();
        setSize(Vector2(getSize().x(), cnt * lbHeight));
        for (int i = 0; i < cnt; i++)
        {
            _labels[i]->moveTo(getPosition() + Vector2{0, i * lbHeight});
        }
    }
    else
    {
        // border
        setBorders(true, true, false, true);
        setSize({110, _lbPrimary.getSize().y()});
        _lbPrimary.moveTo(getPosition() + Vector2{5, 0});
        _lbPrimary.setText(_options[_selectedIndex]);
        _lbPrimary.update();
    }
}

EventResult ListBox::handle(const genv::event &ev, const Vector2 &cursor, bool &canCaptureFocus)
{
    auto r0 = Widget::handle(ev, cursor, canCaptureFocus);
    if (r0 == EventResult::Handled)
        return EventResult::Handled;

    if (isOpen())
    {
        EventResult outerResult = EventResult::Continue;
        for (auto &p_lb : _labels)
        {
            switch (p_lb->handle(ev, cursor))
            {
            case EventResult::Handled:
                return EventResult::Handled;
            case EventResult::Continue:
                outerResult = EventResult::Continue;
            default: (void)0;
            }
        }
        return outerResult;
    }
    else
    {
        return _lbPrimary.handle(ev, cursor);
    }
}

void ListBox::setOptions(const std::vector<std::string> &options)
{
    _options = options;
    updateOptions();
}

void ListBox::updateOptions()
{
    for (auto l : _labels)
        delete l;
    _labels.clear();
    for (int i = _firstIndex; i < _options.size() && i - _firstIndex < _displayMany; i++)
    {
        Label *lb = new Label(getPosition() + Vector2{0, _lbPrimary.getSize().y() * i});
        lb->setText(_options[i]);
        lb->setBorders(true, false, true, false);
        lb->addEvent([&, i, lb](const genv::event &evt, const Vector2 &cursor) {
            if (isOpen() && evt.button == genv::btn_left && lb->containsPoint(cursor))
            {
                _selectedIndex = i + _firstIndex;
                setOpen(false);
                return EventResult::Handled;
            }
            return EventResult::Unhandled;
        });
        _labels.push_back(lb);
    }
    update();
}

void ListBox::setOpen(bool isOpen)
{
    _isOpen = isOpen;
    update();
}

void ListBox::setOpenLength(int length)
{
    _displayMany = length;
    updateOptions();
    update();
}

void ListBox::updateLabels()
{
    for (int i = 0; i < _displayMany; i++)
    {
        _labels[i]->setText(_options[i + _firstIndex]);
    }
    _lbPrimary.setText(_options[_selectedIndex]);
}

void ListBox::tryIncr()
{
    if (isOpen()) {
        if (_firstIndex + _displayMany < _options.size()) {
            _firstIndex++;
        }
    }
    else if (_selectedIndex + 1 < _options.size()) {
        _selectedIndex++;
    }
    updateLabels();
}

void ListBox::tryDecr()
{
    if (isOpen()) {
        if (_firstIndex > 0) {
            _firstIndex--;
        }
    } else if (_selectedIndex > 0) {
        _selectedIndex--;
    }
    updateLabels();
}

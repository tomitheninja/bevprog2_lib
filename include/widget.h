#ifndef WIDGET_H
#define WIDGET_H

#include <memory>
#include "renderable.h"

class Widget;

/// A function that takes an event and the cursor location and the widget, which the event is listening on
/// And returns true if the event is handled and no other widgets should not get this event
typedef std::function<bool(const genv::event &evt, const Vector2 &cursor, Widget &self)> Handler;

class Widget : public Renderable
{
public:
    Widget(std::vector<std::shared_ptr<Widget>> children = {});
    Widget(Widget &&);
    virtual ~Widget();

    // calls draw events
    void draw() const; // calls drawers

    // events
    void addEvent(Handler handler);
    bool handle(const genv::event &evt, const Vector2 cursor, bool &canCaptureFocus);
    bool handle(const genv::event &evt, const Vector2 cursor);

    // parent
    Widget *getParent();

    // focus
    bool isFocused() const;
    static void clearFocus();

    // enable-disable
    void enable();
    void disable();
    bool isEnabled() const;

    // overrides
    int topM() const override; // override to achieve relative positioning
    int leftM() const override;

protected:
    // draw events
    virtual void preDraw() const;
    virtual void preChildDraw() const;
    virtual void postChildDraw() const;
    virtual void postDraw() const;

    std::vector<std::shared_ptr<Widget>> _children;
    std::vector<Handler> _events;

private:
    unsigned int _disabled = 0; // number of parents disabled
    bool _self_disabled = false;
    Widget *_parent = nullptr;
    static Widget *_focused;
};

#endif // WIDGET_H

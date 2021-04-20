#ifndef WIDGET_H
#define WIDGET_H
#include "vector2.h"
#include <vector>
#include <functional>

enum EventResult
{
    Unhandled = 1, // Did not change the widget's state
    Handled,       // Did change the widget's state and the event should not be processed anymore.
    Continue,      // Chaged the widget's state, but should continue processing the event.
};
struct Event
{
    int id;
    std::function<EventResult(genv::event, Vector2)> listener;
};

class Widget
{
public:
    Widget(Vector2 position) : _position(position){};
    virtual ~Widget();
    /**
     * A Vector2 pointing to the top left of the widget
     */
    Vector2 getPosition() const { return _position; }
    Vector2 getSize() const { return _size; }
    /**
     * The new top-left of the widget
     */
    void moveTo(const Vector2 &topLeft);

    /**
     * Returns true if the widget may draw onto the given position.
     */
    virtual bool containsPoint(const Vector2 &cursor) const;

    virtual void draw() = 0;

    /**
     * Registers a new event the widget can handle.
     * @returns The ID of the event
     */
    virtual int addEvent(const Event &event);

    /**
     * Send an event to the widget to handle.
     *
     */
    virtual EventResult handle(const genv::event &evt, const Vector2 &cursor);

protected:
    void setSize(const Vector2 &size);
    /**
     * Can be used to update the hidden properties of the widget
     * For example when a label might need to be updated, when changing it's text
     */
    virtual void update();

private:
    Vector2 _position;
    Vector2 _size = {0, 0};
    std::vector<*Event> listeners; // TODO: something more data oriented?
};

#endif // WIDGET_H

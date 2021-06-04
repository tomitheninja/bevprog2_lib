#ifndef APPLICATION_H
#define APPLICATION_H

#include "button.h"
#include "text_input.h"

class Application
{
public:
    Application();
    virtual ~Application();
    bool tick();

protected:
private:
    Vector2 _screen;
    genv::event _ev;
    std::vector<std::shared_ptr<Widget>> _ws;
    Vector2 _cursor;
};

#endif // APPLICATION_H

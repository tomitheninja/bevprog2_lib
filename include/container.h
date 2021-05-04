#ifndef CONTAINER_H
#define CONTAINER_H

#include "widget.h"

// A widget that auto resizes itself to contain all children elements
class Container : public Widget
{
public:
    Container(std::vector<std::shared_ptr<Widget>> children);
    virtual ~Container();

protected:
private:
};

#endif // CONTAINER_H

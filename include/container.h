#ifndef CONTAINER_H
#define CONTAINER_H

#include "widget.h"

class Container : public Widget
{
public:
    Container(const std::vector<Styler> &styles = {}, const std::vector<Widget *> &children = {});
    virtual ~Container();

protected:
private:
};

#endif // CONTAINER_H

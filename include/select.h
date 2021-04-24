#ifndef SELECT_H
#define SELECT_H

#include "container.h"


class Select : public Container
{
    public:
        Select(const std::vector<std::string> &list = {}, const std::vector<Styler> &styles = {});
        virtual ~Select();
        bool isOpen() const;


    protected:
        bool _isOpen;
        int _selectedIdx = 0;

    private:
};

#endif // SELECT_H

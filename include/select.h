#ifndef SELECT_H
#define SELECT_H

#include "container.h"


class Select : public Container
{
    public:
        Select(const std::vector<std::string> &list = {}, const std::vector<Styler> &styles = {});
        virtual ~Select();
        bool isOpen() const;
        void scrollUp();
        void scrollDown();

        std::string getValue() const;
        void displayMany(int many);

    protected:
        void postChildDraw() const override;
        bool _isOpen;
        int _many;
        int _offset = 0;
        int _selectedIdx = 0;

    private:
};

#endif // SELECT_H

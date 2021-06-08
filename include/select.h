#ifndef SELECT_H
#define SELECT_H

#include "container.h"

class Select : public Container
{
public:
    Select(const std::vector<std::string> &list = {});
    virtual ~Select();
    void appendOption(const std::string &txt);
    void setOptions(const std::vector<std::string> &list = {});
    bool isOpen() const;
    void scrollUp();
    void scrollDown();

    std::string getValue() const;
    void displayMany(int many);
    int getSelectedIdx() const;
    void setSelectedIdx(int idx);

protected:
    void postChildDraw() const override;
    bool _isOpen = false;
    int _many = 0;
    int _manyRequested = 3;
    int _offset = 0;
    int _selectedIdx = 0;

private:
};

#endif // SELECT_H

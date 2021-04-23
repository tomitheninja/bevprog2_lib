#ifndef FIXED_SIZE_LABEL_H
#define FIXED_SIZE_LABEL_H

#include "widget.h"


class FixedSizeLabel : public Widget
{
    public:
        FixedSizeLabel(const std::string &text, const std::vector<Styler> &styles = {}, bool centered = false);
        virtual ~FixedSizeLabel();

        std::string getText() const;
        void setText(const std::string &text);

    protected:
        void preChildDraw() const override;
        std::string _text;
        bool _centered;


    private:
};

#endif // FIXED_SIZE_LABEL_H

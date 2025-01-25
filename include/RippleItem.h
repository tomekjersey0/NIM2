#pragma once
#ifndef RIPPLEITEM_H
#define RIPPLEITEM_H

#include "Ripple.h"
#include "RippleList.h"
#include "enums.h"

class RippleItem : public Ripple {
    private:
        int x, y;
        std::string text;
        COLOR color;
        RippleList * parent;
        bool showing;

    public:
        RippleItem(RippleList * _parent, std::string _text, COLOR _color = COLOR::NORMAL);
        void ShowRipple(bool show);
        void Update() override;
        void SetX(int _x) override;
        void SetY(int _y) override;
        std::string GetText() override;
};

#endif
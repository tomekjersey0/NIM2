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

    public:
        RippleItem(RippleList * _parent, std::string _text, COLOR _color = COLOR::NORMAL);
        void Update() override;
        void SetX(int _x) { x = _x; };
        void SetY(int _y) { y = _y; };
        void getXY(int& _x, int& _y) { _x = x; _y = y; };
};

#endif
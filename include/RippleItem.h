#pragma once
#ifndef RIPPLE_ITEM_H
#define RIPPLE_ITEM_H

#include "Ripple.h"
#include "RippleList.h"
#include "Animation.h"
#include "enums.h"

class RippleItem : public Ripple, public Animation 
{
    private:
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
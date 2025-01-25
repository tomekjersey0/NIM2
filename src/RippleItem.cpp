#include "RippleItem.h"

class RippleList;

RippleItem::RippleItem(RippleList * _parent, std::string _text, COLOR _color) : 
    Ripple(_parent),
    Animation(_text, 1, 0.05),
    parent(_parent),
    color(_color),
    showing(true)
{
    SetPositions(y, x);
    win = parent->GetWindow();
};

void RippleItem::ShowRipple(bool show) {
    showing = show;
}

void RippleItem::Update() {
    if (showing) {
        wattron(parent->GetWindow(), COLOR_PAIR(color));

        Animate();

        wattroff(parent->GetWindow(), COLOR_PAIR(color));
    }
}

void RippleItem::SetX(int _x) {
    x = _x;
}

void RippleItem::SetY(int _y) {
    y = _y;
}

std::string RippleItem::GetText() {
    return text;
}

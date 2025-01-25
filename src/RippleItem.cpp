#include "RippleItem.h"

class RippleList;

RippleItem::RippleItem(RippleList * _parent, std::string _text, COLOR _color) : 
    Ripple(_parent),
    parent(_parent),
    text(_text),
    color(_color),
    showing(true)
{};

void RippleItem::ShowRipple(bool show) {
    showing = show;
}

void RippleItem::Update() {
    if (showing) {
        wattron(parent->GetWindow(), COLOR_PAIR(color));
        mvwprintw(parent->GetWindow(), y, x, text.c_str());
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

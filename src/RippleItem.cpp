#include "RippleItem.h"

class RippleList;

RippleItem::RippleItem(RippleList * _parent, std::string _text, COLOR _color) : 
    Ripple(_parent),
    parent(_parent),
    text(_text),
    color(_color)
{};

void RippleItem::Update() {
    int x, y;
}


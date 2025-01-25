#include "RippleList.h"

class WindowClass;

RippleList::RippleList(WindowClass * _parent, int y, int x, void (*_content)(RippleList * parent), int gap, ORIENTATION orientation) : 
    Ripple(_parent),
    parent(_parent),
    content(_content),
    x(x),
    y(y),
    gap(gap),
    orientation(orientation)
{
    // Adds all the items to the list
    if (content) {
        content(this);
    }

    SetItemPositions();
};

void RippleList::SetItemPositions() {
    // Set the positions of the items
    int _x = x;
    int _y = y;
    for (auto item : items) {
        item->SetX(_x);
        item->SetY(_y);
        if (orientation == ORIENTATION::VERTICAL) {
            _y += gap;
        } else {
            _x += gap + item->GetText().length();
        }
    }
}

void RippleList::AddRipple(Ripple * item) {
    items.push_back(item);
}

void RippleList::Update() {
    for (Ripple  * rip : items) {
        rip->Update();
    }
}

WindowClass * RippleList::GetParent() {
    return parent;
}

WINDOW * RippleList::GetWindow() {
    return parent->getWindow();
}
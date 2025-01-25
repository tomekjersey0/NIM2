#include "RippleList.h"

class WindowClass;

RippleList::RippleList(WindowClass * _parent, int x, int y, void (*_content)(RippleList * parent), ORIENTATION orientation) : 
    Ripple(_parent),
    content(_content)
{
    if (content) {
        content(this);
    }
};

void RippleList::Update() {
    for (Ripple  * rip : items) {
        rip->Update();
    }
}
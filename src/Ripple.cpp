#include "Ripple.h"
#include "RippleList.h"
#include "WindowClass.h"

Ripple::Ripple(WindowClass * _parent) :
    parent(_parent),
    parentList(nullptr)
{
    parent->AddRipple(this);
};

Ripple::Ripple(RippleList * _parent) :
    parent(nullptr),
    parentList(_parent)
{
    parentList->AddRipple(this);
};
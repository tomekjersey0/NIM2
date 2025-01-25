#pragma once
#ifndef RIPPLE_H
#define RIPPLE_H

class WindowClass;
class RippleList;

class Ripple {
    private:
        WindowClass * parent;
        RippleList * parentList;

    public:
        Ripple(WindowClass * _parent);
        Ripple(RippleList * _parent);
        virtual void Update() = 0;
};

#endif
#pragma once
#ifndef RIPPLE_H
#define RIPPLE_H

#include <string>

class WindowClass;
class RippleList;

class Ripple 
{
    private:
        WindowClass * parent;
        RippleList * parentList;

    public:
        Ripple(WindowClass * _parent);
        Ripple(RippleList * _parent);
        virtual void Update() = 0;
        virtual void SetX(int _x) {}
        virtual void SetY(int _y) {}
        virtual std::string GetText() {return "";};
};

#endif
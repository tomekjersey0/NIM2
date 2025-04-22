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
        virtual ~Ripple() = default;
        virtual void Update() = 0;
        virtual void SetX(int _x) {};
        virtual void SetY(int _y) {};
        virtual int GetX() const { return 0; };
        virtual int GetY() const { return 0; };
        virtual void MoveRipple(int dx, int dy) {};
        virtual void MoveRippleTo(int _x, int _y) {};
        virtual std::string GetText() {return "";};
};

#endif
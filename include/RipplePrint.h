#pragma once
#ifndef RIPPLEPRINT_H
#define RIPPLEPRINT_H

#include "enums.h"
#include "Ripple.h"
#include "Animation.h"

#include <string>
#include <chrono>
#include <curses.h>

class WindowClass;

class RipplePrint : public Ripple, public Animation
{
    private:
        COLOR color;
        WindowClass * parent;

    public:
        RipplePrint(WindowClass * _parent, int _y, int _x, std::string _text, double _interval = -1, COLOR _color = COLOR::NORMAL, double _delay = 0.05);
        std::chrono::system_clock::time_point getStartTime();
        int getX();
        int getY();
        std::string GetText() override;
        void setColor(COLOR _color);
        void Update() override;
};
#endif
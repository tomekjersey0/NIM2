#pragma once
#ifndef RIPPLEPRINT_H
#define RIPPLEPRINT_H

#include <string>
#include "enums.h"
#include <chrono>
#include <curses.h>

class WindowClass;

class RipplePrint 
{
    private:
        std::string text, nowText;
        int progress, x, y;
        bool done, looping;
        double delay, interval;
        COLOR color;
        std::chrono::_V2::system_clock::time_point startTime;
        WindowClass * parent;
        WINDOW * win;

    public:
        RipplePrint(WindowClass * _parent, int _y, int _x, std::string _text, double _interval = -1, double _delay = 0.05, COLOR _color = COLOR::NORMAL);
        std::chrono::_V2::system_clock::time_point getStartTime();
        int getX();
        int getY();
        std::string getText();
        void eraseRipple();
        void restartRipple();
        void Update();
};

#endif
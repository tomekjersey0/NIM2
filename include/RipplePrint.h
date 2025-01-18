#ifndef RIPPLEPRINT_H
#define RIPPLEPRINT_H

#include <curses.h>
#include <string>
#include <chrono>
#include "enums.h"
#include "WindowClass.h"

class RipplePrint {
    private:
        std::string text;
        int progress, delay, x, y;
        COLOR color;
        std::chrono::_V2::system_clock::time_point startTime;
        WindowClass * parent;
        WINDOW * win;

    public:
        RipplePrint(WindowClass * _parent, std::string _text, int _x, int _y, int _delay=0.03, COLOR _color=COLOR::NORMAL) : 
            parent(_parent),
            text(_text),
            x(_x),
            y(_y),
            delay(_delay),
            color(_color)
        {
            startTime = std::chrono::system_clock::now();
            progress = 0;
            parent->AddRipple(this);
            win = parent->getWindow();
        }
        std::chrono::_V2::system_clock::time_point getStartTime();
        int getX();
        int getY();
        std::string getText();
        void Update();
};
#endif
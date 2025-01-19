#ifndef RIPPLEPRINT_H
#define RIPPLEPRINT_H

#include <curses.h>
#include <string>
#include <chrono>
#include "enums.h"

class WindowClass;

class RipplePrint {
    private:
        std::string text;
        int progress, delay, x, y;
        COLOR color;
        std::chrono::_V2::system_clock::time_point startTime;
        WindowClass * parent;
        WINDOW * win;

    public:
        RipplePrint(WindowClass * _parent, std::string _text, int _x, int _y, int _delay=0.03, COLOR _color=COLOR::NORMAL);
        std::chrono::_V2::system_clock::time_point getStartTime();
        int getX();
        int getY();
        std::string getText();
        void Update();
};
#endif
#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <chrono>
#include <curses.h>

class Animation {
    protected:
        int x, y;
        std::string text;
        WINDOW * win;
        std::string nowText;
        int progress;
        bool done, looping;
        double delay, interval;
        std::chrono::_V2::system_clock::time_point startTime, startAnimTime;

    public:
        Animation(int _y, int _x, std::string _text, double _interval, double _delay);
        Animation(std::string text, double _interval, double _delay);
        void eraseRipple();
        void restartRipple();
        void Animate();
        void SetPositions(int _y, int _x);
};

#endif
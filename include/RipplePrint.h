#pragma once
#ifndef RIPPLE_PRINT_H
#define RIPPLE_PRINT_H

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
        int GetX() const override;
        int GetY() const override;
        void SetX(int _x) override;
        void SetY(int _y) override;
        void MoveRipple(int dx, int dy) override;
        void MoveRippleTo(int _x, int _y) override;
        std::string GetText() override;
        void setColor(COLOR _color);
        void Update() override;
};
#endif
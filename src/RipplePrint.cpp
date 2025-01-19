#include "WindowClass.h"
#include "RipplePrint.h"

RipplePrint::RipplePrint(WindowClass * _parent, std::string _text, int _x, int _y, int _delay, COLOR _color) : 
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

std::chrono::_V2::system_clock::time_point RipplePrint::getStartTime() {
    return startTime;
}

int RipplePrint::getX() {
    return x;
}

int RipplePrint::getY() {
    return y;
}

std::string RipplePrint::getText() {
    return text;
}

void RipplePrint::Update() {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = now - startTime;
    double elapsedSeconds = elapsed.count();
    mvwprintw(win, 1, 1, "%.2f", elapsedSeconds);
}
#include "RipplePrint.h"
#include "WindowClass.h"

RipplePrint::RipplePrint(WindowClass * _parent, int _y, int _x, std::string _text, double _interval, COLOR _color, double _delay) :
    Ripple(_parent),
    Animation(_y, _x, _text, _interval, _delay),
    parent(_parent),
    color(_color)
{
    win = parent->getWindow();
}

std::chrono::system_clock::time_point RipplePrint::getStartTime() {
    return startTime;
}

int RipplePrint::getX() {
    return x;
}

int RipplePrint::getY() {
    return y;
}

std::string RipplePrint::GetText() {
    return text;
}

void RipplePrint::setColor(COLOR _color) {
    color = _color;
}


void RipplePrint::Update() {
    wattron(win, COLOR_PAIR(color));

    Animate();

    wattroff(win, COLOR_PAIR(color));
}

#include "RipplePrint.h"
#include "WindowClass.h"

RipplePrint::RipplePrint(WindowClass * _parent, int _y, int _x, std::string _text, double _interval, COLOR _color, double _delay) :
    Ripple(_parent),
    parent(_parent),
    text(_text),
    x(_x),
    y(_y),
    delay(_delay),
    color(_color),
    interval(_interval)
{
    startTime = std::chrono::system_clock::now();
    progress = 0;
    win = parent->getWindow();
    nowText = "";
    if (_interval < 0 /* so is -1 or bogus value*/) {
        // assume it hasn't been set
        looping = false;
    }
    else {
        looping = true;
    }
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

std::string RipplePrint::GetText() {
    return text;
}

void RipplePrint::setColor(COLOR _color) {
    color = _color;
}

void RipplePrint::eraseRipple() {
    std::string textBlank(text.length(), ' ');
    mvwprintw(win, y, x, textBlank.c_str());
}

void RipplePrint::restartRipple() {
    eraseRipple();
    done = false;
    progress = 0;
    nowText = "";
}

void RipplePrint::Update() {
    wattron(win, COLOR_PAIR(color));

    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = now - startTime;
    double elapsedSeconds = elapsed.count();

    if (elapsedSeconds >= delay && !done) {
        nowText += text[progress];
        mvwprintw(win, y, x, nowText.c_str());
        startTime = std::chrono::system_clock::now();
        progress++;
        if (progress == text.length()) {
            done = true;
            progress = 0;
        }
    }

    if (looping && done) {
        if (elapsedSeconds >= interval) {
            restartRipple();
        }
    }

    wattroff(win, COLOR_PAIR(color));
}

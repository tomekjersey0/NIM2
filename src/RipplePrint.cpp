#include "RipplePrint.h"
#include "WindowClass.h"

RipplePrint::RipplePrint(WindowClass * _parent, int _y, int _x, std::string _text,double _interval, double _delay, COLOR _color) :
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
    parent->AddRipple(this);
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

std::string RipplePrint::getText() {
    return text;
}

void RipplePrint::eraseRipple() {
    std::string textBlank;
    for (int i = 0; i < text.length(); i++) {
        textBlank += " ";
    }
    mvwprintw(win, y, x, textBlank.c_str());
}

void RipplePrint::restartRipple() {
    eraseRipple();
    done = false;
    progress = 0;
    nowText = "";
}

void RipplePrint::Update() {
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
}
    mvwprintw(win, 1, 1, "%.2f", elapsedSeconds);
}

#include "RipplePrint.h"

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
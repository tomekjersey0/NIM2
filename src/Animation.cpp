#include "Animation.h"

Animation::Animation(int _y, int _x, std::string _text, double _interval, double _delay) :
    Animation(_text, _interval, _delay)
{
    y = _y;
    x = _x;
}

Animation::Animation(std::string _text, double _interval, double _delay) : 
    text(_text),
    interval(_interval),
    delay(_delay)
{
    startTime = std::chrono::system_clock::now();
    startAnimTime = std::chrono::system_clock::now();
    done = false;
    progress = 0;
    nowText = "";
    if (_interval < 0 /* so is -1 or bogus value*/) {
        // assume it hasn't been set
        looping = false;
    }
    else {
        looping = true;
    }
};


void Animation::SetPositions(int _y, int _x) {
    y = _y;
    x = _x;
}

void Animation::eraseRipple() {
    std::string textBlank(text.length(), ' ');
    mvwprintw(win, y, x, "%s", textBlank.c_str());
}

void Animation::restartRipple() {
    eraseRipple();
    done = false;
    progress = 0;
    nowText = "";
}

void Animation::Animate() {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = now - startTime;
    std::chrono::duration<double> elapsedAnim = now - startAnimTime;
    double elapsedSecondsFromStartAnimation = elapsedAnim.count();
    double elapsedSecondsFromLastCharacter = elapsed.count();

    if (elapsedSecondsFromLastCharacter >= delay && !done) {
        nowText += text[progress];
        mvwprintw(win, y, x, "%s", nowText.c_str());
        startTime = std::chrono::system_clock::now();
        progress++;
        if (progress == text.length()) {
            done = true;
            progress = 0;
        }
    }

    if (looping && done) {
        if (elapsedSecondsFromStartAnimation >= interval) {
            restartRipple();
            startAnimTime = std::chrono::system_clock::now();
        }
    }
}